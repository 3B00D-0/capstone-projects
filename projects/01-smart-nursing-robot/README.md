# 🤖 Smart Nursing Robot

> **Autonomous Hospital Delivery Vehicle with Line Following & PID Control**  
> *Developed by Team VERTEX — Minia University, Faculty of Education (STEM Education & Engineering)*

---

## 📌 Project Overview
The **Smart Nursing Robot** is an autonomous guided vehicle designed to assist hospital staff by safely transporting pharmaceuticals and light medical supplies from central dispensaries directly to patient bedsides.

It utilizes an infrared reflectance sensor array paired with a **PID (Proportional-Derivative) controller** to achieve jitter-free trajectory tracking along pre-mapped hospital corridors.

---

## ✨ Key Features
- **Autonomous Path Traversal:** 5-channel QTR-8A IR sensor array calculates line position with high-frequency feedback loops.
- **PID Control Loop:** Proportional-Derivative regulation guarantees smooth cornering without overshooting or oscillation.
- **Secure Medicine Delivery Bay:** Servo-actuated medicine compartment with capacitive touch activation (`TTP223`).
- **Patient Arrival Alert System:** Automatic audio buzzer triggers upon reaching the target stop marker, auto-silencing when the patient touches the sensor and retrieves their medicine.
- **Fail-Safe Arrival Detection:** Confirms destination arrival across all sensors before entering hold state.

---

## 🛠️ Hardware Architecture
| Component | Specification | Function |
| :--- | :--- | :--- |
| **Microcontroller** | Arduino Uno (ATmega328P) | Core execution and control logic |
| **Motor Driver** | Adafruit Motor Shield v1 | Dual DC motor control with PWM speed regulation |
| **Path Sensors** | Pololu QTR-8A (5 channels active) | Ground reflectance line tracking |
| **Touch Interface** | TTP223 Capacitive Touch Sensor | Contact-free bay open/close trigger |
| **Actuators** | 2x DC Geared Motors + 1x Micro Servo | Locomotion & medicine bay lid actuation |
| **Power Supply** | 2x 18650 Li-Ion Cells in series (~7.4V) | Independent motor and logic power |

---

## 📂 Source Code
- Arduino Sketch: [`firmware/main.ino`](./firmware/main.ino)
- Portfolio Metadata: [`project.json`](./project.json)
