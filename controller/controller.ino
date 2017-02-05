#include <string.h>
#include <Servo.h>

//-------------------------------
// VARIABLES
//-------------------------------

enum MODE { M_IDLE = 0, M_GAME, M_FINISH };
MODE mode;

bool isHard;

/*
  0  = cup not removed
  5  = hit cup
  10 = hit points cup
  
*/
int pts_array [6];

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
void clearArray();
int genRandCup();

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
    
    if (CheckEmptyCups() != 0){
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
    //start game

    //clear array (all cups in)
    clearArray();

    //generate random points cup
    int win_cup = genRandCup();
    
    while (CheckEmptyCups() !=6 ){ //still cups left
      
    }
    
    //all 6 cups removed
  }

  if (mode == M_FINISH){
    digitalWrite(pin_servo, LOW);

    
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

void clearArray(){
  for (int i = 0; i < 6; i++){
    pts_array[i] = 0;
  }
}

int genRandCup(){
  int a_index = 0; //length of existing cup array
  int existing_cup_array[6];
  
  for (int i = 0; i < 6; i++) {
    if (pts_array[i] == 0){
      existing_cup_array[a_index] = i;
      a_index++;
    }
  }

  //existing_cup_array contains list of all pts array indexes with value = 0. Has length of a_index

  if (a_index == 0) {
    //all cups are gone, cannot do rand int command (game is over)
    return -1;
  }
  
  //Chose random index from existing_cup_array
  int randIndex = random(0, a_index);
  //Convert that into a cup number to return
  return existing_cup_array[randIndex] + 1;  
}

//-------------------------------
// HELPER FUNCTIONS
//-------------------------------


