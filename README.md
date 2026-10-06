# 🎓 Capstone Projects Hub

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Author](https://img.shields.io/badge/Author-Abdelrahman%20Mohamed-orange.svg)](https://github.com/3B00D-0)
[![Institution](https://img.shields.io/badge/Institution-Minia%20University-green.svg)](https://www.minia.edu.eg/)
[![Field](https://img.shields.io/badge/Focus-STEM%20Education%20%7C%20Robotics%20%7C%20IoT-purple.svg)](#)

> A centralized, production-grade monorepo containing undergraduate and research capstone projects by **Abdelrahman Mohamed (Abdo)** at the intersection of **STEM Education, Robotics, IoT Systems, Applied Mathematics, and Machine Learning**.

---

## 🧭 Executive Project Index

| # | Project | Category | Tech Stack | Status | Link |
| :-: | :--- | :--- | :--- | :-: | :--- |
| **01** | **[Smart Nursing Robot](./projects/01-smart-nursing-robot/)** | Healthcare Robotics | Arduino C++, PID, QTR-8A, Touch Sensor | Completed | [Explore →](./projects/01-smart-nursing-robot/) |
| **02** | **[HazardBot Rover](./projects/02-hazardbot/)** | Hazardous Reconnaissance | ESP32-WROOM-32, WiFi/BLE, MQ-2, MQ-135, PWA | Completed | [Explore →](./projects/02-hazardbot/) |
| **03** | **[Smart Greenhouse](./projects/03-smart-greenhouse-esp8266/)** | IoT & Climate Control | ESP8266 NodeMCU, Soil Moisture, DHT22, Relays, LCD | Completed | [Explore →](./projects/03-smart-greenhouse-esp8266/) |
| **04** | **[Smart Sign Language Glove](./projects/04-smart-sign-language-glove/)** | Assistive Tech & ML | ESP32, Flex Sensors, MPU6050, Random Forest, React | Active | [Explore →](./projects/04-smart-sign-language-glove/) |

---

## 🏛️ Monorepo Architecture

Every capstone inside this monorepo is completely self-contained while conforming to a unified specification:

```text
capstone-projects/
├── README.md                              # Master Capstone Portfolio Dashboard
├── .gitignore                             # Universal multi-language clean ignore
├── shared/                                # Reusable utilities, templates, styles
└── projects/
    ├── 01-smart-nursing-robot/            # Autonomous Hospital Delivery Vehicle
    │   ├── README.md                      # Engineering documentation & schematics
    │   ├── project.json                   # Structured metadata for Mega Portfolio API
    │   └── src/                           # Arduino C++ firmware
    ├── 02-hazardbot/                      # Hazardous Exploration Rover + PWA
    │   ├── README.md                      # Full EDP documentation & specs
    │   ├── project.json                   # Structured metadata
    │   ├── firmware/                      # Flight code & calibration sketches
    │   └── app/                           # Progressive Web App (PWA) interface
    ├── 03-smart-greenhouse-esp8266/       # Automated IoT Microclimate Care System
    │   ├── README.md                      # Hardware architecture & wiring specs
    │   ├── project.json                   # Structured metadata
    │   └── src/                           # ESP8266 firmware
    ├── 04-smart-sign-language-glove/      # Real-Time Sign Translation Wearable
    │   ├── README.md                      # ML pipeline & sensor layout
    │   ├── project.json                   # Structured metadata
    │   ├── firmware/                      # ESP32 sensor capture
    │   ├── backend/                       # Python AI & WebSocket bridge
    │   └── frontend/                      # React visualization web app
    └── _template/                         # Starter template for new capstones
        ├── README.md
        ├── project.json
        └── src/
```

### ⚡ Mega Portfolio Integration Ready
Each project directory carries a standardized **`project.json`** manifest. This enables external websites, web portfolios, or CMS feeds to programmatically ingest project details, tech stacks, live links, and demo assets directly via the GitHub API without manual updates.

---

## 🚀 Adding a New Capstone

To initialize a new project in this monorepo:
1. Duplicate `projects/_template` into `projects/<new-project-slug>`.
2. Update `project.json` with your title, category, and tech stack tags.
3. Write your implementation inside `src/` (or `firmware/` / `software/`).
4. Add an entry to the index table in this `README.md`.

---

## 👤 Author
**Abdelrahman Mohamed (Abdo)**  
STEM Educator & Aspiring Systems/Software Engineer  
- GitHub: [@3B00D-0](https://github.com/3B00D-0)  
- Email: [abdosayed.msm@gmail.com](mailto:abdosayed.msm@gmail.com)
