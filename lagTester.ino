// Mouse - Version: Latest
#include <Mouse.h>

// light sensor pin
const byte lightSensorPin = 11;
// the number of the pushbutton pin
const byte buttonPin = 2;

// used in tests to get time when test starts
unsigned long startTime;
// used in tests to get time when sensor responded to pixel changes
unsigned long endTime;

// variable for reading the pushbutton state
bool buttonState = 0;

// variable for reading the light sensor state
bool newLightSensorState = 0;
// variable for storing previous state of light sensor
bool oldLightSensorState = 0;

void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize mouse
  Mouse.begin();
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  // initialize light sensor pin as an input
  pinMode(lightSensorPin, INPUT);
  // initialize the LED pin as an output:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // read the state of the pushbutton value:
  int buttonState = digitalRead(buttonPin);

  // check if the button is pressed. If it is, the buttonState is LOW:
  if (buttonState == LOW) {
    // turn LED on:
    digitalWrite(LED_BUILTIN, HIGH);
    
    oldLightSensorState = newLightSensorState; // store previous state of light sensor
    newLightSensorState = digitalRead(lightSensorPin); // get new state of light sensor
    // wait until sensor sees black
    while(true)
    {
      delay(5);
      oldLightSensorState = newLightSensorState; // store previous state of light sensor
      newLightSensorState = digitalRead(lightSensorPin); // get new state of light sensor
      if(newLightSensorState == oldLightSensorState)
        break;
    }
    
    Mouse.press();
    bool startSensorState = newLightSensorState;
    startTime = micros();
    delayMicroseconds(3);
    
    // wait until sensor's state is changed
    while(newLightSensorState == 1)
    {
      oldLightSensorState = newLightSensorState; // store previous state of light sensor
      newLightSensorState = digitalRead(lightSensorPin); // get new state of light sensor
      delayMicroseconds(3);
    }
    
    bool endSensorState = newLightSensorState;
    endTime = micros();
    Mouse.release();
    
    float responseTime = ((float)(endTime - startTime))/1000.0;
    Serial.println("");
    Serial.print(startTime);
    Serial.print("\t");
    Serial.print(endTime);
    Serial.print("\t");
    Serial.print(startSensorState);
    Serial.print("\t");
    Serial.print(endSensorState);
    Serial.print("\t");
    Serial.print(responseTime);
    
    delay(random(100,250));
  } else {
    // turn LED off:
    digitalWrite(LED_BUILTIN, LOW);
  }
}
