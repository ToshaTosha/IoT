#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);

#define DIR_RIGHT 4 
#define SPEED_RIGHT 5
#define DIR_LEFT 7 
#define SPEED_LEFT 6

#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define CIRCLE 'C'
#define CROSS 'X'
#define TRIANGLE 'T'
#define SQUARE 'S'
#define START 'A'
#define PAUSE 'P'

void move(bool lforward, bool rforward, int lvelocity, int rvelocity){
  digitalWrite(DIR_RIGHT, rforward);
  digitalWrite(DIR_LEFT, lforward);
  analogWrite(SPEED_RIGHT, rvelocity);
  analogWrite(SPEED_LEFT, lvelocity);
}

void move_forward(int velocity){
  move(true, false, velocity, velocity);
}

void move_back(int velocity){
  move(false, true, velocity, velocity);
}

void rotate_left(int velocity){
  move(false, false, velocity, velocity);
}

void rotate_right(int velocity){
  move(true, true, velocity, velocity);
}
void stop(){
  move(false, true, 0, 0);
}



// typedef void (*CommandFunction)(int, int);

// CommandFunction move[4] = {
//   move_forward,     
//   move_back, 
//   rotate_left,
//   rotate_right
// };

int wheel_speed [] = {205, 205};
int rotation_speed [] = {500, 500, 500, 500}; //////

int speed_diff = 10;
int rotation_diff = 100;


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  for (int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
}


void calibrate_direction(){

}
void calibrate_velocity(){

}
void calibrate_rotation(){

}
int change_type = 0;

void loop() {

  if (mySerial.available()) {
    char command = mySerial.read();

    Serial.print("COMMAND: ");
    Serial.println(command);
    
    if(command==START){
        change_type += 1;
    }

    switch (change_type){
        case 1: 
          calibrate_direction();
          break;
        case 2:
          calibrate_velocity();
          break;
        case 3:
          calibrate_rotation();
          break;
        case 4:
          ///// откалибровался и поехал
          /// стрелки: двигаться в определённую сторону пока не пришёл 0
          break;
        default:
          break;
      }
  }
}

void executeCommand(char command) {
  switch (command) {
    case FORWARD:
      // Perform action for moving forward
      break;
    case BACKWARD:
      // Perform action for moving backward
      break;
    case LEFT:
      // Perform action for turning left
      break;
    case RIGHT:
      // Perform action for turning right
      break;
    case CIRCLE:
      // Perform action for circle
      break;
    case CROSS:
      // Perform action for immediate stop or crossing
      break;
    case TRIANGLE:
      // Perform action for toggling a state (e.g., LED on/off)
      break;
    case SQUARE:
      // Perform action for retrieving and sending status information
      break;
    default:
      // Invalid command received
      break;
  }
}

