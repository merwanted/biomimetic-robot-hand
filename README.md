<p align="center">
  <a href="README.md">🇬🇧 <b>English</b></a> | <a href="README.tr.md">🇹🇷 <b>Türkçe</b></a>
</p>

# 🖐️ Biomimetic Robotic Hand & Telemetry Glove

<div align="center">

[![Field](https://img.shields.io/badge/Field-Biomedical%20%26%20Robotics-blue?style=for-the-badge&labelColor=1a1a1a)](https://github.com/merwanted/biomimetic-robot-hand)
[![Hardware](https://img.shields.io/badge/Platform-Arduino%20Uno%20%2F%20C%2B%2B-00979D?style=for-the-badge&logo=arduino&logoColor=white&labelColor=1a1a1a)](https://github.com/merwanted/biomimetic-robot-hand)
[![Event](https://img.shields.io/badge/Organization-T%C3%9CB%C4%B0TAK%20Robotics%20Project-red?style=for-the-badge&labelColor=1a1a1a)](https://github.com/merwanted/biomimetic-robot-hand)
[![Status](https://img.shields.io/badge/Status-Hardware%20Exhibition%20Prototype-success?style=for-the-badge&labelColor=1a1a1a)](https://github.com/merwanted/biomimetic-robot-hand)

<p align="center">
  <b>Embedded Hardware & Firmware Prototype Developed for the TÜBİTAK Robotics Exhibition</b><br/>
  <i>A low-latency tele-manipulation system tracking human finger articulation via a sensorized glove to actuate a 5-digit tendon-driven robotic hand.</i>
</p>

</div>

---

> ⚠️ **Project Status:** This repository contains a **functional hardware prototype (Presentation & Research Prototype)** engineered for the **TÜBİTAK Robotics Exhibition**. It serves as an applied engineering proof of concept in tele-robotics and biomimetic prosthetics rather than a commercial medical device.

---

## 📌 Project Overview & Biomedical Motivation

### Objective
Capture natural human hand articulation with low latency (<100ms) and mirror kinematic finger movements onto a remotely controlled biomimetic robotic effector.

### Application Domains:
1. **Prosthetics & Rehabilitation:** Assistive mechanical terminal devices controlled via natural biomechanical inputs for individuals with upper-limb absence.
2. **Hazardous Material Handling:** Enabling operators to conduct fine manipulation tasks from a safe perimeter in radioactive, toxic, or explosive environments.
3. **Tele-Operation & Search and Rescue:** Remote object acquisition for exploration and disaster response rovers.

---

## 🏗️ Mechanical & Biomimetic Kinematics

The robotic hand replicates human musculoskeletal biomechanics:

```
[Human Hand / Glove] ──► [Flex Sensors] ──► [Voltage Divider Circuit]
                                                       │
                                                       ▼
[Robotic Digits] ◄── [Tendon Lines] ◄── [Servos] ◄── [Arduino EMA Filter]
```

* **Flexion (Curling):** As the operator flexes a finger, sensor electrical resistance rises. The microcontroller registers the analog voltage delta and drives the corresponding servo horn to tension the tendon wire routed through anatomical finger joints.
* **Extension (Releasing):** When the operator straightens their fingers, the servo rotates in reverse, allowing dorsal elastic bands/springs to return each finger to its neutral upright stance.

---

## ⚙️ Signal Processing & Anti-Jitter Filtering (EMA Filter)

Analog flex sensors are vulnerable to electromagnetic noise, wiring flexure, and contact jitter. Unfiltered analog signals lead to servo chatter and motor overheating.

An onboard **Exponential Moving Average (EMA)** algorithm filters voltage transients in real-time:

$$\text{Value}_{\text{current}} = (\alpha \times \text{Raw}) + ((1 - \alpha) \times \text{Value}_{\text{previous}})$$

An alpha factor of $\alpha = 0.25$ provides an optimal compromise between low latency response and smooth servo dampening.

---

## 📂 Repository Structure

```
biomimetic-robot-hand/
├── src/
│   ├── robot_hand.ino       # 5-finger real-time servo control & EMA filtering firmware
│   └── calibration.ino     # Interactive min/max calibration utility for individual hand sizes
├── hardware/
│   └── circuit_schematic.md # Pinout mappings, voltage divider reference, and common GND guide
├── README.md                # English Documentation (Default)
└── README.tr.md             # Turkish Documentation
```

---

## 🚀 Setup & Execution Guide

1. Assemble wiring according to the schematic in [`hardware/circuit_schematic.md`](hardware/circuit_schematic.md).
2. Flash `src/calibration.ino` onto the Arduino Uno to read your hand's minimum (flat) and maximum (bent) ADC values via the Serial Monitor.
3. Update the calibration arrays in `src/robot_hand.ino` with your measured thresholds, then upload the primary control firmware.

---

## 👨💻 Developer & Attribution
* **Developer:** Mert Özemir (Merwanted)
* **Scope:** TÜBİTAK Supported Robotics Project / Exhibition Prototype
