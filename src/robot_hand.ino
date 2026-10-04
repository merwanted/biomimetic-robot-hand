/*
 * ============================================================================
 * PROJE: Biyomimetik Robot El & Telemetri Eldiveni Kontrol Yazılımı
 * YARIŞMA / SERGİ: TÜBİTAK Robotik ve Biyomedikal Proje Prototipi
 * GELİŞTİRİCİ: Mert Özemir (Merwanted)
 * ============================================================================
 * AÇIKLAMA:
 * Kullanıcının eldiven üzerindeki 5 parmak flex (bükülme) sensörlerinden gelen
 * analog voltaj değişimlerini Exponential Moving Average (EMA) filtresi ile
 * pürüzsüzleştirir; 5 adet servo motorun tendon mekanizmasını gerçek zamanlı (<100ms)
 * olarak sürer.
 */

#include <Servo.h>

// Parmak Sayısı
const int NUM_FINGERS = 5;

// Analog Giriş Pinleri (Flex Sensörler - Voltaj Bölücü Devresi)
const int FLEX_PINS[NUM_FINGERS] = {A0, A1, A2, A3, A4};
// 0: Başparmak, 1: İşaret, 2: Orta, 3: Yüzük, 4: Serçeparmak

// Dijital PWM Çıkış Pinleri (Servo Motorlar)
const int SERVO_PINS[NUM_FINGERS] = {3, 5, 6, 9, 10};

// Servo Nesneleri
Servo servos[NUM_FINGERS];

// Kalibrasyon Değerleri (Açık El - Düz vs. Kapalı El - Bükülü)
// Not: Her kullanıcının el yapısına göre calibration.ino ile güncellenebilir.
int flexMin[NUM_FINGERS] = {400, 420, 390, 410, 380}; // Tamamen açık
int flexMax[NUM_FINGERS] = {750, 780, 760, 770, 730}; // Tamamen bükülü

// Servo Açı Sınırları (Tendon gerilimini korumak için 0-180 arası güvenli bölge)
const int SERVO_MIN_ANGLE = 10;   // Parmak serbest / açık
const int SERVO_MAX_ANGLE = 165;  // Parmak çekili / yumruk

// Sensör Pürüzsüzleştirme (EMA Filtresi Katsayısı - Titremeyi önler)
float smoothedValues[NUM_FINGERS] = {0};
const float ALPHA = 0.25; // 0.0 - 1.0 arası yumuşatma faktörü

void setup() {
  Serial.begin(9600);
  Serial.println(F("==========================================="));
  Serial.println(F("🤖 TÜBİTAK Biyomimetik Robot El Başlatılıyor"));
  Serial.println(F("==========================================="));

  // Servoları pinlere bağla ve başlangıç (açık el) pozisyonuna getir
  for (int i = 0; i < NUM_FINGERS; i++) {
    servos[i].attach(SERVO_PINS[i]);
    servos[i].write(SERVO_MIN_ANGLE);
    smoothedValues[i] = analogRead(FLEX_PINS[i]);
  }

  delay(500);
  Serial.println(F("Sistem hazır. Gerçek zamanlı telemetri aktif."));
}

void loop() {
  for (int i = 0; i < NUM_FINGERS; i++) {
    // 1. Ham analog veriyi oku (0-1023)
    int rawValue = analogRead(FLEX_PINS[i]);

    // 2. EMA Filtresi: Ani voltaj dalgalanmalarını ve servo titremesini süz
    smoothedValues[i] = (ALPHA * rawValue) + ((1.0 - ALPHA) * smoothedValues[i]);

    // 3. Değeri kalibrasyon aralığına sınırla
    int clampedValue = constrain((int)smoothedValues[i], flexMin[i], flexMax[i]);

    // 4. Bükülme değerini servo motorun açı değerine (0-180°) haritala
    int targetAngle = map(clampedValue, flexMin[i], flexMax[i], SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);

    // 5. Tendon motorunu hareket ettir
    servos[i].write(targetAngle);
  }

  // Telemetri / Hata Ayıklama çıktısı (Her 50ms'de bir)
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 50) {
    lastPrint = millis();
    Serial.print(F("THUMB: "));  Serial.print(servos[0].read()); Serial.print(F("° | "));
    Serial.print(F("INDEX: "));  Serial.print(servos[1].read()); Serial.print(F("° | "));
    Serial.print(F("MIDDLE: ")); Serial.print(servos[2].read()); Serial.print(F("° | "));
    Serial.print(F("RING: "));   Serial.print(servos[3].read()); Serial.print(F("° | "));
    Serial.print(F("PINKY: "));  Serial.print(servos[4].read()); Serial.println(F("°"));
  }

  delay(15); // ~60Hz servo güncelleme döngüsü
}
