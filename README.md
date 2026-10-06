# 🎓 Capstone Projects Hub

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Author](https://img.shields.io/badge/Author-Abdelrahman%20Mohamed-orange.svg)](https://github.com/3B00D-0)
[![Institution](https://img.shields.io/badge/Institution-Minia%20University-green.svg)](https://www.minia.edu.eg/)
[![Field](https://img.shields.io/badge/Focus-STEM%20Education%20%7C%20Robotics%20%7C%20IoT%20%7C%20Systems-purple.svg)](#)

> A centralized, production-grade monorepo containing undergraduate and research capstone projects by **Abdelrahman Mohamed (Abdo)** at the intersection of **STEM Education, Robotics, IoT Systems, Applied Mathematics, and Machine Learning**.

---

## 🧭 Featured Capstones (Latest First)

| Project | Date | Category | Key Tech Stack | Status | Documentation & Code |
| :--- | :-: | :--- | :--- | :-: | :--- |
| **[HazardBot Rover](./projects/hazardbot/)** | **May 2026** | Hazardous Reconnaissance | ESP32-WROOM-32, WiFi/BLE, MQ-2, MQ-135, PWA | Completed | [Explore Project →](./projects/hazardbot/) |
| **[Smart Greenhouse](./projects/smart-greenhouse/)** | **May 2026** | IoT & Precision Agriculture | ESP8266, SSD1306 OLED, Soil Sensor, Relays | Completed | [Explore Project →](./projects/smart-greenhouse/) |
| **[Smart Nursing Robot](./projects/smart-nursing-robot/)** | **Dec 2025** | Healthcare Robotics | Arduino C++, PID Control, QTR-8A, Touch Sensor | Completed | [Explore Project →](./projects/smart-nursing-robot/) |
| **[Smart Sign Language Glove](./projects/sign-language-glove/)** | **Dec 2025** | Assistive Tech & ML | ESP32, Flex Sensors, MPU6050, Random Forest, React | Active | [Explore Project →](./projects/sign-language-glove/) |
| **[Electrocoagulation Water Purifier](./projects/water-purifier-electrocoagulation/)** | **May 2025** | Environmental Engineering | Arduino C++, H-Bridge Polarity Inversion, Water EC | Completed | [Explore Project →](./projects/water-purifier-electrocoagulation/) |

---

## 🏛️ Monorepo Architecture & Standardized Naming

Every capstone inside this repository conforms to a strict, standardized anatomy:

```text
capstone-projects/
├── README.md                                    # Master Capstone Portfolio Dashboard
├── .gitignore                                   # Universal multi-language clean ignore
├── shared/                                      # Reusable utilities, templates, styles
└── projects/
    ├── hazardbot/                               # Hazardous Environment Exploration Rover
    │   ├── README.md                            # Comprehensive EDP whitepaper & photos
    │   ├── project.json                         # Structured metadata for Mega Portfolio API
    │   ├── firmware/
    │   │   ├── main.ino                         # Production firmware v3.1 (BLE, WiFi AP, sensors)
    │   │   └── sensor-calibration.ino           # Sensor warmup & baseline test sketch
    │   ├── app/                                 # Companion Progressive Web App (PWA)
    │   │   ├── index.html                       # Real-time telemetry dashboard & joystick
    │   │   └── manifest.json                    # Installable web app manifest
    │   └── docs/
    │       ├── booklet.pdf                      # Formal Engineering Project Booklet
    │       ├── booklet.md                       # Full technical question & answer documentation
    │       ├── poster.md                        # Exhibition poster presentation content
    │       └── media/                           # High-res hardware photos (front, chassis, wiring)
    │
    ├── smart-greenhouse/                        # Automated IoT Microclimate Care System
    │   ├── README.md                            # Circuit schematics & sensor thresholds
    │   ├── project.json                         # Structured metadata
    │   ├── firmware/main.ino                    # ESP8266 NodeMCU firmware (OLED + LDR + Relays)
    │   └── docs/media/                          # Wiring diagrams
    │
    ├── smart-nursing-robot/                     # Autonomous Hospital Delivery Vehicle
    │   ├── README.md                            # Technical documentation & hardware specs
    │   ├── project.json                         # Structured metadata
    │   ├── firmware/main.ino                    # Arduino C++ production flight firmware
    │   └── docs/media/                          # Schematics & hardware photographs
    │
    ├── sign-language-glove/                     # Real-Time Sign Translation Wearable
    │   ├── README.md                            # Kinematic layout & ML classification pipeline
    │   ├── project.json                         # Structured metadata
    │   ├── firmware/                            # ESP32 sensor capture
    │   ├── backend/                             # Python Random Forest & WebSocket server
    │   └── frontend/                            # React live visualizer app
    │
    └── water-purifier-electrocoagulation/       # Microcontroller Water Treatment System
        ├── README.md                            # Chemical engineering & electrolytic specs
        ├── project.json                         # Structured metadata
        ├── firmware/main.ino                    # Arduino polarity-inversion timed control loop
        └── docs/
            ├── research-paper.pdf               # Laboratory research findings & report
            └── media/                           # Coagulation schematics & filtration stages
```

### ⚡ Mega Portfolio Integration Ready
Each project directory carries a standardized **`project.json`** manifest. This enables external websites, web portfolios, or CMS feeds to programmatically ingest project details, tech stacks, live links, and demo assets directly via the GitHub API without manual updates.

---

## 🚀 Adding a New Capstone

To initialize a new project in this monorepo:
1. Duplicate `projects/_template` into `projects/<project-slug>`.
2. Update `project.json` with your title, category, and tech stack tags.
3. Place your code in `firmware/main.ino` (or `src/`).
4. Place PDFs, posters, and photos into `docs/` and `docs/media/`.
5. Add an entry to the table in this `README.md`.

---

## 👤 Author
**Abdelrahman Mohamed (Abdo)**  
STEM Educator & Aspiring Systems/Software Engineer  
- GitHub: [@3B00D-0](https://github.com/3B00D-0)  
- Email: [abdosayed.msm@gmail.com](mailto:abdosayed.msm@gmail.com)
