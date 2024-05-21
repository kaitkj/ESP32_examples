#if CONFIG_IDF_TARGET_ESP32S3
  static int myled = 5; //GPIO for LED
  #define LIGHT_SENSOR_PIN 6
#else
  static int myled = 14; //GPIO for LED
  #define LIGHT_SENSOR_PIN 12
#endif

// LDR Characteristics
const float GAMMA = 0.5;
const float RL10 = 5;

void setup() {
  // initialize serial communication at 115200 bits per second
  Serial.begin(115200);
  pinMode(myled, OUTPUT);
}

void loop() {
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  float voltage = analogValue / 4095. * 5;
  float resistance = 10000 * voltage / (5 - voltage);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

  Serial.print("Analog Value = ");
  Serial.println(analogValue);
  Serial.print("Voltage = ");
  Serial.println(voltage);
  Serial.print("Resistance = ");
  Serial.println(resistance);
  Serial.print("lux = ");
  Serial.print(lux);

  //On myled when room is dark, off myled when room is bright
  if (lux > 40) {
    Serial.println(" => Bright \n");
    digitalWrite(myled, LOW);
  } else {
    Serial.println(" => Dark \n");
    digitalWrite(myled, HIGH);
  }
  delay(500);
}
