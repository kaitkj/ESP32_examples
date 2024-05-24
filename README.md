# ESP32_examples 
Examples prepared for workshop content. The examples are built for ESP32-WROOM-32E Dev Kit, ESP32-S3-DevkitC-1 and Arduino IDE. For setup of Arduino IDE for ESP32, visit [Espressif Arduino Repository](https://github.com/espressif/arduino-esp32/tree/master) and [Getting Started Guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/getting_started.html).

## Content
1. Basic LED
    - Push button once to toggle between on and off LED
3. LDR LED
    - When in dark environment, turn on LED, else off LED
4. Receiver LED
    - Receiver via Bluetooth Classic. When receiving '1', turn on LED. When receiving '0', turn off LED
    - Only for ESP32
5. Transmitter Button
    - Transmitter via Bluetooth Classic. When button press, send a signal to toggle LED on receiver
    - Only for ESP32
6. Transmitter LDR
    - Transmitter via Bluetooth Classic. When in dark environment, turn on LED, else off LED
    - Only for ESP32
7. BLE Client LED
    - Connects to BLE Server and receives updates via notifyCallback. When receiving '1', turn on LED. When receiving '0', turn off LED
    - Only for ESP32-S3
8. BLE Server Button
    - Connects to BLE Client and sends updates via notify. When the button is pressed, toggle the characteristic value to '1' or '0'
    - Only for ESP32-S3
  
9. Rainmaker switch and LDR
    - Runs Rainmaker. Collects LDR sensor data, and control LED from both app and device.
    - Only for ESP32-S3
    - Work in progress for compatibility with ESP32

## Logistics

1. ESP32 Dev Kit OR ESP32-S3 Dev Kit
2. Breadboard
3. Light Dependent Resistor
4. Push button
5. Red LED
6. Resistors (will need at least 1 pcs 1-3k ohm resistor, and 1 pcs 8-10k ohm resistor)
7. Lots of jumper wires
8. Micro USB Data Cable
