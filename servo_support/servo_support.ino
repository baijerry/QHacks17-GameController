#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo;
int pin_read = 12;

SoftwareSerial serial_servo(8, 9); //RX, TX; only 8 is used

int pos = 0;    // variable to store the servo position
int move_flag;

void setup() {
  servo.attach(2);
  servo.write(0);
  serial_servo.begin(9600);
  move_flag = false;
  pinMode(pin_read, INPUT);
}



void loop(){

  if (serial_servo.available()){
    char letter = serial_servo.read();
    if (letter == 'o') {
                move_flag = false;
            }
    if (letter == 'i') {
                move_flag = true;
    }
  }

  if (move_flag){
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
  else {
    //nothing
  }

/*  
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
*/

}
