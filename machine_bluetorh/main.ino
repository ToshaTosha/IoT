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


int states[4][2]{
  {0,0},
  {0,1},
  {1,0},
  {1,1}
};

int forward[] = {0,0};
int back[] = {0,0};
int left[] = {0,0};
int right[] = {0,0};

int wheel_speed [] = {205, 205};
int rotation_speed [] = {500, 500, 500, 500}; //////

int speed_diff = 10;
int rotation_diff = 100;

void move(bool lforward, bool rforward, int lvelocity, int rvelocity){
  digitalWrite(DIR_RIGHT, rforward);
  digitalWrite(DIR_LEFT, lforward);
  analogWrite(SPEED_RIGHT, rvelocity);
  analogWrite(SPEED_LEFT, lvelocity);
}

void move_forward(){
  move(forward[0], forward[1], wheel_speed[0], wheel_speed[1]);
}

void move_back(){
  move(back[0], back[1], wheel_speed[0], wheel_speed[1]);
}

void rotate_left(){
  move(left[0], left[1], wheel_speed[0], wheel_speed[1]);
}

void rotate_right(){
  move(right[0], right[1], wheel_speed[0], wheel_speed[1]);
}
void stop(){
  move(false, true, 0, 0);
}


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  for (int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
}


char dir_cmd;
int next = 0; //счетчик нажатия на крест

void calibrate_direction(char cmd){

  if(cmd == FORWARD || cmd == BACKWARD ||
  cmd == LEFT || cmd == RIGHT){
    dir_cmd = cmd;
    move(states[next][0],states[next][1], wheel_speed[0], wheel_speed[1]);
    delay(1000);
    stop();
  }
  else if(cmd == CROSS){
    next++;
    move(states[next][0],states[next][1], wheel_speed[0], wheel_speed[1]);
    delay(1000);
    stop();
            
  }
  else if(cmd == TRIANGLE){
    switch (dir_cmd){
      case FORWARD:
        forward[0] = states[next][0];
        forward[1] = states[next][1];
        break;
      case BACKWARD:
        back[0] = states[next][0];
        back[1] = states[next][1];
        break;
      case LEFT:
        left[0] = states[next][0];
        left[1] = states[next][1];
        break;
      case RIGHT:
        right[0] = states[next][0];
        right[1] = states[next][1];
        break;
    }
    next=0;
  }
  else{
    break;
  }
}
void calibrate_velocity(char cmd){

}
void calibrate_rotation(char cmd){

}
int change_type = 0;
void loop() {

  if (mySerial.available()) {
    
    char cmd = mySerial.read();
    Serial.print("COMMAND: ");
    Serial.println(cmd);
    
    if(cmd==START){
        change_type += 1;
    }

    switch (change_type){
        case 1:
          calibrate_direction(cmd);
          break;
        case 2:
          //calibrate_velocity(command);
          break;
        case 3:
          //calibrate_rotation(command);
          break;
        case 4:
          Serial.println("calibration completed");
          ///// откалибровался и поехал
          /// стрелки: двигаться в определённую сторону пока не пришёл 0
          break;
        default:
          break;
      }
  }
}
