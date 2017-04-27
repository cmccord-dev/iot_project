#include <Servo.h>
#include <SoftwareSerial.h>
Servo myservo;

// constants used here to set pin numbers:
const int buttonPin = 2;      // pushbutton pin
const int ledPin =  13;       // LED pin
const int pirPin = 3;         // PIR sensor
const int pirPin2 = 4;        // PIR2 sensor (inside the door)
const int buzzerPin = 6;      // buzzerPin
const int btTX = 8;
const int btRX = 7;

char val = '0';               // variable to receive data from the serial port with bluetooth

SoftwareSerial bt(btTX, btRX);

// variables:
int buttonState = 0;         // variable for reading the pushbutton status
int pirState = LOW;          // we start, assuming no motion is detected
int pirval = 0;              // variable for reading the pin status
int pirval2 = 0;
int alarm = 0;

void setup() {
  // initialize inputs and outputs
  pinMode(buttonPin, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(pirPin2, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  myservo.attach(5);
  bt.begin(115200);

  myservo.write(90);            //setting the servo mid-point
  for (int i = 0; i < 256; i += 5) {
    analogWrite(buzzerPin, i);
    delay(20);
  }
}
unsigned long t;
void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  pirval = digitalRead(pirPin);
  pirval2 = digitalRead(pirPin2);


  if (bt.available()) {        // if data is available to read
    //{;}
    val = bt.read();         // read it and store it in 'val'

    if (val == '1')  {            // if '1' was received turn servo 180deg to open lock
      alarm = 0;
      myservo.write(180);           // turn servo to 180 deg
      Serial.println("Lock open");
    }

    if (val == '0')  {           // if '0' was received turn servo to 90deg to lock the lock
      myservo.write(90);        // turn servo to 90 deg
      Serial.println("Door is now locked");
      alarm = 1;
    }
    if (val == '2')  {                      // if '2' was received turn off the buzzer
      digitalWrite(buzzerPin, LOW);        // turn off the alarm
      Serial.println("Alarm deactivated");
    }
  }
  if (alarm == 1 && pirval2 == HIGH)  {
    digitalWrite(buzzerPin, HIGH);
    bt.println("ALARM!");
    Serial.println("ALARM!");
  }

  /* if(t-millis()>500){t=millis();
    bt.println("test!");
    }
    if(bt.available()) Serial.write(bt.read());
    return;*/

  // PIR sensor stuff
  if (pirval == HIGH) {                     // check if the input is HIGH
    Serial.println("Motion detected!");     // Announce on serial monitor
    bt.println("Motion detected!");          // send the alert through bluetooth
  }

  // Doorbell is pressed? If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    Serial.println("DING DONG MOTHERFUCKER!");
    bt.println("Doorbell");
  } else {
    digitalWrite(buzzerPin, HIGH);
  }
}
