#include <Arduino.h>

const int LED_MERAH = 4;
const int LED_HIJAU = 5;
const int TOMBOL    = 15;

enum Keadaan { SIAP, PANASKAN, TAHAN, DINGINKAN, JEDA };

void masuk(Keadaan k);
unsigned long lamaDiKeadaanIni();
bool tombolBaruDitekan();

Keadaan keadaan = SIAP;
unsigned long tMasuk = 0;
unsigned long lamaJalan = 0;
Keadaan keadaanSebelumJeda;

unsigned long tKedipHijau = 0;
unsigned long tKedipMerah = 0;

void masuk(Keadaan k) {
  keadaan = k;
  tMasuk = millis();
  
  Serial.print("masuk keadaan ");
  switch (k) {
    case SIAP: Serial.print("SIAP"); break;
    case PANASKAN: Serial.print("PANASKAN"); break;
    case TAHAN: Serial.print("TAHAN"); break;
    case DINGINKAN: Serial.print("DINGINKAN"); break;
    case JEDA: Serial.print("JEDA"); break;
  }
  Serial.print(" pada t = ");
  Serial.println(millis());
}

unsigned long lamaDiKeadaanIni() {
  return millis() - tMasuk;
}

bool tombolBaruDitekan() {
  static bool tombolSebelumnya = HIGH;
  static unsigned long tTombolTerakhir = 0;
  bool tombolSekarang = digitalRead(TOMBOL);
  
  if (tombolSekarang == LOW && tombolSebelumnya == HIGH && (millis() - tTombolTerakhir > 200)) {
    tTombolTerakhir = millis();
    tombolSebelumnya = tombolSekarang;
    return true;
  }
  
  if (tombolSekarang == HIGH) {
    tombolSebelumnya = HIGH;
  }
  
  return false;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(TOMBOL, INPUT_PULLUP);
  
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_HIJAU, LOW);
  
  masuk(SIAP);
}

void loop() {
  switch (keadaan) {
    
    case SIAP:
      digitalWrite(LED_MERAH, LOW);
      if (millis() - tKedipHijau >= 500) {
        tKedipHijau = millis();
        digitalWrite(LED_HIJAU, !digitalRead(LED_HIJAU));
      }
      
      if (tombolBaruDitekan()) {
        masuk(PANASKAN);
        
        // Tunggu sampai tombol dilepas
        while (digitalRead(TOMBOL) == LOW) {}
      }
      break;

    case PANASKAN:
      digitalWrite(LED_MERAH, HIGH);
      digitalWrite(LED_HIJAU, LOW);
      
      if (tombolBaruDitekan()) {
        lamaJalan = lamaDiKeadaanIni();
        keadaanSebelumJeda = PANASKAN;
        masuk(JEDA);
        while (digitalRead(TOMBOL) == LOW) {}
      }
      
      if (lamaDiKeadaanIni() >= 5000) {
        masuk(TAHAN);
      }
      break;

    case TAHAN:
      digitalWrite(LED_HIJAU, LOW);
      if (millis() - tKedipMerah >= 250) {
        tKedipMerah = millis();
        digitalWrite(LED_MERAH, !digitalRead(LED_MERAH));
      }
      
      if (tombolBaruDitekan()) {
        lamaJalan = lamaDiKeadaanIni();
        keadaanSebelumJeda = TAHAN;
        masuk(JEDA);
        while (digitalRead(TOMBOL) == LOW) {}
      }
      
      if (lamaDiKeadaanIni() >= 8000) {
        masuk(DINGINKAN);
      }
      break;

    case DINGINKAN:
      digitalWrite(LED_MERAH, LOW);
      digitalWrite(LED_HIJAU, HIGH);
      
      if (tombolBaruDitekan()) {
        lamaJalan = lamaDiKeadaanIni();
        keadaanSebelumJeda = DINGINKAN;
        masuk(JEDA);
        while (digitalRead(TOMBOL) == LOW) {}
      }
      
      if (lamaDiKeadaanIni() >= 4000) {
        masuk(SIAP);
      }
      break;

    case JEDA:
      digitalWrite(LED_MERAH, LOW);
      digitalWrite(LED_HIJAU, LOW);
      
      // Tunggu sampai tombol dilepas dulu sebelum menerima perintah lanjut
      if (digitalRead(TOMBOL) == HIGH) {
        if (tombolBaruDitekan()) {
          tMasuk = millis() - lamaJalan;
          keadaan = keadaanSebelumJeda;
          Serial.println("Melanjutkan proses...");
          while (digitalRead(TOMBOL) == LOW) {}
        }
      }
      break;
  }
}