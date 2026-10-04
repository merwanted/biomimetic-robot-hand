/*
 * ============================================================================
 * PROJE: Biyomimetik Robot El - Kalibrasyon Aracı
 * YARIŞMA / SERGİ: TÜBİTAK Robotik Prototipi
 * ============================================================================
 * Kullanım:
 * 1. Kodu Arduino'ya yükleyin ve Seri Monitörü (9600 baud) açın.
 * 2. 5 saniye boyunca elinizi tamamen AÇIK tutun.
 * 3. Sonraki 5 saniye boyunca elinizi tamamen YUMRUK yapıp sıkın.
 * 4. Konsolda beliren min/max değerlerini robot_hand.ino içine kopyalayın.
 */

const int NUM_FINGERS = 5;
const int FLEX_PINS[NUM_FINGERS] = {A0, A1, A2, A3, A4};
int minVal[NUM_FINGERS];
int maxVal[NUM_FINGERS];

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println(F("=== KALİBRASYON MODU BAŞLADI ==="));

  for (int i = 0; i < NUM_FINGERS; i++) {
    minVal[i] = 1023;
    maxVal[i] = 0;
  }

  Serial.println(F("1. Aşama: Elinizi 5 saniye boyunca tamamen AÇIK tutun..."));
  unsigned long start = millis();
  while (millis() - start < 5000) {
    for (int i = 0; i < NUM_FINGERS; i++) {
      int val = analogRead(FLEX_PINS[i]);
      if (val < minVal[i]) minVal[i] = val;
    }
    delay(20);
  }

  Serial.println(F("2. Aşama: Şimdi elinizi 5 saniye boyunca YUMRUK yapıp bükün..."));
  start = millis();
  while (millis() - start < 5000) {
    for (int i = 0; i < NUM_FINGERS; i++) {
      int val = analogRead(FLEX_PINS[i]);
      if (val > maxVal[i]) maxVal[i] = val;
    }
    delay(20);
  }

  Serial.println(F("\n=== KALİBRASYON TAMAMLANDI ==="));
  Serial.println(F("Aşağıdaki satırları robot_hand.ino içine yapıştırın:\n"));

  Serial.print(F("int flexMin[5] = {"));
  for (int i = 0; i < NUM_FINGERS; i++) {
    Serial.print(minVal[i]);
    if (i < NUM_FINGERS - 1) Serial.print(F(", "));
  }
  Serial.println(F("};"));

  Serial.print(F("int flexMax[5] = {"));
  for (int i = 0; i < NUM_FINGERS; i++) {
    Serial.print(maxVal[i]);
    if (i < NUM_FINGERS - 1) Serial.print(F(", "));
  }
  Serial.println(F("};"));
}

void loop() {
  // Bitti, boş döngü
}
