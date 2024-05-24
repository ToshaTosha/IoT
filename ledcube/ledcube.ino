int rows[] = {2, 3};
int columns[] = {4, 5, 6, 7};

int size = sizeof(rows) / sizeof(rows[0]);
int delay_time=700;

void setup() {
  Serial.begin(9600);
  for (int i=2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
  
  switch_leds();
}

void rows_off(){
  digitalWrite(rows[0], LOW);
  digitalWrite(rows[1], LOW);
}

void columns_on(){
  for (int j = 0; j < 4; j++) {
    digitalWrite(columns[j], HIGH);
  }
}
void columns_off(){
  for (int j = 0; j < 4; j++) {
    digitalWrite(columns[j], LOW);
  }
}

void one_led(int state1, int state2){
    digitalWrite(rows[0], state1);
    digitalWrite(rows[1], state2);
    for(int j = 0; j < size*2; j++){
      digitalWrite(columns[0], j == 0 ? LOW:HIGH);
      digitalWrite(columns[1], j == 1 ? LOW:HIGH);
      digitalWrite(columns[2], j == 2 ? LOW:HIGH);
      digitalWrite(columns[3], j == 3 ? LOW:HIGH);
      delay(delay_time);
    }
    rows_off();
}

void two_leds(int state1, int state2){
  
  // ДОБАВИТЬ ДИАГОНАЛЬ///
    digitalWrite(rows[0], state1);
    digitalWrite(rows[1], state2);
    for(int j = 0; j < size*2; j++){
      int j2=0;
      if(j+1 != size*2){
        j2=j+1;
      }
      digitalWrite(columns[j],LOW);
      digitalWrite(columns[j2],LOW);
      delay(delay_time);
      digitalWrite(columns[j],HIGH);
      digitalWrite(columns[j2],HIGH);
    }
    rows_off();
}

void three_leds(int state1, int state2){
	for (int c = 0; c < size*2; c++) {
      digitalWrite(rows[0], state1);
      digitalWrite(rows[1], state2);
      
      for (int j = 0; j < size*2; j++) {
        digitalWrite(columns[j], c == j ? HIGH:LOW);
      }
      delay(delay_time);
      rows_off();
    }
}

void all(int state1, int state2){
   digitalWrite(rows[0], state1);
   digitalWrite(rows[1], state2);
   delay(delay_time);
   rows_off();
}

void switch_leds(){
  //1
  one_led(1,0);
  one_led(0,1);
  one_led(1,1);
  columns_on();
  
  //2
  two_leds(1,0);
  two_leds(0,1);
  two_leds(1,1);
  columns_on();
  
  //3
  three_leds(1,0);
  three_leds(0,1);
  three_leds(1,1);
  columns_off();
  
  //4
  all(1,0);
  all(0,1);
  all(1,1);
  
}

void loop() {
  
  
}
