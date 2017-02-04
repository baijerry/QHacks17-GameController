#include <string.h>
#include <Servo.h>

//-------------------------------
// VARIABLES
//-------------------------------

enum MODE { M_IDLE = 0, M_GAME, M_FINISH };
MODE mode;

bool isHard;

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
int CheckEmptyCups();

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

  mode = M_IDLE;
  isHard = false;
}

//-------------------------------
// MAIN LOOP
//-------------------------------
void loop(){
  if (mode == M_IDLE){
    //TODO: wait for starting game command
    //- parse isHard data
    while(0){
      delay(100);
    }
    
    if (!checkcupstatus()){
      //not ready to start

      //TODO: send not ready command
    }
    while (CheckEmptyCups()!=0){
      delay(100);
    }
    //TODO: send ready command

    if (isHard){
      digitalWrite(pin_servo, HIGH);
    }
    else {
      digitalWrite(pin_servo, LOW);
    }
    
    mode = M_GAME;
  }

  if (mode == M_GAME){
    int pts_array [6];
    
    if (CheckEmptyCups()==6) {
      //game over
      //TODO: send game over data
      mode = M_FINISH;
    }
  }

  if (mode == M_FINISH){
    
  }
}

//-------------------------------
// MAIN FUNCTIONS
//-------------------------------
int CheckEmptyCups(){
  int count = 0;
  if (digitalRead(pin_cup1) == LOW)
    count++;
  if (digitalRead(pin_cup2) == LOW)
    count++;
  if (digitalRead(pin_cup3) == LOW)
    count++;
  if (digitalRead(pin_cup4) == LOW)
    count++;
  if (digitalRead(pin_cup5) == LOW)
    count++;
  if (digitalRead(pin_cup6) == LOW)
    count++;

  return count;
}

//-------------------------------
// HELPER FUNCTIONS
//-------------------------------


