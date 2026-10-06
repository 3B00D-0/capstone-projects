# 💧 Automated Electrocoagulation Water Purification System

> **Microcontroller-Regulated Water Treatment via Periodic Polarity Reversal**  
> *STEM Education & Environmental Engineering · Minia University*

---

## 📌 Project Overview
The **Automated Electrocoagulation Water Purification System** is an engineering capstone exploring scalable wastewater and greywater treatment. Electrocoagulation (EC) destabilizes suspended colloidal particles and heavy metal pollutants through electrolytic oxidation without requiring toxic chemical coagulants.

This project implements an automated microcontroller control loop that solves a core chemical engineering obstacle: **electrode passivation**. By alternating DC current polarity across sacrificial electrodes every 20 seconds, the system prevents insulating oxide film buildup, running a 20-minute purification cycle before engaging secondary activated-charcoal filtration.

---

## ⚙️ Technical Working Principle
1. **Electrolytic Coagulation Phase (20 Minutes):**
   - Metal ions ($Al^{3+}$ or $Fe^{2+}$) are electrolytically generated from sacrificial plates.
   - Polarity reverses automatically every 20,000 ms to clean electrode surfaces uniformly.
2. **Settling & Transfer Phase:**
   - Suspended floccules agglomerate and precipitate.
3. **Pumping & Multi-Stage Filtration:**
   - An electric pump transports clarified effluent through sand and activated carbon filtration beds.

---

## 🛠️ Hardware Specification
| Component | Function | Configuration |
| :--- | :--- | :--- |
| **Microcontroller** | System timing & polarity cycling | Arduino Uno |
| **H-Bridge Driver** | Adafruit Motor Shield | Reverses DC electrode current polarity |
| **Electrode Array** | Sacrificial plates (Aluminum / Iron) | Channel 1 (64 kHz PWM full drive) |
| **Filtration Pump** | Peristaltic / DC Submersible transfer pump | Channel 2 (2 kHz PWM) |

---

## 📂 Project Structure
- `firmware/`:
  - [`main.ino`](./firmware/main.ino): Arduino control loop with timed polarity alternation.
- `docs/`:
  - [`research-paper.pdf`](./docs/research-paper.pdf): Project research whitepaper and laboratory findings.
  - `media/`:
    - `electrocoagulation-process-diagram.jpg`: Chemical coagulation schematic.
    - `water-filtration-stage.png`: Physical filtration bed layout.
    - `charcoal-filter-spec.webp`: Activated charcoal media specification.
    - `peristaltic-pump-subsystem.jpg`: Fluid pump hardware.
- [`project.json`](./project.json): Portfolio metadata feed.
