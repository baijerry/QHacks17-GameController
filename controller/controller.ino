#include <string.h>
#include <Servo.h>
//#include <SoftwareSerial.h>

//-------------------------------
// VARIABLES
//-------------------------------

enum MODE { M_IDLE = 0, M_GAME, M_FINISH };
MODE mode;
//SoftwareSerial serial_servo(13, 12); //RX, TX; only 12 is used
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
void debug();
void setLED(int win_cup);
void flashfront();
void setLEDs_off();
void setLEDs_on();
//void printcupstatus();

//-------------------------------
// SETUP
//-------------------------------
void setup() {
  Serial.begin(9600);
  //serial_servo.begin(9600);
  
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

  flashfront();
  delay(500);
}

//-------------------------------
// MAIN LOOP
//-------------------------------
void loop(){
  if (mode == M_IDLE){
    Serial.println("Enter Letter to Start Game");
    while (!Serial.available()){
      delay(100);
    }
    
    if (CheckEmptyCups() != 0){
      //not ready to start
      Serial.println("Not all cups are in");
    }
    while (CheckEmptyCups()!=0){
      //printcupstatus();
      delay(1000);
    }
    Serial.println("Starting Game!");
    
    //Send signal (ready)
    Serial.print("NODE:ready:1");
    
    Serial.println("");

    //start servo
    //digitalWrite(pin_servo, HIGH);
    //serial_servo.write('i');

    mode = M_GAME;
  }

  if (mode == M_GAME){
    //start game

    //clear pts array (all cups in)
    clearArray();

    //generate random points cup (-1 if game over)
    int win_cup = genRandCup();

    while (CheckEmptyCups() !=6 ){ //still cups left
      //poll 6 cups to see if 1 got removed

      if (DetectCupChange(win_cup)){ //Polls cups, detects removed cups, sends data, updates pts array
        //cup was pulled
        win_cup = genRandCup();
        setLED(win_cup);
      }
      delay(10);
    }

    //all 6 cups removed

    //send signal (end)
    Serial.print("NODE:end:1");
    Serial.println("");

    mode == M_FINISH;
  }

  if (mode == M_FINISH){
    //digitalWrite(pin_servo, LOW);
    //serial_servo.write('o');
    mode == M_IDLE;
  }
}

//-------------------------------
// HELPER FUNCTIONS
//-------------------------------
void print_pts_array(){
  for (int i = 0; i < 6; i++)
    Serial.println(pts_array[i]);
}

void printcupstatus(){
  //poll all pins
  if (digitalRead(pin_cup1) == HIGH){
    Serial.print("Cup 1: In");
  }else {
    Serial.print("Cup 1: Out");
  }
    
  if (digitalRead(pin_cup2) == HIGH){
    Serial.print("Cup 2: In");
  }else {
    Serial.print("Cup 2: Out");
  }
    
  if (digitalRead(pin_cup3) == HIGH){
    Serial.print("Cup 3: In");
  }else {
    Serial.print("Cup 3: Out");
  }
    
  if (digitalRead(pin_cup4) == HIGH){
    Serial.print("Cup 4: In");
  }else {
    Serial.print("Cup 4: Out");
  }
    
  if (digitalRead(pin_cup5) == HIGH){
    Serial.print("Cup 5: In");
  }else {
    Serial.print("Cup 5: Out");
  }
    
  if (digitalRead(pin_cup6) == HIGH){
    Serial.print("Cup 6: In");
  }else {
    Serial.print("Cup 6: Out");
    }
}

void flashfront(){
  Serial.println("flashing front");
  for (int i =0; i < 6; i++){  
    setLEDs_off();
    delay(200);
    setLEDs_on();
    delay(200);
  }
    setLEDs_off();
}

void debug(){
  Serial.println("Debug:");
  while(!Serial.available()){
    delay(10);
  }
  
  int todo = Serial.read();

  switch (todo){
    case 0:
      print_pts_array();
      break;
    case 1:

      break;
  }
}

void setLEDs_off(){
  digitalWrite(pin_led1, LOW);
  digitalWrite(pin_led2, LOW);
  digitalWrite(pin_led3, LOW);
  digitalWrite(pin_led4, LOW);
  digitalWrite(pin_led5, LOW);
  digitalWrite(pin_led6, LOW);
}

void setLEDs_on(){
  digitalWrite(pin_led1, HIGH);
  digitalWrite(pin_led2, HIGH);
  digitalWrite(pin_led3, HIGH);
  digitalWrite(pin_led4, HIGH);
  digitalWrite(pin_led5, HIGH);
  digitalWrite(pin_led6, HIGH);
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

void setLED(int win_cup){
  setLEDs_off();
  
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
           
          //send signal (shot, 10pts)
          String cup = String(i+1);
          String out = "NODE:shot:10," + cup;
          Serial.print(out);
          Serial.println("");
          
          pts_array[i] = 10;
        }
        else{
          //send signal (shot, 5pts)
          String cup = String(i+1);
          String out = "NODE:shot:5," + cup;
          Serial.print(out);
          Serial.println("");
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
