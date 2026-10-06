/*
 * HazardBot - Sensor Calibration Script
 * Team VERTEX
 * Engineers: Mohamed Adel (MQ-2), Malak Khalid (MQ-135, DHT11)
 */

#include "DHT.h"

// --- Pin Definitions ---
#define MQ2_PIN 36      // Mohamed Adel: MQ-2 Analog Input (ADC1)
#define MQ135_PIN 39    // Malak Khalid: MQ-135 Analog Input (ADC1)
#define DHTPIN 21       // Malak Khalid: DHT11 Digital Data Input
#define DHTTYPE DHT11   // Define the exact DHT sensor type

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start the serial monitor at 115200 baud rate
  Serial.begin(115200);
  
  // Start the DHT11 sensor
  dht.begin();

  Serial.println("HazardBot Sensors Initializing...");
  Serial.println("Warming up MQ sensors (Please wait 3 minutes)...");
}

void loop() {
  // 1. Read Analog Data (Mohamed & Malak K.)
  int mq2_value = analogRead(MQ2_PIN);
  int mq135_value = analogRead(MQ135_PIN);

  // 2. Read Digital Data (Malak K.)
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Default is Celsius

  // 3. Error Checking for DHT11
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("ERROR: Failed to read from DHT sensor!");
  } else {
    // 4. Print all data to Serial Monitor for Mohra
    Serial.print("MQ-2 (Gas/Smoke): ");
    Serial.print(mq2_value);
    
    Serial.print("  |  MQ-135 (Air Quality): ");
    Serial.print(mq135_value);
    
    Serial.print("  |  Temp: ");
    Serial.print(temperature);
    Serial.print("°C  |  Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }

  // Wait 2 seconds before the next reading
  delay(2000);
}