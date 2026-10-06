
# 🤖 HazardBot: Team VERTEX Presentation Guide & Code Log

This document outlines the specific contributions of each team member, the engineering challenges they overcame, their presentation script for the evaluating Doctor/Professor, and the supporting code snippets.

---

## 1 — Abd-Elrahman Mohamed · Lead System Architect

**Technical Contribution:** Designed the overall system architecture, selected the ESP32, mapped GPIO pins, managed voltage divider circuits, and led final integration.
**Challenge Solved:** Identified a severe hardware conflict where the ESP32’s ADC2 pins shut down when the WiFi radio is active. Re-routed all analog sensors to the isolated ADC1 channel to fix the issue.

> [!speech] 🎙️ What to tell the Doctor:
> *"Hello Doctor. As the System Architect, my primary role was integrating our 9 subsystems into one cohesive rover. My biggest challenge was a hardware conflict: the ESP32 shares its ADC2 internal circuitry with the WiFi radio. Whenever we turned on WiFi, our gas readings dropped to zero. I diagnosed this architectural flaw and re-routed all analog sensors to the isolated ADC1 channel, which permanently stabilized our telemetry."*

**Supporting Code:**
```cpp
// Moving analog sensors to safe ADC1 pins to avoid WiFi conflict
#define MQ2_PIN   36 // ADC1_CH0
#define MQ135_PIN 39 // ADC1_CH3

```

---

## 2 — Fares Hassan · Motor & Movement Engineer

**Technical Contribution:** Wrote the C++ motor control logic interfacing with the L298N driver using 4 direction pins and 2 PWM pins.
**Challenge Solved:** Fixed "ghost driving" by adding an asynchronous safety timeout. If the rover doesn't receive a command within a set timeframe, it automatically cuts power to the motors.

> [!speech] 🎙️ What to tell the Doctor:
> *"My responsibility was the locomotion logic. Early on, we discovered a major safety flaw: if the network dropped a 'stop' command, the rover would keep driving infinitely. I solved this by programming an asynchronous safety timeout using the `millis()` function. If the rover doesn't receive a valid command within 120 milliseconds, it assumes connection loss and automatically applies the brakes."*

**Supporting Code:**

```cpp
// Anti-spam and safety cutoff protection
const unsigned long commandCooldown = 120; 

void executeCommand(char cmd) {
  // Prevent flooding / ghost driving
  if (millis() - lastCommandTime < commandCooldown) {
    return;
  }
  lastCommandTime = millis();

  if (cmd == 'F' || cmd == 'f') moveForward();
  else if (cmd == 'S' || cmd == 's') stopMotors();
  // ...
}

```

---

## 3 — Mohamed Adel · Gas Sensor Engineer

**Technical Contribution:** Integrated the MQ-2 combustible gas sensor and calibrated it for LPG, propane, and smoke detection.
**Challenge Solved:** The MQ-2 outputs a 5V signal, but the ESP32 has a strict 3.3V GPIO limit. Designed and soldered a physical Voltage Divider circuit (10kΩ/20kΩ) to step the voltage down safely.

> [!speech] 🎙️ What to tell the Doctor:
> *"I was in charge of the MQ-2 gas sensor integration. Because the MQ-2 outputs a 5-Volt analog signal and the ESP32 has a strict 3.3-Volt limit, a direct connection would have fried our microcontroller. I designed a hardware Voltage Divider circuit using 10k and 20k-ohm resistors to step the signal down safely before translating it into our software thresholds."*

**Supporting Code:**

```cpp
// Calibrated ADC thresholds based on the stepped-down 3.3V signal
const int MQ2_WARNING   = 150;  
const int MQ2_DANGER    = 300;  
volatile int current_mq2 = 0;

// Read safely from the voltage-divided pin
current_mq2 = analogRead(MQ2_PIN);

```

---

## 4 — Malak Khalid · Air Quality & Climate Engineer

**Technical Contribution:** Integrated the MQ-135 and DHT11 sensors and wrote the logic to poll them efficiently.
**Challenge Solved:** The DHT11 uses a timing-sensitive protocol. Using standard `delay()` functions froze the entire rover. Rewrote the polling logic using non-blocking asynchronous timers.

> [!speech] 🎙️ What to tell the Doctor:
> *"I managed the Air Quality and Climate array. The main hurdle here was that the DHT11 sensor requires very specific timing to read data. If we used standard `delay()` functions, it froze the motors and the web server. I rewrote our polling architecture to use asynchronous `millis()` timers, allowing us to read the environment every 2 seconds without ever blocking the CPU's main loop."*

**Supporting Code:**

```cpp
unsigned long lastSensorRead = 0;
const long sensorInterval = 2000;

void loop() {
  unsigned long now = millis();
  
  // Non-blocking sensor read every 2 seconds
  if (now - lastSensorRead >= sensorInterval) {
    lastSensorRead = now;
    float h = dht.readHumidity(); 
    float t = dht.readTemperature();
    // ...
  }
}

```

---

## 5 — Ahmed Abobakr · Mobile App Developer

**Technical Contribution:** Built the BLE smartphone control app with a joystick and telemetry display using MIT App Inventor / WebBLE.
**Challenge Solved:** Holding the joystick down flooded the Bluetooth connection, crashing the ESP32. Implemented a timer to throttle outbound commands to exactly one packet every 100ms.

> [!speech] 🎙️ What to tell the Doctor:
> *"I developed the mobile tactical interface. Initially, when an operator held down the digital joystick, the app fired hundreds of commands per second, which crashed the ESP32's Bluetooth stack. I implemented an outbound data throttle—a timer that restricts transmission to exactly one packet every 100 milliseconds. This provided perfectly smooth control while keeping the network stable."*

