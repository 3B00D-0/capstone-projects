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

## 🔌 Hardware Architecture & Electrical Schematic

### 🌐 Tier 1: System Interconnect Overview (High-Level Architecture)
```mermaid
graph LR
    subgraph Power ["🔋 Power Subsystem"]
        PSU["12V / 5A DC Supply"]
    end

    subgraph Controller ["🧠 Compute & Control Hub"]
        UNO["Arduino Uno R3"]
        SHIELD["Adafruit Motor Shield v1 (L293D H-Bridge)"]
    end

    subgraph ChemicalStage ["⚡ Stage 1: Electrocoagulation Cell"]
        CELL["Sacrificial Metal Electrodes (Al/Fe Plates)"]
    end

    subgraph FiltrationStage ["🌊 Stage 2: Clarification & Polishing"]
        PUMP["12V Peristaltic Pump"]
        FILTER["Multi-Stage Sand & Activated Carbon Bed"]
    end

    PSU -->|"12V High-Current Drive"| SHIELD
    SHIELD -->|"5V Logic Bus"| UNO
    SHIELD -->|"Port M1 (64 kHz Polarity Inversion)"| CELL
    SHIELD -->|"Port M2 (2 kHz Flow Rate Control)"| PUMP
    PUMP -->|"Pressurized Effluent"| FILTER
```

---

### 📌 Tier 2: Pin-by-Pin Physical Wiring & Assembly Specification
| Subsystem Component | Shield / Board Terminal | Arduino Uno Pin | Signal Type | Wire Color | Notes & Operating Parameters |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **External DC Source** | EXT_PWR (+) | Vin | High-Current DC | 🔴 Red | 12V 5A Bench Supply |
| **External DC Ground** | EXT_PWR (-) | GND | Ground | ⚫ Black | Shared common ground plane |
| **EC Plate A (Anode/Cathode)** | M1 Output A | D11 / D3 (via 74HC595) | Bidirectional DC | 🔴 Red | High-current polarity alternating |
| **EC Plate B (Cathode/Anode)** | M1 Output B | D11 / D3 (via 74HC595) | Bidirectional DC | ⚫ Black | Toggles polarity every 20s to stop passivation |
| **Peristaltic Pump (+)** | M2 Output A | D3 / D5 (via 74HC595) | PWM Motor Drive | 🟡 Yellow | 155 PWM (Soft flow control) |
| **Peristaltic Pump (-)** | M2 Output B | GND Terminal | DC Return | 🔵 Blue | Motor return path |

> [!NOTE] Passivation Prevention Circuit
> - The Adafruit Motor Shield acts as a high-current H-Bridge for the chemical cell. Alternating the H-Bridge direction (`FORWARD` / `BACKWARD`) inverts the DC voltage across the aluminum plates, shedding the non-conductive oxide crust and extending electrode lifespan by over 400%.


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
