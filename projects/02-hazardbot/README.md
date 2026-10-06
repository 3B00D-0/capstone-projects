# 🛡️ HazardBot: Hazardous Environment Exploration Rover

> **Capstone Engineering Project · Team VERTEX (9 Members) · Minia University**  
> *Low-Cost Dual-Controlled (Bluetooth + WiFi) Environmental Reconnaissance Rover*

---

## 📌 Executive Summary
**HazardBot** is an autonomous and teleoperated rover engineered to replace human entry into hazardous environments (chemical leaks, enclosed fires, industrial zones). Built for under **$25 USD**, it streams real-time telemetry—flammable gas concentrations, toxic air quality, temperature, and humidity—directly to a mobile Progressive Web App (PWA) and an onboard HTTP server hosted on a single **ESP32-WROOM-32** microcontroller.

---

## ✨ Key Capabilities
- **Dual Teleoperation Modes:**
  - **Bluetooth Mode:** Short-range, zero-latency direct manual joystick navigation via mobile app.
  - **WiFi AP Web Mode:** Local access point hosting an embedded web dashboard for real-time telemetry graphs and remote control.
- **Multi-Hazard Sensor Array:**
  - **MQ-2:** Flammable gases (LPG, Propane, Hydrogen, Smoke).
  - **MQ-135:** Toxic air pollutants (Benzene, Alcohol, Ammonia, CO2, Smoke).
  - **DHT11:** Ambient temperature (0–50°C) and relative humidity.
- **Safety Alert Subsystem:** Immediate audiovisual alarms (Active Buzzer + Red High-Luminance LED) triggered when gas thresholds breach safe limits.
- **Progressive Web App (PWA):** Installable offline web application with full joystick controls and live sensor gauges.

---

## ⚙️ Hardware Architecture & Critical Solutions
| Component | Part | Role |
| :--- | :--- | :--- |
| **Microcontroller** | NodeMCU ESP32-S (ESP32-WROOM-32) | Core compute, WiFi AP, Bluetooth SPP |
| **Motor Driver** | L298N Dual H-Bridge | Dual TT DC gear motor control with PWM speed shaping |
| **Locomotion** | 2× TT DC Motors + Castor Wheel | Differential drive chassis |
| **Power Distribution** | 2× 18650 Li-Ion (7.4V series nominal) | Independent motor driver & logic power |
| **Sensors** | MQ-2, MQ-135, DHT11 | Environmental telemetry collection |
| **Alerts** | Active Buzzer + Red Indicator LED | Threshold breach alert system |

### ⚡ Critical Hardware Engineering Solutions Solved
1. **5V Sensor ↔ 3.3V Logic Level Matching:** MQ analog outputs produce 0–5V, exceeding ESP32 maximum ratings. Solved using precision **10kΩ / 20kΩ voltage dividers** stepping analog voltages down to safe 3.3V limits.
2. **ADC2 & WiFi Hardware Contention:** ESP32 WiFi controller locks all ADC2 channels during transmission. Solved by exclusively routing all analog inputs to **ADC1 channels (GPIO36, GPIO39)**.
3. **Boot Strapping Protection:** GPIO12 strapping pin conflicts with motor ENB lines during reset. Re-routed to **GPIO13** to guarantee reliable boot sequencing.

---

## 📂 Repository Layout
- `firmware/`:
  - [`HazardBot_VERTEX.ino`](./firmware/HazardBot_VERTEX.ino): Production flight sketch (WiFi, Bluetooth, sensor loop).
  - [`HazardBot_Calibration.ino`](./firmware/HazardBot_Calibration.ino): Sensor baseline and PID motor calibration routines.
- `app/`:
  - [`index.html`](./app/index.html): Progressive Web App UI with joystick and real-time dashboard.
  - [`manifest.json`](./app/manifest.json): PWA installation manifest.
  - Icons and design assets.
- [`project.json`](./project.json): Portfolio metadata feed.
