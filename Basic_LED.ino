int button = 15; //declare button to pin 15
int LED = 2; //declare LED to pin 2
bool buttonState = 0; //start at off

void setup() {
  //put your setup code here, to run once:
  Serial.begin(155200);
  pinMode(button, INPUT_PULLUP); //set button as input, with pullup (normally high)
  pinMode(LED, OUTPUT); //set LED as output
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(button) != 1){ //when button press, signal becomes LOW, fulfilling the condition
    buttonState = !buttonState; //flips the boolean buttonState value

    if (buttonState == 1){  //when buttonState is 1, on the LED
      digitalWrite(LED, HIGH);
      Serial.print("LED Status:");
      Serial.println(buttonState);
      }
      else{
        digitalWrite(LED, LOW); //when buttonState is 0, off the LED
        Serial.print("LED Status:");
        Serial.println(buttonState);
      }
    while (digitalRead(button) != 1){ //hold program
      delay(100);
    }
  }
}