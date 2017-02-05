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
int DetectCupChange(int win_cup); //Polls cups, detects removed cups, sends data, updates pts array

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

    //generate random points cup (-1 if game over)
    int win_cup = genRandCup();
    
    while (CheckEmptyCups() !=6 ){ //still cups left
      //poll 6 cups to see if 1 got removed

      if (DetectCupChange(win_cup)){ //Polls cups, detects removed cups, sends data, updates pts array
        //cup was pulled
        win_cup = genRandCup();
      }
      delay(10);
    }
    
    //all 6 cups removed

    //TODO: Send final game data from pts_array

    mode == M_FINISH;
  }

  if (mode == M_FINISH){
    digitalWrite(pin_servo, LOW);
    mode == M_IDLE;
  }
}

//-------------------------------
// HELPER FUNCTIONS
//-------------------------------

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

//returns -1 if all cups gone, otherwise returns cup# of an avaliable cup
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

//Polls cups, detects removed cups, sends data, updates pts array
int DetectCupChange(int win_cup){
  bool pollArray [6];
  
  //poll all pins
  if (digitalRead(pin_cup1) == HIGH){
    pollArray[0] = false;
  }
  else {
    pollArray[0] = true;
  }
  if (digitalRead(pin_cup2) == HIGH){
    pollArray[1] = false;
  }
  else {
    pollArray[1] = true;
  }
  if (digitalRead(pin_cup3) == HIGH){
    pollArray[2] = false;
  }
  else {
    pollArray[2] = true;
  }
  if (digitalRead(pin_cup4) == HIGH){
    pollArray[3] = false;
  }
  else {
    pollArray[3] = true;
  }
  if (digitalRead(pin_cup5) == HIGH){
    pollArray[4] = false;
  }
  else {
    pollArray[4] = true;
  }
  if (digitalRead(pin_cup6) == HIGH){
    pollArray[5] = false;
  }
  else {
    pollArray[5] = true;
  }

  //compare pts array and poll array for changes
    //if cup is missing, determine whether its a 5 or a 10, send data, and update pts array

  bool flag_CupsChanged = false;
  
  for (int i = 0; i < 6; i++) {
    if (pts_array[i] == 0)
      if (pollArray[i] == true){
        //cup gone
        flag_CupsChanged = true;
        if (i+1 == win_cup){
          //TODO send cup is 10 data
          pts_array[i] = 10;
        }
        else{
          //TODO send cup is 5 data
          pts_array[i] = 5;
        }
      }
    }

  if (flag_CupsChanged){
    return 1;
  }
  else{
    return 0;
  }
}


