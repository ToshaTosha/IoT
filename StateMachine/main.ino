// 4, 7 for direction
// 5, 6 for speed

//возможно придется подобрать константы (поменять high и low местами)
#define DIR_RIGHT 4 // HIGH - forward; LOW - back
#define SPEED_RIGHT 5
#define DIR_LEFT 7 // HIGH - forward; LOW - back
#define SPEED_LEFT 6

#define TRIG 9
#define ECHO 8

int counter = 0;
int FD = 30;//
int CD = 15;//

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
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
void move_back(int velocity){
  move(false, false, velocity, velocity);
}

void rotate_left(int velocity){
  move(false, true, velocity, velocity);
}

void rotate_right(int velocity){
  move(true, false, velocity, velocity);
}

void stop(){
  move(false, true, 0, 0);
}

float get_distance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  unsigned long duration = pulseIn(ECHO, HIGH);
  float distance_cm = duration * 0.0343 / 2.0;
  return distance_cm;
}

void loop() {
  //float distance = get_distance();
  /*if(distance > CD){

  }*/
  Serial.println(counter - millis());
  if (millis() - counter < 1250) {
    rotate_left(255);
  } else {
    stop();
  }

}
