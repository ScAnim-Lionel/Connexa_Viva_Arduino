/*
  Connexa Viva Capacitive Sensor Detection
  Lionel / Science Animation 2014
  
  Based on State change detection (edge detection)
  http://arduino.cc/en/Tutorial/ButtonStateChange
 	
 The circuit:
 * Interface Z capacitive sensor output on D2
 * 10K resistor attached to pin 2 from +5V
 * sensor LED attached from pin 3 to ground through 150R resistor 
 * status LED
 
 */

// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int contactledPin = 3;       // the pin that the LED is attached to
const int metamorphledPin = 12;       // the pin that the LED is attached to


// Variables will change:
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

//time reflexes timer
long unsigned lastTap = 0;
int metamorphTimer = 4000; // Timer to trigg metamorphosis
int touchtime = 500; // Timer to switch off the contact led

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
  delay (50);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      lastTap = millis(); //record time of tap (since arduino was started/Reset)

      Serial.println(0);
      digitalWrite(contactledPin, HIGH);
//      digitalWrite(metamorphledPin, LOW);
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      digitalWrite(contactledPin, LOW);

    }




    //be metamorph if contact is more than 4 seconds
    if((millis() - lastTap) > metamorphTimer) {
      // doseOff();
      Serial.println(1);
//      digitalWrite(metamorphledPin, HIGH);
    }
  
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState; 
  
    if((millis() - lastTap) > touchtime) {
      digitalWrite(contactledPin, LOW);

    }
}
