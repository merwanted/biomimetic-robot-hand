# 🔌 Donanım ve Devre Bağlantı Şeması

Bu döküman, **Biyomimetik Robot El & Telemetri Eldiveni** devresinin elektronik bağlantılarını açıklar.

---

## 📌 1. Bileşen Listesi

| Bileşen | Adet | Görev |
| :--- | :---: | :--- |
| **Arduino Uno R3** | 1 | Ana kontrol mikrodenetleyicisi |
| **Flex (Bükülme) Sensörü 2.2"** | 5 | Eldiven parmaklarının bükülme direncini ölçer |
| **Servo Motor (SG90 / MG996R)** | 5 | Parmak tendon mekanizmasını çeken aktüatörler |
| **10kΩ Direnç (1/4W)** | 5 | Voltaj bölücü (Voltage Divider) devresi için |
| **Harici 5V Güç Kaynağı (Adaptör/Regülatör)**| 1 | Servolar için harici güç hattı |
| **Breadboard & Jumper Kablolar** | - | Sinyal ve güç dağıtımı |

---

## ⚡ 2. Voltaj Bölücü (Voltage Divider) Devresi

Flex sensörler büküldükçe dirençleri artar (~10kΩ düz ➔ ~30kΩ-40kΩ bükülü). Arduino analog girişinden (ADC) bu değişimi voltaj olarak okumak için 10kΩ sabit dirençle voltaj bölücü kurulur:

```
          +5V (Arduino)
            │
            ▼
      ┌───────────┐
      │   FLEX    │  (Bükülme Sensörü)
      │  SENSÖR   │
      └─────┬─────┘
            │
            ├──────────────► Arduino Analog Pini (A0 - A4)
            │
      ┌─────┴─────┐
      │   10kΩ    │  (Sabit Direnç)
      │  DİRENÇ   │
      └─────┬─────┘
            │
            ▼
       GND (Arduino)
```

---

## 🖐️ 3. Pin Bağlantı Tablosu

### Flex Sensörler (Analog Girişler):
- **Başparmak:** A0 Pini
- **İşaret Parmağı:** A1 Pini
- **Orta Parmak:** A2 Pini
- **Yüzük Parmağı:** A3 Pini
- **Serçe Parmak:** A4 Pini

### Servo Motorlar (Dijital PWM Çıkışları):
- **Başparmak Servosu:** Dijital Pin 3 (PWM)
- **İşaret Parmağı Servosu:** Dijital Pin 5 (PWM)
- **Orta Parmak Servosu:** Dijital Pin 6 (PWM)
- **Yüzük Parmağı Servosu:** Dijital Pin 9 (PWM)
- **Serçe Parmak Servosu:** Dijital Pin 10 (PWM)

---

## ⚠️ Kritik Güç Kuralı (Ortak GND Prensibi)

* **Servolar Arduino'dan Beslenemez:** 5 adet servo aynı anda hareket ettiğinde 1.5A - 2.5A akım çeker. Arduino'nun 5V pini bu akımı veremez ve kart yeniden başlar (Brownout reset).
* **Çözüm:** Servolar harici bir 5V güç kaynağından beslenmeli; harici güç kaynağının **GND** hattı ile Arduino'nun **GND** hattı birbirine bağlanmalıdır (**Common Ground**).
