#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

int LED = 14;
bool incomingState;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.print("The device started, now you can pair it with bluetooth! The MAC Address is ");
  uint8_t macBT[6];
  esp_read_mac(macBT, ESP_MAC_BT);
  Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\r\n", macBT[0], macBT[1], macBT[2], macBT[3], macBT[4], macBT[5]);
}

void loop() {
  if (SerialBT.available()) {
    incomingState = SerialBT.read();
    
    if (incomingState == 1){
      digitalWrite(LED, HIGH);
      Serial.print("LED Status:");
      Serial.println(incomingState);
    } 
    else if (incomingState == 0){
      digitalWrite(LED, LOW);
      Serial.print("LED Status:");
      Serial.println(incomingState);
      }
  }
  delay(20);
}
