#include "config.h"

#include "ArduinoJson.h"
#include "SparkIntervalTimer.h"

#include <string.h>
#include <Servo.h>

//-------------------------------
// VARIABLES
//-------------------------------

enum MODE { M_IDLE = 0, M_GAME, M_FINISH };
MODE mode;

//pin mapping
/*
  1
 2 3
4 5 6
*/
#define pin_cup1 0
#define pin_cup2 1
#define pin_cup3 2
#define pin_cup4 3
#define pin_cup5 4
#define pin_cup6 5

#define pin_led1 6
#define pin_led2 7
#define pin_led3 8
#define pin_led4 9
#define pin_led5 10
#define pin_led6 11

#define pin_servo 12

//arrays

//forward declare
bool checkcupstatus();

//-------------------------------
// SETUP
//-------------------------------
void setup() {
  pinMode (pin_cup1, INPUT);
  pinMode (pin_cup2, INPUT);
  pinMode (pin_cup3, INPUT);
  pinMode (pin_cup4, INPUT);
  pinMode (pin_cup5, INPUT);
  pinMode (pin_cup6, INPUT);

  pinMode (pin_led1, OUTPUT);
  digitalWrite(pin_led1, LOW);
  pinMode (pin_led2, OUTPUT);
  digitalWrite(pin_led2, LOW);
  pinMode (pin_led3, OUTPUT);
  digitalWrite(pin_led3, LOW);
  pinMode (pin_led4, OUTPUT);
  digitalWrite(pin_led4, LOW);
  pinMode (pin_led5, OUTPUT);
  digitalWrite(pin_led5, LOW);
  pinMode (pin_led6, OUTPUT);
  digitalWrite(pin_led6, LOW);
}

//-------------------------------
// MAIN LOOP
//-------------------------------
void loop(){
  if (mode == M_IDLE){
    
    //ToDo: wait for starting game command
    if (checkcupstatus()){
        
      }
  }    
}

//-------------------------------
// MAIN FUNCTIONS
//-------------------------------
bool checkcupstatus(){
  bool flag = true;
  if (digitalRead(pin_cup1) == LOW)
    flag = false;
  if (digitalRead(pin_cup2) == LOW)
    flag = false;
  if (digitalRead(pin_cup3) == LOW)
    flag = false;
  if (digitalRead(pin_cup4) == LOW)
    flag = false;
  if (digitalRead(pin_cup5) == LOW)
    flag = false;
  if (digitalRead(pin_cup6) == LOW)
    flag = false;
}

//-------------------------------
// HELPER FUNCTIONS
//-------------------------------
