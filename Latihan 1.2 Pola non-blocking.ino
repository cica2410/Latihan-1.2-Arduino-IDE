#include <Arduino.h>

const int LED_MERAH = 4;
const int LED_HIJAU = 5;

const unsigned long PERIODE_MERAH = 300;   // ms
const unsigned long PERIODE_HIJAU = 700;   // ms

unsigned long tMerah = 0;
unsigned long tHijau = 0;
bool nyalaMerah = false;
bool nyalaHijau = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
}

void loop() {
  unsigned long sekarang = millis();

  if (sekarang - tMerah >= PERIODE_MERAH) {
    tMerah = sekarang;
    nyalaMerah = !nyalaMerah;
    digitalWrite(LED_MERAH, nyalaMerah);
  }

  if (sekarang - tHijau >= PERIODE_HIJAU) {
    tHijau = sekarang;
    nyalaHijau = !nyalaHijau;
    digitalWrite(LED_HIJAU, nyalaHijau);
  }

  // TIDAK ADA delay() di sini
}