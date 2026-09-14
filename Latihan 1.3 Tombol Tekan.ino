#include <Arduino.h>

const int LED_MERAH = 4;
const int LED_HIJAU = 5;
const int TOMBOL    = 15;

const unsigned long PERIODE_MERAH = 300;
const unsigned long PERIODE_HIJAU = 700;

unsigned long tMerah = 0;
unsigned long tHijau = 0;
bool nyalaMerah = false;
bool nyalaHijau = false;

// Untuk tombol (debounce)
bool tombolSebelumnya = HIGH;
unsigned long tTombolTerakhir = 0;
const unsigned long DEBOUNCE = 50;

void setup() {
  Serial.begin(115200);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(TOMBOL, INPUT_PULLUP);
}

void loop() {
  unsigned long sekarang = millis();

  // Tugas 1: LED Merah (300 ms)
  if (sekarang - tMerah >= PERIODE_MERAH) {
    tMerah = sekarang;
    nyalaMerah = !nyalaMerah;
    digitalWrite(LED_MERAH, nyalaMerah);
  }

  // Tugas 2: LED Hijau (700 ms)
  if (sekarang - tHijau >= PERIODE_HIJAU) {
    tHijau = sekarang;
    nyalaHijau = !nyalaHijau;
    digitalWrite(LED_HIJAU, nyalaHijau);
  }

  // Tugas 3: Tombol — kirim SATU BARIS saat tombol BARU ditekan
  bool tombolSekarang = digitalRead(TOMBOL);
  if (tombolSekarang == LOW && tombolSebelumnya == HIGH && (sekarang - tTombolTerakhir > DEBOUNCE)) {
    Serial.println("Tombol ditekan!");
    tTombolTerakhir = sekarang;
  }
  tombolSebelumnya = tombolSekarang;
}