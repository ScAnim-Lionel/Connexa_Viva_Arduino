/*
  Connexa Viva Capacitive Sensor Detection
  Lionel / Science Animation 2014
  
  Based on State change detection (edge detection)
  http://arduino.cc/en/Tutorial/ButtonStateChange
 	
 The circuit:
 * Interface Z capacitive sensor output on D2
 * 10K resistor attached to pin 2 from +5V
 * LED attached from pin 13 to ground (or use the built-in LED on
 most Arduino boards)
 
 */

// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int contactledPin = 13;       // the pin that the LED is attached to
const int happyledPin = 12;       // the pin that the LED is attached to


// Variables will change:
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

//time reflexes timer
long unsigned lastTap = 0;
int happyTimer = 4000; // each 4 contact seconds, CV will be happy


void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(contactledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  // delay (1);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      lastTap = millis(); //record time of tap (since arduino was started/Reset)

      Serial.println("tap");
      digitalWrite(contactledPin, HIGH);
      digitalWrite(happyledPin, LOW);
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      digitalWrite(contactledPin, LOW);

    }

    //be happy if contact is more than 4 seconds
    if((millis() - lastTap) > happyTimer) {
      // doseOff();
      Serial.println("happy");
      digitalWrite(happyledPin, HIGH);
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState; 
}
