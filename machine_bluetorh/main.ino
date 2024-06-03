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
int rotation_time [] = {250, 500, 750, 1000}; // рандомные значения для 90 180 270 360 градусов 

int speed_diff = 10;
int rotation_diff = 50;

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
    if(next>=4){
      next=0;
    }
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
  }
}

int wheel = 0;
void calibrate_velocity(char cmd){
  if(cmd == LEFT){
    wheel = 0;
    move_forward();
    delay(1000);
    stop();
  }
  else if(cmd == RIGHT){
    wheel = 1;
    move_forward();
    delay(1000);
    stop();
  }
  else if(cmd == SQUARE){
    if(wheel_speed[wheel] + speed_diff > 255){
      wheel_speed[wheel] = 255;
    }else{
      wheel_speed[wheel] += speed_diff;
    }
    move_forward();
    delay(200);
    stop();
  }
  else if(cmd == CIRCLE){
    if(wheel_speed[wheel] - speed_diff < 0){
      wheel_speed[wheel] = 0;
    }else{
      wheel_speed[wheel] -= speed_diff;
    }
    move_forward();
    delay(200);
    stop();
  }
  else{
  }
}

int count = 0;
int num = -1;
void rotate(){
  rotate_right();
  delay(rotation_time[num]);
  stop();
}
void calibrate_rotation(char cmd){
  if(cmd == LEFT){ // +
    if(count == 1){
      rotation_time[num] += rotation_diff;
    }
  }
  if(cmd == RIGHT){ // -
    if(count == 1){
      if(rotation_time[num] - rotation_diff < 0){
        rotation_time[num] = 0;
      }
      else{
        rotation_time[num] -= rotation_diff;
      }
    }
  }
  if(cmd == SQUARE){ //90
    num = 0;
    count++;
    if(count == 2){
      rotate();
      count = 0;
    }
    
  }
  else if(cmd == TRIANGLE){ // 180
    num = 1;
    count++;
    if(count == 2){
      rotate();
      count = 0;
    }
  }
  else if(cmd == CIRCLE){ // 270
    num = 2;
    count++;
    if(count == 2){
      rotate();
      count = 0;
    }
  }
  else if(cmd == CROSS){ // 360
    num = 3;
    count++;
    if(count == 2){
      rotate();
      count = 0;
    }
  }
  else{
  }
}



int change_type = 0;
int pause_count = 0;
char prev_cmd;

void choose_rot(){
          if(prev_cmd == SQUARE){
            delay(rotation_time[0]);
            stop();
          }
          if(prev_cmd == TRIANGLE){
            delay(rotation_time[1]);
            stop();
          }
          if(prev_cmd == CIRCLE){
            delay(rotation_time[2]);
            stop();
          }
          if(prev_cmd == CROSS){
            delay(rotation_time[3]);
            stop();
          }
          else{}
}

void loop() {

  if (mySerial.available()) {
    
    char cmd = mySerial.read();
    Serial.print("COMMAND: ");
    Serial.println(cmd);
    
    if(cmd==START){
      change_type++;
    }
    if(cmd==PAUSE){
      pause_count++;
    }
    if(pause_count == 1){ //просмотр калибровки
        prev_cmd = cmd;
        if(cmd==FORWARD){
          move_forward();
        }
        if(cmd==BACKWARD){
          move_back();
        }
        if(cmd==LEFT){
          rotate_left();
          choose_rot();
        }
        if(cmd==RIGHT){
          rotate_right();
          choose_rot();
        }

        if(cmd == SQUARE || cmd == TRIANGLE || cmd == CIRCLE || cmd == CROSS){
          stop();
        }
    }
    if(pause_count == 2){ // возвращение к калибровке
      pause_count = 0;
      stop();
    }
    if(pause_count == 2 and change_type == 4){ // откалибровать заново
      change_type = 0;
      stop();
    }

    switch (change_type){
        case 1:
          calibrate_direction(cmd);
          break;
        case 2:
          calibrate_velocity(cmd);
          break;
        case 3:
          calibrate_rotation(cmd);
          break;
        default:
          break;
      }
  }
}
