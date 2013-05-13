/*
  Sketch used for "buildwatch" extreme feedback device.
 
  This example code is in the public domain.
 */
int greenLed1 = 9;
int greenLed2 = 3;
int yellowLed1 = 10;
int yellowLed2 = 5;
int redLed1 = 11;
int redLed2 = 6;
int brightness = 255;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int color = 'x';

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication:
  Serial.begin(9600);  
  // initialize the digital pin as an output.
  pinMode(greenLed1, OUTPUT);
  pinMode(greenLed2, OUTPUT);
  pinMode(yellowLed1, OUTPUT);
  pinMode(yellowLed2, OUTPUT);
  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  
  // dimming effect
  if (color == 'y' || color == 'r') {
    // reverse the direction of the fading at the ends of the fade:
    if (brightness == 0 || brightness == 255) {        
      fadeAmount = -fadeAmount;
    }
    
    brightness = brightness + fadeAmount;
    
    int led1 = color == 'y' ? yellowLed1 : redLed1;
    int led2 = color == 'y' ? yellowLed2 : redLed2;
    analogWrite(led1, brightness);
    analogWrite(led2, brightness);
    
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  
  // read state:
  if (Serial.available() > 0) {
    color = Serial.read();
    
    int greenVal = color == 'g' ? HIGH : LOW;
    int yellowVal = color == 'y' ? HIGH : LOW;
    int redVal = color == 'r' ? HIGH : LOW;
    
    digitalWrite(greenLed1, greenVal);
    digitalWrite(greenLed2, greenVal);
    digitalWrite(yellowLed1, yellowVal);
    digitalWrite(yellowLed2, yellowVal);
    digitalWrite(redLed1, redVal);
    digitalWrite(redLed2, redVal);
  }
}
