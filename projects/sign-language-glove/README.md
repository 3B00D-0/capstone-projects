# 🧤 Smart Sign Language Glove

> **Real-Time Gesture Recognition & Sign Translation via ESP32, Flex Sensors, Random Forest ML & React**  
> *Assistive Wearable Technology Project · Minia University*

---

## 📌 Project Overview
The **Smart Sign Language Glove** is an assistive communication system engineered to bridge the communication divide between the Deaf/Hard-of-Hearing community and the non-signing public. 

It tracks hand gestures in real time using 5 finger flex sensors and a 6-axis inertial measurement unit (IMU), transmits kinematic telemetry to a Python machine learning engine for Random Forest classification, and broadcasts recognized letters/words to an interactive React dashboard via WebSockets.

---

## 🏛️ System Architecture
```
┌────────────────────────┐      Serial / BLE      ┌─────────────────────────┐     WebSockets     ┌────────────────────────┐
│  Hardware Glove        │ ─────────────────────> │  Python AI Backend      │ ─────────────────> │  React Web Dashboard   │
│  - ESP32 Microcontroller│                       │  - Data Collector       │                    │  - Real-time Visualizer│
│  - 5× Flex Sensors     │                        │  - Random Forest Model  │                    │  - Letter Translation  │
│  - MPU6050 6-DOF IMU   │                        │  - WebSocket Server     │                    │  - Historical Log      │
└────────────────────────┘                        └─────────────────────────┘                    └────────────────────────┘
```

---

## 🛠️ Hardware Specification
| Joint / Finger | Sensor | ESP32 GPIO | Circuit |
| :--- | :--- | :--- | :--- |
| **Thumb** | Flex Sensor | `GPIO 32` | 10kΩ Voltage Divider |
| **Index** | Flex Sensor | `GPIO 35` | 10kΩ Voltage Divider |
| **Middle** | Flex Sensor | `GPIO 34` | 10kΩ Voltage Divider |
| **Ring** | Flex Sensor | `GPIO 39` (VN) | 10kΩ Voltage Divider |
| **Pinky** | Flex Sensor | `GPIO 36` (VP) | 10kΩ Voltage Divider |
| **Wrist Orientation** | MPU6050 6-DOF IMU | `I2C (SDA/SCL)` | Accelerometer + Gyroscope |

---

## 📂 Project Structure
- `firmware/`: ESP32 C++ firmware reading analog flex values and IMU quaternions.
- `backend/`: Python data collection, Random Forest model training, and WebSocket bridge.
- `frontend/`: React dashboard visualizing hand kinematic positions and live translations.
- [`project.json`](./project.json): Portfolio metadata feed.
