#include <Arduino.h>

// Struct tanımı
struct DataPacket {
  char header[4]; // Başlık, "SRC\0" olacak
  int a;
  int b;
};

void setup() {
  Serial.begin(9600); // Seri haberleşmeyi başlat
}

void loop() {
  // Veri paketi oluştur
  DataPacket data;
  strcpy(data.header, "SRC");
  data.a = 123; // Örnek veri
  data.b = 456; // Örnek veri
  
  // Veriyi seri porta gönder
  Serial.write((uint8_t*)&data, sizeof(data));
  
  delay(1000); // Bir saniye bekleyin
}

