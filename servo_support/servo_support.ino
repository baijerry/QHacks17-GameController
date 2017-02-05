#include <Servo.h>

Servo servo;
int pin_read = 12;

int pos = 0;    // variable to store the servo position

void setup() {
  servo.attach(2);
  servo.write(0);
  pinMode(pin_read, INPUT);
}

void loop(){
  if (digitalRead(pin_read) == HIGH){
    delay(300);
    if (digitalRead(pin_read) == HIGH){
      for (pos = 0; pos <= 180; pos += 2) {
        servo.write(pos);
        delay(35);
      }
      delay(500);
      for (pos = 180; pos >= 0; pos -= 2) {
        servo.write(pos);
        delay(35);
      }
      delay(500);
    }
  }

  delay(10);
}