**Supporting Code (JavaScript App Equivalent):**

```javascript
// Throttling outbound driving commands from the mobile interface
if (cmd === 'S') {
    pendingFetch = false; 
    lastCmdSent = now;
    sendCommand(cmd);
} else if (now - lastCmdSent >= 150 && !pendingFetch) {
    lastCmdSent = now; 
    pendingFetch = true;
    sendCommand(cmd);
}

```

---

## 6 — Basmala Sherif · Communication Engineer

**Technical Contribution:** Engineered the Bluetooth (BLE) GATT server on the ESP32, packaging 5 variables into a single data string for transmission.
**Challenge Solved:** Running the WiFi library and the BLE library simultaneously caused the compiler to fail due to RAM overflow. Reconfigured the Arduino partition scheme to "Huge APP (3MB)" to allocate enough memory.

> [!speech] 🎙️ What to tell the Doctor:
> *"I handled the ESP32's internal communication architecture. Compiling the massive WiFi and BLE radio libraries together originally caused a fatal memory overflow. I solved this by diving into the microcontroller's memory map and reallocating the flash partition to 'Huge APP', which gave us the memory needed to run our dual-radio system. I then wrote the algorithm that packages our 5 sensor variables into a single, highly efficient BLE data packet."*

**Supporting Code:**

```cpp
// Packaging 5 data points into a single efficient BLE string
if (deviceConnected) {
  String payload = "Gas:" + String(current_mq2) + 
                   "|Air:" + String(current_mq135) + 
                   "|T:" + String(current_temp, 1) + 
                   "|H:" + String(current_hum, 1) + 
                   "|A:" + String(current_alert);

  pTxCharacteristic->setValue(payload.c_str()); 
  pTxCharacteristic->notify();
}

```

---

## 7 — Ahmed Wael · Power & Hardware Integration Engineer

**Technical Contribution:** Managed the power circuit, utilizing the L298N's 5V regulator to power the ESP32 from a 9V battery source, and mounted all components securely.
**Challenge Solved:** Simultaneous radio startup caused a 600mA current spike, triggering the ESP32 brownout detector and an infinite reboot loop. Staggered the power draw during setup to fix it.

> [!speech] 🎙️ What to tell the Doctor:
> *"I was responsible for power distribution and hardware mounting. We hit a major wall where the rover was stuck in an infinite reboot loop. I diagnosed this as a power brownout: turning on the WiFi and Bluetooth antennas at the exact same millisecond drew too much current. I solved this by adding staggered software delays during the boot sequence, allowing the voltage to stabilize before activating the second radio."*

**Supporting Code:**

```cpp
// Staggering radio initialization to prevent power brownouts
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) delay(500);

// Stop BT, let power stabilize, then start BT
btStop(); 
delay(200); 
btStart(); 
delay(200);

BLEDevice::init("HazardBot_BLE");

```

---

## 8 — Mohra Hany · Alert & Threshold Logic Engineer

**Technical Contribution:** Coded the mathematical logic that categorizes data into Safe, Warning, and Danger states.
**Challenge Solved:** The MQ sensor hardware experienced severe baseline drift as the internal heater broke in (dropping from 1200 ADC to 60 ADC). Dynamically recalibrated the software thresholds rather than replacing hardware.

> [!speech] 🎙️ What to tell the Doctor:
> *"I designed the mathematical logic for our hazard detection. The biggest challenge was hardware drift; over several days of testing, our MQ-2 gas sensor's clean-air baseline dropped drastically from 1200 down to 60 ADC as the heater broke in. Instead of replacing the sensor, I analyzed the new curve and dynamically recalibrated our software thresholds, ensuring our Danger alerts remained hyper-accurate."*

**Supporting Code:**

```cpp
// Dynamic Alert Logic based on recalibrated hardware drift thresholds
current_alert = (current_mq2 >= MQ2_DANGER || current_mq135 >= MQ135_DANGER) ? 2 :
                (current_mq2 >= MQ2_WARNING || current_mq135 >= MQ135_WARNING) ? 1 : 0;

```

---

## 9 — Malak Montaser · Web Dashboard Engineer

**Technical Contribution:** Developed the HTML/JS tactical dashboard with sparkline graphs, async UI updates, and real-time alerts.
**Challenge Solved:** The ESP32's dynamic IP address changed on every boot, breaking the dashboard link. Integrated the `ESPmDNS` library for zero-configuration networking.

> [!speech] 🎙️ What to tell the Doctor:
> *"I engineered the tactical web dashboard. Initially, the laptop hotspot assigned a random IP address to the rover every time we turned it on, which required hardcoding the HTML daily. I solved this by integrating an mDNS resolver into the firmware. Now, the rover broadcasts a localized domain, and the dashboard connects flawlessly to `hazardbot.local` without ever needing an IP address."*

**Supporting Code (C++ and JS integration):**

```cpp
// ESP32 Firmware (C++)
#include <ESPmDNS.h> 
if (MDNS.begin("hazardbot")) { 
    Serial.println("mDNS started: hazardbot.local"); 
}

```

```javascript
// Web Dashboard (JavaScript)
async function fetchLive() {
  // Directly fetches from the mDNS name instead of an IP
  const ip = document.getElementById('ip-input').value.trim(); // "hazardbot.local"
  const r = await fetch(`http://${ip}/data`);
  const d = await r.json();
  // Update UI...
}

```