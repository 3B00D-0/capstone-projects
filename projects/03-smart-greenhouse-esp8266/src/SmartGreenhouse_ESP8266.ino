// ══════════════════════════════════════════════════════
//   Smart Plant System — ESP8266 NodeMCU
//   Updated: OLED Display + Auto Fan (No Button) + Digital LDR
// ══════════════════════════════════════════════════════

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ─────────────────────────────────────────
//  PIN DEFINITIONS
// ─────────────────────────────────────────
#define RELAY_FAN    D5   // Relay IN1 → Fan
#define RELAY_PUMP   D6   // Relay IN2 → Pump
#define RELAY_LIGHT  D7   // Relay IN3 → UV Light

#define DHTPIN       D4   // DHT22 DATA
#define DHTTYPE      DHT22

#define SOIL_PIN     A0   // Analog Pin 0 → Soil Sensor AO
#define LDR_PIN      D3   // Digital Pin 3 → LDR Module (DO Pin)

// ─────────────────────────────────────────
//  RELAY LOGIC (ACTIVE LOW)
// ─────────────────────────────────────────
#define RELAY_ON   LOW
#define RELAY_OFF  HIGH

// ─────────────────────────────────────────
//  THRESHOLDS & SETTINGS
// ─────────────────────────────────────────
#define SOIL_DRY_THRESHOLD   650   // above → pump ON
#define SOIL_WET_THRESHOLD   350   // below → pump OFF
#define TEMP_HOT             30.0  // °C above → fan ON
#define TEMP_COOL            25.0  // °C below → fan OFF

// LDR Digital Module Logic:
// Usually outputs HIGH (1) when DARK, and LOW (0) when LIGHT.
// *You may need to swap these if your specific module is reversed*
#define LDR_DARK   HIGH
#define LDR_LIGHT  LOW

// ─────────────────────────────────────────
//  OBJECTS
// ─────────────────────────────────────────
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);

// ─────────────────────────────────────────
//  STATE VARIABLES
// ─────────────────────────────────────────
bool fanState   = false;
bool pumpState  = false;
bool lightState = false;

unsigned long lastSensorUpdate = 0;
const unsigned long SENSOR_INTERVAL = 1000; // Update every 1 second

// ─────────────────────────────────────────
//  HELPER: Set Relay Safely
// ─────────────────────────────────────────
void setRelay(uint8_t pin, bool turnOn) {
  digitalWrite(pin, turnOn ? RELAY_ON : RELAY_OFF);
}

// ─────────────────────────────────────────
//  SETUP
// ─────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  Serial.println("\n\n=== Smart Plant ESP8266 ===");

  // Init relays to OFF before setting as OUTPUT to prevent brief ON pulse
  digitalWrite(RELAY_FAN,   RELAY_OFF);
  digitalWrite(RELAY_PUMP,  RELAY_OFF);
  digitalWrite(RELAY_LIGHT, RELAY_OFF);
  
  pinMode(RELAY_FAN,   OUTPUT);
  pinMode(RELAY_PUMP,  OUTPUT);
  pinMode(RELAY_LIGHT, OUTPUT);

  // Set LDR Pin as Input
  pinMode(LDR_PIN, INPUT);

  // Initialize I2C (SDA=D2, SCL=D1)
  Wire.begin(D2, D1);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Boot Screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Smart Plant v2");
  display.println("Booting Sensors...");
  display.display();
  delay(1500);

  // Start DHT22
  dht.begin();
  Serial.println("Setup complete. Running...");
}

// ─────────────────────────────────────────
//  LOOP
// ─────────────────────────────────────────
void loop() {
  unsigned long now = millis();

  // ─── SENSOR UPDATE (every 1 second) ───
  if (now - lastSensorUpdate >= SENSOR_INTERVAL) {
    lastSensorUpdate = now;

    // Read Sensors
    int   soil = analogRead(SOIL_PIN);        
    float temp = dht.readTemperature();       
    float hum  = dht.readHumidity();
    int   ldrValue = digitalRead(LDR_PIN);

    // ── AUTO: Fan (Temperature based) ──
    if (!isnan(temp)) {
      if (temp > TEMP_HOT)        fanState = true;
      else if (temp < TEMP_COOL)  fanState = false;
      setRelay(RELAY_FAN, fanState);
    } else {
      Serial.println("[ERR] DHT22 read failed!");
    }

    // ── AUTO: Pump (Soil Moisture based) ──
    if (soil > SOIL_DRY_THRESHOLD)       pumpState = true;
    else if (soil < SOIL_WET_THRESHOLD)  pumpState = false;
    setRelay(RELAY_PUMP, pumpState);

    // ── AUTO: UV Light (LDR based) ──
    // If it is dark, turn on the light.
    if (ldrValue == LDR_DARK) {
      lightState = true;
    } else {
      lightState = false;
    }
    setRelay(RELAY_LIGHT, lightState);

    // ── OLED Display Update ────────────────
    display.clearDisplay();
    display.setCursor(0, 0);
    
    // Row 1: Soil & Pump
    display.print("Soil: ");
    display.print(soil);
    display.print(pumpState ? "  PMP:ON" : "  PMP:OFF");
    
    // Row 2: Temp & Humidity
    display.setCursor(0, 16); 
    if (!isnan(temp)) {
      display.print("T: ");
      display.print(temp, 1);
      display.print("C  H: ");
      display.print((int)hum);
      display.print("%");
    } else {
      display.print("DHT ERR!");
    }

    // Row 3: Light & Fan Status
    display.setCursor(0, 32);
    display.print("Fan:");
    display.print(fanState ? "ON " : "OFF");
    display.print(" UV:");
    display.print(lightState ? "ON" : "OFF");
    
    display.display(); 

    // ── Serial Debug ───────────────────────
    Serial.printf(
      "Soil:%4d | T:%.1fC H:%.0f%% | LDR:%s | Fan:%s Pump:%s UV:%s\n",
      soil,
      isnan(temp) ? 0.0 : temp,
      isnan(hum)  ? 0.0 : hum,
      (ldrValue == LDR_DARK) ? "DARK" : "LITE",
      fanState   ? "ON"  : "OFF",
      pumpState  ? "ON"  : "OFF",
      lightState ? "ON"  : "OFF"
    );
  }
}