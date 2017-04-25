/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 */

 #include <Servo.h>
#include <SoftwareSerial.h>
 Servo myservo;

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // pushbutton pin
const int ledPin =  13;      // LED pin
const int pirPin = 3;   // PIR sensor
const int buzzerPin = 6; //buzzerPin

const int btTX = 8;
const int btRX = 7;

SoftwareSerial bt(btTX, btRX);

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int pirState = LOW;          // we start, assuming no motion is detected
int pirval = 0;                 // variable for reading the pin status

void setup() {
  // initialize inputs and outputs
  pinMode(buttonPin, INPUT);
  pinMode(pirPin, INPUT);     // declare sensor as input
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  myservo.attach(4);
  bt.begin(115200);                                                                                                                                                                                 

  myservo.write(90);    //setting the servo mid-point
  for(int i = 0; i < 256; i+= 5){
    analogWrite(buzzerPin, i);
    delay(20);
  }
}
unsigned long t;
void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  pirval = digitalRead(pirPin);

  // Buzzer
  if(t-millis()>500){t=millis();
  bt.println("test!");
  }
  if(bt.available()) Serial.write(bt.read());
  return;
  // PIR sensor stuff
  if (pirval == HIGH) {          // check if the input is HIGH
    Serial.println("Motion detected!");  // Announce on serial monitor
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detecter ready!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } 
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  
  // Doorbell is pressed? If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    Serial.println("DING DONG MOTHERFUCKER!");
    myservo.write(180);
    //delay(2000);
    myservo.write(90);
    digitalWrite(buzzerPin, LOW);

  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, HIGH);

  } 
}
