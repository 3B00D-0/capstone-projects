/*
 * ============================================
 * HazardBot — Stable Firmware v3.1 (FINAL)
 * BLE + WiFi Stable Control Edition + mDNS
 * ============================================
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h> // Required for hazardbot.local
#include "DHT.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// ── WiFi ────────────────────────────────────────
const char* ssid     = "3bood";
const char* password = "90908080";

// ── Async Web Server ────────────────────────────
AsyncWebServer server(80);

// ── BLE ─────────────────────────────────────────
BLEServer* pServer = NULL;
BLECharacteristic* pTxCharacteristic = NULL;

bool deviceConnected = false;
bool oldDeviceConnected = false;

#define SERVICE_UUID           "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID_RX "8a6e9a08-3cf1-45a8-9d51-4e4f7a6f8b9e"
#define CHARACTERISTIC_UUID_TX "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// ── Sensors ─────────────────────────────────────
#define DHTPIN   21
#define DHTTYPE  DHT11

DHT dht(DHTPIN, DHTTYPE);

#define MQ2_PIN   36
#define MQ135_PIN 39

// ── Motors ──────────────────────────────────────
#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33

#define ENA 14
#define ENB 13

#define MOTOR_SPEED 220

// ── Alert Thresholds (RECALIBRATED) ─────────────
const int MQ2_WARNING   = 150;  // Lowered for new 60 baseline
const int MQ2_DANGER    = 300;  // Lowered for new 60 baseline

const int MQ135_WARNING = 500;
const int MQ135_DANGER  = 650;

// ── State ───────────────────────────────────────
volatile float current_temp  = 0.0;
volatile float current_hum   = 0.0;

volatile int current_mq2     = 0;
volatile int current_mq135   = 0;

volatile int current_alert   = 0;

// ── Timers ──────────────────────────────────────
unsigned long lastSensorRead    = 0;
unsigned long lastWiFiCheck     = 0;
unsigned long lastCommandTime   = 0;

const long sensorInterval       = 2000;
const long wifiCheckInterval    = 5000;

// Anti-spam protection
const unsigned long commandCooldown = 120;

// ── Motor Functions ─────────────────────────────
void setupMotors() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  ledcAttach(ENA, 5000, 8);
  ledcAttach(ENB, 5000, 8);

  ledcWrite(ENA, MOTOR_SPEED);
  ledcWrite(ENB, MOTOR_SPEED);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// FIXED RIGHT (Kept from your calibration)
void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// FIXED LEFT (Kept from your calibration)
void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ── Command Handler ─────────────────────────────
void executeCommand(char cmd) {

  // Prevent flooding / hallucination
  if (millis() - lastCommandTime < commandCooldown) {
    return;
  }

  lastCommandTime = millis();

  if (cmd == 'F' || cmd == 'f') {
    moveForward();
  }
  else if (cmd == 'B' || cmd == 'b') {
    moveBackward();
  }
  else if (cmd == 'R' || cmd == 'r') {
    turnRight();
  }
  else if (cmd == 'L' || cmd == 'l') {
    turnLeft();
  }
  else if (cmd == 'S' || cmd == 's') {
    stopMotors();
  }
}

// ── BLE Callbacks ───────────────────────────────
class MyServerCallbacks : public BLEServerCallbacks {

  void onConnect(BLEServer* s) {
    deviceConnected = true;
    Serial.println("BLE Device Connected");
  }

  void onDisconnect(BLEServer* s) {
    deviceConnected = false;
    Serial.println("BLE Device Disconnected");
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {

  void onWrite(BLECharacteristic* c) {
    String v = c->getValue();
    if (v.length() > 0) {
      executeCommand(v[0]);
    }
  }
};

// ── Build JSON ──────────────────────────────────
String buildJSON() {

  return
    "{\"temp\":"  + String(current_temp, 1) +
    ",\"hum\":"   + String(current_hum, 1) +
    ",\"mq2\":"   + String(current_mq2) +
    ",\"mq135\":" + String(current_mq135) +
    ",\"alert\":" + String(current_alert) +
    "}";
}

// ── WiFi Reconnect ──────────────────────────────
void checkWiFi() {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost — reconnecting...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);

    int tries = 0;
    while (WiFi.status() != WL_CONNECTED && tries < 20) {
      delay(500);
      tries++;
      Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("\nReconnected: ");
      Serial.println(WiFi.localIP());
    }
  }
}

// ── Setup ───────────────────────────────────────
void setup() {

  Serial.begin(115200);

  setupMotors();
  stopMotors();

  dht.begin();

  // ── WiFi ────────────────────────────────────
  WiFi.setAutoReconnect(true);
  WiFi.persistent(false);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nIP: ");
  Serial.println(WiFi.localIP());

  // ── Start mDNS (Fixes Dynamic IP Issue) ─────
  if (!MDNS.begin("hazardbot")) {
    Serial.println("Error setting up MDNS responder!");
  } else {
    Serial.println("mDNS responder started. Connect to http://hazardbot.local");
  }

  // ── Web Server Routes ───────────────────────
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest* req) {
    req->send(200, "application/json", buildJSON());
  });

  server.on("/cmd", HTTP_GET, [](AsyncWebServerRequest* req) {
    if (req->hasParam("val")) {
      String val = req->getParam("val")->value();
      if (val.length() > 0) {
        executeCommand(val[0]);
      }
    }
    req->send(200, "application/json", buildJSON());
  });

  // ── CORS ────────────────────────────────────
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET");

  server.begin();

  Serial.println("Async server started.");

  // ── BLE Stabilization ───────────────────────
  btStop();
  delay(200);
  btStart();
  delay(200);

  // ── BLE Setup ───────────────────────────────
  BLEDevice::init("HazardBot_BLE");

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService* svc = pServer->createService(SERVICE_UUID);

  pTxCharacteristic = svc->createCharacteristic(
    CHARACTERISTIC_UUID_TX,
    BLECharacteristic::PROPERTY_NOTIFY
  );

  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic* rxChar = svc->createCharacteristic(
    CHARACTERISTIC_UUID_RX,
    BLECharacteristic::PROPERTY_WRITE
  );

  rxChar->setCallbacks(new MyCallbacks());

  svc->start();
  pServer->getAdvertising()->start();

  Serial.println("BLE started: HazardBot_BLE");
}

// ── Loop ────────────────────────────────────────
void loop() {

  unsigned long now = millis();

  // ── Sensor Reading ──────────────────────────
  if (now - lastSensorRead >= sensorInterval) {

    lastSensorRead = now;

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (!isnan(h) && !isnan(t)) {
      current_hum  = h;
      current_temp = t;
    }

    current_mq2   = analogRead(MQ2_PIN);
    current_mq135 = analogRead(MQ135_PIN);

    current_alert =
      (current_mq2 >= MQ2_DANGER || current_mq135 >= MQ135_DANGER) ? 2 :
      (current_mq2 >= MQ2_WARNING || current_mq135 >= MQ135_WARNING) ? 1 : 0;

    // ── BLE Notify ────────────────────────────
    if (deviceConnected) {

      String payload =
        "Gas:" + String(current_mq2) +
        "|Air:" + String(current_mq135) +
        "|T:" + String(current_temp, 1) +
        "|H:" + String(current_hum, 1) +
        "|A:" + String(current_alert);

      pTxCharacteristic->setValue(payload.c_str());
      pTxCharacteristic->notify();
    }

    Serial.print("T:");
    Serial.print(current_temp);

    Serial.print(" H:");
    Serial.print(current_hum);

    Serial.print(" MQ2:");
    Serial.print(current_mq2);

    Serial.print(" MQ135:");
    Serial.println(current_mq135);
  }

  // ── WiFi Watchdog ───────────────────────────
  if (now - lastWiFiCheck >= wifiCheckInterval) {
    lastWiFiCheck = now;
    checkWiFi();
  }

  // ── BLE Reconnect ───────────────────────────
  if (!deviceConnected && oldDeviceConnected) {
    delay(500);
    pServer->startAdvertising();
    oldDeviceConnected = false;
  }

  if (deviceConnected && !oldDeviceConnected) {
    oldDeviceConnected = true;
  }
}