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
- **Real-Time Visual Feedback:** 16×2 I2C LCD provides immediate diagnostic telemetry (Temp, Humidity, Soil %, Active Relays).
- **Manual Override Controls:** Physical push-button interface for emergency manual fan and pump triggers.

---

## 🛠️ Hardware Specification
| Component | Function | Interface / Pin |
| :--- | :--- | :--- |
| **NodeMCU ESP8266** | Central compute & control logic | Core Microcontroller |
| **DHT22** | Ambient temperature & relative humidity | GPIO (Digital Input with 10kΩ pull-up) |
| **Soil Moisture Sensor** | Substrate volumetric water content | Analog Pin `A0` (0–1023 ADC) |
| **4-Channel Relay (5V)** | Isolated AC/DC power switching | Active-LOW GPIO triggers |
| **16×2 LCD with I2C** | Real-time telemetry dashboard | `D1` (SCL) / `D2` (SDA) |
| **5V Water Pump** | Precision soil irrigation | Relay Channel 1 |
| **5V Cooling Fan** | Thermal dissipation & airflow | Relay Channel 2 |
| **5V UV Grow Light** | Plant photosynthesis support | Relay Channel 3 |

---

## 📂 Source Code
- ESP8266 Firmware: [`src/SmartGreenhouse_ESP8266.ino`](./src/SmartGreenhouse_ESP8266.ino)
- Portfolio Feed: [`project.json`](./project.json)
