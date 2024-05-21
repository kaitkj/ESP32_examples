#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

String MACadd = "48:E7:29:3F:AC:5E";//Write receiver side MAC address
uint8_t address[6]  = {0x48, 0xE7, 0x29, 0x3F, 0xAC, 0x5E};//Write Receiver side MAC address in HEX
bool connected;

int button = 27;
bool buttonState = 0; //start at off

void setup() {
  Serial.begin(115200);
  pinMode(button, INPUT_PULLUP);
  SerialBT.begin("ESP32test", true); 
  Serial.println("The device started in master mode, make sure remote BT device is on!");
  
  // connect(address) is fast (upto 10 secs max), connect(name) is slow (upto 30 secs max) as it needs
  // to resolve name to address first, but it allows to connect to different devices with the same name.
  // Set CoreDebugLevel to Info to view devices bluetooth address and device names
  connected = SerialBT.connect(address);
  
  if(connected) {
    Serial.println("Connected Successfully!");
  } 
  else {
    while(!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
    }
  }
}

void loop() {
  if (digitalRead(button) != 1){
      buttonState = !buttonState;

      if (buttonState == 1){
        SerialBT.write(1);
        Serial.print("LED Status:");
        Serial.println(buttonState);
        }
        else {
          SerialBT.write(0);
          Serial.print("LED Status:");
          Serial.println(buttonState);
        }
      while (digitalRead(button) != 1){ //hold program
        delay(100);
      }
    }
  if (SerialBT.hasClient() == 0){
    Serial.println("Disconnected. Make sure remote device is available and in range, then restart app.");
    delay(10000);
  }
  delay(20);
}
