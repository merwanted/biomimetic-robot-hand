# 🖐️ Biyomimetik Robot El & Telemetri Eldiveni

<div align="center">

[![Field](https://img.shields.io/badge/Alan-Biyomedikal%20%26%20Robotik-blue?style=for-the-badge&labelColor=1a1a1a)](https://github.com/merwanted/biomimetic-robot-hand)
[![Hardware](https://img.shields.io/badge/Platform-Arduino%20Uno%20%2F%20C%2B%2B-00979D?style=for-the-badge&logo=arduino&logoColor=white&labelColor=1a1a1a)](https://github.com/merwanted/biomimetic-robot-hand)
[![Event](https://img.shields.io/badge/Organizasyon-T%C3%9CB%C4%B0TAK%20Robotik%20Projesi-red?style=for-the-badge&labelColor=1a1a1a)](https://github.com/merwanted/biomimetic-robot-hand)
[![Status](https://img.shields.io/badge/Durum-Donan%C4%B1m%20Sergi%20Prototipi-success?style=for-the-badge&labelColor=1a1a1a)](https://github.com/merwanted/biomimetic-robot-hand)

<p align="center">
  <b>TÜBİTAK Robotik Projeleri Kapsamında Geliştirilmiş Donanım & Gömülü Yazılım Prototipi</b><br/>
  <i>Kullanıcının el hareketlerini flex sensörlü eldivenle algılayıp tendon mekanizmalı 5 parmaklı robotik ele aktaran tele-manipülasyon sistemi.</i>
</p>

</div>

---

> ⚠️ **Proje Durumu:** Bu depo, **TÜBİTAK Robotik Projeleri / Bilim Sergisi** kapsamında tasarlanmış ve sunulmuş **çalışan bir donanım prototipidir (Presentation & Research Prototype)**. Ticari son kullanıcı ürünü değil, tele-robotik ve biyomedikal protez prensiplerini kanıtlayan bir mühendislik çalışmasıdır.

---

## 📌 Proje Özeti & Biyomedikal Motivasyon

### Amaç
İnsan elinin doğal hareketlerini düşük gecikmeyle (<100ms) algılayarak uzaktan kontrol edilen biyomimetik bir robotik ele aktarmak.

### Uygulama Alanları:
1. **Protez & Biyomedikal Teknolojisi:** Uzuv kaybı yaşayan bireyler için doğal motor komutlarıyla kontrol edilebilen mekanik el protezleri.
2. **Tehlikeli Madde Yönetimi:** Radyoaktif, kimyasal veya patlayıcı ortamlarda operatörün güvenli mesafeden hassas manipülasyon yapabilmesi.
3. **Tele-Operasyon:** Arama-kurtarma robotlarında uzaktan el hareketleriyle nesne kavrama.

---

## 🏗️ Mekanik ve Biyomimetik Çalışma Mantığı

Robot el, insan elinin anatomik çalışma prensibini taklit eder:

```
[İnsan Eli / Eldiven] ──► [Flex Sensörler] ──► [Voltaj Bölücü Devre]
                                                         │
                                                         ▼
[Robotik Parmaklar] ◄── [Tendon İpleri] ◄── [Servolar] ◄── [Arduino EMA Filtresi]
```

* **Fleksiyon (Bükülme):** Kullanıcı parmağını büktüğünde flex sensörün direnci artar. Arduino bu değişimi algılar ve ilgili servo motoru döndürerek parmak eklemlerine bağlı tendon ipini çeker.
* **Ekstansiyon (Geri Açılma):** Kullanıcı elini açtığında servo motor ters yöne döner ve parmak sırtındaki yay/elastik bantlar parmağı orijinal dik pozisyonuna geri çeker.

---

## ⚙️ Sinyal İşleme & Titreme Engelleme (EMA Filtresi)

Analog flex sensörler ortam gürültüsünden ve kablo hareketlerinden dolayı gürültülü (jittery) sinyal üretebilir. Bu durum servoların sürekli titremesine ve aşırı ısınmasına yol açar.

Yazılımda uygulanan **Exponential Moving Average (EMA)** filtreleme algoritması ile ani voltaj sıçramaları süzülür:

$$\text{Değer}_{\text{yeni}} = (\alpha \times \text{Ham}) + ((1 - \alpha) \times \text{Değer}_{\text{önceki}})$$

Burada $\alpha = 0.25$ seçilerek tepki süresi ile sinyal pürüzsüzlüğü arasında ideal denge sağlanmıştır.

---

## 📂 Depo Yapısı

```
biomimetic-robot-hand/
├── src/
│   ├── robot_hand.ino       # 5 parmak gerçek zamanlı kontrol & EMA filtreleme firmware'i
│   └── calibration.ino     # Kişiye özel el boyutu için otomatik kalibrasyon aracı
├── hardware/
│   └── circuit_schematic.md # Pin bağlantıları, voltaj bölücü ve ortak GND rehberi
└── README.md
```

---

## 🚀 Kurulum & Çalıştırma

1. Devre bağlantılarını [`hardware/circuit_schematic.md`](hardware/circuit_schematic.md) dosyasındaki şemaya göre yapın.
2. `src/calibration.ino` dosyasını Arduino Uno'ya yükleyerek Seri Monitör üzerinden kendi elinizin min/max bükülme değerlerini tespit edin.
3. Elde ettiğiniz değerleri `src/robot_hand.ino` dosyasındaki kalibrasyon dizisine yapıştırın ve ana firmware'i yükleyin.

---

## 👨💻 Geliştirici & Proje Bilgisi
* **Geliştirici:** Mert Özemir (Merwanted)
* **Kapsam:** TÜBİTAK Destekli Robotik Projeleri / Sergi Prototipi
