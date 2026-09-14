#include <Arduino.h>

const int LED_MERAH = 4;
const int FREKUENSI = 500; // Hz
const int RESOLUSI = 10;   // bit -> nilai duty 0..1023

void setup() {
  Serial.begin(115200);
  delay(1000);

  // --- Core ESP32 versi 3.x ---
  ledcAttach(LED_MERAH, FREKUENSI, RESOLUSI);
  
  Serial.println("Mulai pengukuran PWM. Amati multimeter Anda!");
}

void loop() {
  // Daftar nilai duty dari 0 hingga 1023 (maksimal 10 bit)
  int nilaiDuty[] = {0, 256, 512, 768, 1023};

  for (int i = 0; i < 5; i++) {
    ledcWrite(LED_MERAH, nilaiDuty[i]); // Keluarkan PWM ke pin

    Serial.print("duty = ");
    Serial.print(nilaiDuty[i]);
    Serial.print(" (");
    Serial.print(100.0 * nilaiDuty[i] / 1023.0, 1);
    Serial.println(" %)");

    delay(8000); // Tunggu 8 detik agar Anda sempat membaca multimeter
  }
}