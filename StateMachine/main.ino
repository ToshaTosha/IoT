// 4, 7 for direction
// 5, 6 for speed

//возможно придется подобрать константы (поменять high и low местами)
#define DIR_RIGHT 4 
#define SPEED_RIGHT 5
#define DIR_LEFT 7 
#define SPEED_LEFT 6

//передний датчик
#define F_TRIG 9
#define F_ECHO 8

//левый датчик
#define L_TRIG 11
#define L_ECHO 10

int ROTATION_TIME = 500; // время вращения вправо
int ROTATION_TIME_LEFT = 500; // время вращения влево
int FORWARD_BEFORE_ROTATION = 400; // 
int FORWARD_AFTER_ROTATION = 700;
int time = 0; 

int FD = 20; // расстояние спереди
int CD = 10; // расстояние сбоку 

void setup() {
  Serial.begin(9600);
  
  pinMode(F_TRIG, OUTPUT);
  pinMode(F_ECHO, INPUT);
  pinMode(L_TRIG, OUTPUT);
  pinMode(L_ECHO, INPUT);
  for (int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
  stop();
}

void move(bool lforward, bool rforward, int lvelocity, int rvelocity){
  digitalWrite(DIR_RIGHT, rforward);
  digitalWrite(DIR_LEFT, lforward);
  analogWrite(SPEED_RIGHT, rvelocity);
  analogWrite(SPEED_LEFT, lvelocity);
}

void move_forward(int velocity){
  move(true, false, velocity, velocity);
}

/*void move_back(int velocity){
  move(false, true, velocity, velocity);
}*/

void rotate_left(int velocity){
  move(false, false, velocity, velocity);
}

void rotate_right(int velocity){
  move(true, true, velocity, velocity);
}

void turn_left(int velocity){ //выравнивание к стене
  move(true, false, velocity/2, velocity);
}
void turn_right(int velocity){ //выравнивание от стены
  move(true, false, velocity, velocity/2);
}

void stop(){
  move(false, true, 0, 0);
}

float get_distance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);
  float distance_cm = duration * 0.0343 / 2.0;
  return distance_cm;
}

void loop() {
  
  float f_dist = get_distance(F_TRIG, F_ECHO);
  float l_dist = get_distance(L_TRIG, L_ECHO);

  time=millis();

  Serial.print("f_dist:");
  Serial.println(f_dist);
  Serial.print("  l_dist:");
  Serial.println(l_dist);

  if(f_dist > FD && l_dist < CD){
    move_forward(255);
  }
  if(l_dist>CD){
    turn_left(200);
  } 
  if(l_dist<CD){
    turn_right(200);
  } 
  if(f_dist < CD && l_dist < FD) { //вращение вправо
    Serial.println("ROTATE RIGHT");
    while(millis() - time < ROTATION_TIME){
       rotate_right(255);
    }
    time=millis();
    while(millis() - time < FORWARD_AFTER_ROTATION){
      move_forward(200);
    }
  }
  if(f_dist > FD && l_dist > FD) { //вращение влево
    time=millis();
    while(millis() - time <  FORWARD_BEFORE_ROTATION){
      move_forward(200);
    }
    Serial.println("ROTATE LEFT");
    time=millis();
    while(millis() - time < ROTATION_TIME_LEFT){
       rotate_left(255);
    }
    time=millis();
    while(millis() - time <  FORWARD_AFTER_ROTATION){
      move_forward(200);
    }
  }
 }
