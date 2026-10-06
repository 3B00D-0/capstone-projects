# 🌱 Smart Greenhouse & Automated Plant System

> **IoT Microclimate & Soil Moisture Control with ESP8266 NodeMCU**  
> *Minia University, Faculty of Education — STEM Education & Technology*

---

## 📌 Project Overview
The **Smart Greenhouse System** is an automated IoT microclimate manager designed for precision agriculture and educational biology laboratories. Powered by an **ESP8266 NodeMCU**, the system continuously monitors environmental vital signs (temperature, humidity, soil hydration) and automatically actuates active climate controls without human intervention.

---

## ✨ Features
- **Closed-Loop Soil Hydration:** Resistive soil moisture sensor triggers a 5V submersible water pump when soil moisture falls below calibrated thresholds.
- **Microclimate Regulation:** DHT22 temperature and humidity sensor drives a 5V exhaust fan to vent excess heat.
- **Supplemental Photoperiod Lighting:** Relayed UV grow lighting cycle to maintain photosynthetic activity.
- **Real-Time Visual Feedback:** Adafruit SSD1306 (128×64) OLED I2C display provides real-time telemetry (Temp, Humidity, Soil %, Active Relay states).
- **Light-Sensitive Photoperiod:** Digital LDR Module measures ambient luminosity to trigger supplemental lighting.

---

## 🛠️ Hardware Specification
| Component | Function | Interface / Pin |
| :--- | :--- | :--- |
| **NodeMCU ESP8266** | Central compute & control logic | Core Microcontroller |
| **DHT22** | Ambient temperature & relative humidity | Pin `D4` |
| **Soil Moisture Sensor** | Substrate volumetric water content | Analog Pin `A0` |
| **LDR Sensor Module** | Ambient illumination detector | Digital Pin `D3` |
| **SSD1306 OLED (128×64)** | High-contrast real-time telemetry display | I2C (`D1` SCL / `D2` SDA) |
| **Relay Channel 1** | 5V DC Exhaust Cooling Fan | Pin `D5` (Active-LOW) |
| **Relay Channel 2** | 5V Submersible Water Pump | Pin `D6` (Active-LOW) |
| **Relay Channel 3** | 5V UV Grow Lamp | Pin `D7` (Active-LOW) |

---

## 📂 Source Code
- ESP8266 Firmware: [`firmware/main.ino`](./firmware/main.ino)
- Portfolio Feed: [`project.json`](./project.json)
