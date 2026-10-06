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

## 🔌 Visual Hardware Wiring & Signal Diagram

```mermaid
graph TD
    subgraph Power ["🔋 Power Distribution"]
        BAT["2× 18650 Li-Ion (7.4V)"] -->|EXT PWR| SHIELD["Adafruit Motor Shield v1"]
        SHIELD -->|5V Regulated| UNO["Arduino Uno MCU"]
        BAT -.->|Common GND| UNO
    end

    subgraph Actuators ["⚙️ Propulsion & Mechanism"]
        SHIELD -->|Channel M1 (1 kHz)| M1["Left Drive Motor"]
        SHIELD -->|Channel M2 (1 kHz)| M2["Right Drive Motor"]
        SHIELD -->|Channel M3| BUZZ["Alert Buzzer"]
        UNO -->|"SERVO_PIN (Pin 10)"| SERVO["Medicine Lid Servo (SG90)"]
    end

    subgraph Perception ["📡 Line Tracking & Human Interaction"]
        QTR["Pololu QTR-8A (5 Sensors)"] -->|"Pins A4, A3, A2, A1, A0"| UNO
        UNO -->|"EMITTER_PIN (Pin 2)"| QTR
        TOUCH["TTP223 Capacitive Touch"] -->|"SENSOR_PIN (Pin A5)"| UNO
    end
```

---

## 📋 Master Hardware Pinout Specification

| Subsystem | Component | Component Pin | Arduino Uno Pin | Signal Type | Description / Notes |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Locomotion** | Left DC Motor | Terminal M1 | Shield Port 1 | High-current PWM | Driven at 1 kHz frequency |
| **Locomotion** | Right DC Motor | Terminal M2 | Shield Port 2 | High-current PWM | Driven at 1 kHz frequency |
| **Alarm** | Piezo Buzzer | Terminal M3 | Shield Port 3 | Digital PWM | 500ms pulsed audible arrival alarm |
| **Medicine Lid**| Servo Motor | Signal (Orange) | **Pin 10** | Servo PWM | 90° closed, 180° open |
| **Touch Trigger**| TTP223 Sensor | OUT | **Pin A5** | Digital Input | Toggle trigger on touch (debounced) |
| **Line Tracking**| QTR Sensor 1 | OUT 1 | **Pin A0** | Analog / RC Read | Outer Right boundary sensor |
| **Line Tracking**| QTR Sensor 2 | OUT 2 | **Pin A1** | Analog / RC Read | Inner Right line tracker |
| **Line Tracking**| QTR Sensor 3 | OUT 3 | **Pin A2** | Analog / RC Read | Center alignment sensor |
| **Line Tracking**| QTR Sensor 4 | OUT 4 | **Pin A3** | Analog / RC Read | Inner Left line tracker |
| **Line Tracking**| QTR Sensor 5 | OUT 5 | **Pin A4** | Analog / RC Read | Outer Left boundary sensor |
| **Emitter Ctrl** | QTR IR LEDs | LEDON | **Pin 2** | Digital Output | Toggles IR emitter LEDs for calibration |

> [!NOTE] Power Supply Architecture
> - The Adafruit Motor Shield is powered via external 7.4V battery pack with the `PWR` jumper set to draw motor current directly from batteries, protecting the Arduino from inductive voltage spikes and brownouts.

---

## 📂 Source Code
- Arduino Sketch: [`firmware/main.ino`](./firmware/main.ino)
- Portfolio Metadata: [`project.json`](./project.json)
