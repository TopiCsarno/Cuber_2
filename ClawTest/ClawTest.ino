#include <Servo.h>

Servo myservo;

const byte servoPin = 9;
int pos = 0;
boolean stop = 0;

const byte numChars = 128;
char input[numChars];
boolean newData = false;

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
  Serial.println("Setup finished\n");
}

void loop() {
  receiveMessage();
  parseMessage();
  delay(50);
}

void parseMessage() {
  if (newData == true) {
    if (strcmp(input, "move") == 0) {
      Serial.println("Move executed\n");
      moveServo(90);
    } else {
      Serial.println("invalid\n");
    }
    newData = false;
  }
}

void receiveMessage() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
     rc = Serial.read();
     if (recvInProgress == true) {
       if (rc != endMarker) {
         input[ndx] = rc;
         Serial.print(input[ndx]);
         ndx++;
         if (ndx >= numChars) {
           ndx = numChars - 1;
         }
       }
       else {
         input[ndx] = '\0'; // terminate the string
         recvInProgress = false;
         ndx = 0;
         newData = true;
         Serial.println("\n");
       }
     }

     else if (rc == startMarker) {
       recvInProgress = true;
     }
   }
}
