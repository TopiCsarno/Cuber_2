//define functions called by the main loop

void moveServo(int dest) {

  while (dest != pos) {
    pos = (dest - pos) > 0 ? pos+1 : pos-1;
    Serial.println(pos);
    delay(25);
  }
  Serial.print("pos changed to: ");
  Serial.println(pos);
  //myservo.write(pos);
}

void emstop() {
  stop = true;
}
