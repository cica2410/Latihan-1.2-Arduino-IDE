#include <Arduino.h>

unsigned long tLalu = 0;
unsigned long minPutaran = 4294967295UL;
unsigned long maxPutaran = 0;
unsigned long jumlah = 0;
unsigned long cacah = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  tLalu = micros();
}

void loop() {
  unsigned long sekarang = micros();
  unsigned long putaran = sekarang - tLalu;
  tLalu = sekarang;

  if (cacah > 0) {
    if (putaran < minPutaran) minPutaran = putaran;
    if (putaran > maxPutaran) maxPutaran = putaran;
    jumlah += putaran;
  }
  cacah++;

  delay(50);   // delay 50 ms

  if (cacah >= 100) {   // <--- Diubah dari 10000 ke 100
    Serial.print("min = ");
    Serial.print(minPutaran);
    Serial.print(" us | max = ");
    Serial.print(maxPutaran);
    Serial.print(" us | rata-rata = ");
    Serial.print(jumlah / (cacah - 1));
    Serial.println(" us");

    minPutaran = 4294967295UL;
    maxPutaran = 0;
    jumlah = 0;
    cacah = 1;
  }
}
