//alıcı
#include <Arduino.h>

// Struct tanımı
struct DataPacket {
  char header[4]; // Başlık, "SRC\0" olacak
  int a;
  int b;
};

void setup() {
  Serial.begin(9600); // Seri haberleşmeyi başlat
  while (!Serial); // Seri bağlantının hazır olduğundan emin ol
}

void loop() {
  static bool headerReceived = false;
  static DataPacket data;
  static int dataIndex = 0;
  
  while (Serial.available() > 0) {
    char c = Serial.read();
    
    if (!headerReceived) {
      // Başlık kontrolü
      if (dataIndex < 3 && c == "SRC"[dataIndex]) {
        data.header[dataIndex] = c;
        dataIndex++;
        
        if (dataIndex == 3) {
          data.header[3] = '\0'; // Null karakter ekle
          headerReceived = true;
          dataIndex = 0;
        }
      } else {
        // Başlık eşleşmezse resetle
        dataIndex = 0;
      }
    } else {
      // Veri alımı
      if (dataIndex < sizeof(DataPacket)) {
        ((char*)&data)[dataIndex] = c;
        dataIndex++;
        
        if (dataIndex == sizeof(DataPacket)) {
          // Veri paketi tamamlandı
          Serial.print("Received data: ");
          Serial.print("Header: ");
          Serial.print(data.header);
          Serial.print(", a: ");
          Serial.print(data.a);
          Serial.print(", b: ");
          Serial.println(data.b);
          
          // İşleme hazır hale getir
          headerReceived = false;
          dataIndex = 0;
        }
      }
    }
  }
}

