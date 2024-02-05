int button = 27; //declare button to pin 27
int LED = 14; //declare LED to pin 14
bool buttonState = 0; //start at off

void setup() {
  //put your setup code here, to run once:
  Serial.begin(155200);
  pinMode(button, INPUT_PULLUP); //set button as input, with pullup (normally high)
  pinMode(LED, OUTPUT); //set LED as output
  Serial.println();
  Serial.println();
  Serial.println("*** Toggle the Green button to On/Off light ***");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(button) != 1){ //when button press, signal becomes LOW, fulfilling the condition
    buttonState = !buttonState; //flips the boolean buttonState value
    if (buttonState == 1) {
          digitalWrite(LED, HIGH); //when buttonState is 1, on the LED
          Serial.println("*** Light On **"); 
    } else{
      digitalWrite(LED, LOW); //when buttonState is 0, off the LED
      Serial.println("*** Light Off ***");
    }
    while (digitalRead(button) != 1){
      delay (100);
    }
  delay(100);
  }
}
