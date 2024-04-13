// 4, 7 for direction
// 5, 6 for speed

//возможно придется подобрать константы (поменять high и low местами)
#define DIR_RIGHT 4 // HIGH - forward; LOW - back
#define SPEED_RIGHT 5
#define DIR_LEFT 7 // HIGH - forward; LOW - back
#define SPEED_LEFT 6

//передний датчик
#define F_TRIG 9
#define F_ECHO 8

//левый датчик
#define L_TRIG 11
#define L_ECHO 10

int counter = 0;
int FD = 30;//
int CD = 15;//

void setup() {
  Serial.begin(9600);
  
  pinMode(F_TRIG, OUTPUT);
  pinMode(F_ECHO, INPUT);
  pinMode(L_TRIG, OUTPUT);
  pinMode(L_ECHO, INPUT);
  for (int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
  counter = millis();
}

void move(bool lforward, bool rforward, int lvelocity, int rvelocity){
  digitalWrite(DIR_RIGHT, rforward);
  digitalWrite(DIR_LEFT, lforward);
  analogWrite(SPEED_RIGHT, rvelocity);
  analogWrite(SPEED_LEFT, lvelocity);
}

void move_forward(int velocity){
  move(true, true, velocity, velocity);
}
/*void move_back(int velocity){
  move(false, false, velocity, velocity);
}*/

void rotate_left(int velocity){
  move(false, true, velocity, velocity);
}

void rotate_right(int velocity){
  move(true, false, velocity, velocity);
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
  Serial.print("f_dist:");
  Serial.print(f_dist);
  Serial.print("  l_dist:");
  Serial.println(l_dist);
  /*if(distance > CD){

  }*/
  Serial.println(counter - millis());
  if (millis() - counter < 1250) {
    rotate_left(255);
  } else {
    stop();
  }

}
