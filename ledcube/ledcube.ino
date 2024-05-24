int rows[] = {2, 3};
int columns[] = {4, 5, 6, 7};

void setup() {
  Serial.begin(9600);
  for (int i=2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
  int delay_time=200;
  int size = sizeof(rows) / sizeof(rows[0]);
  switch_leds(size, delay_time);
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
void switch_leds(int size, int delay_time){
  //1 слой 1 светодиод
  for(int i = 0; i < size; i++){
    digitalWrite(rows[i], HIGH);
    for(int j = 0; j < size*2; j++){
      digitalWrite(columns[0], j == 0 ? LOW:HIGH);
      digitalWrite(columns[1], j == 1 ? LOW:HIGH);
      digitalWrite(columns[2], j == 2 ? LOW:HIGH);
      digitalWrite(columns[3], j == 3 ? LOW:HIGH);
      delay(delay_time);
    }
    digitalWrite(rows[i], LOW);    
  }
  columns_on();
  
  //по 2, 1 слой
  for (int i = 0; i < size; i++) {
    digitalWrite(rows[i], HIGH);
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
    
    digitalWrite(rows[i], LOW);
  }
  columns_on();
  //по 3, 1 слой
  for (int r = 0; r < size; r++) {
    for (int c = 0; c < size*2; c++) {
      for (int i = 0; i < size; i++) {
        digitalWrite(rows[i], r == i ? HIGH:LOW);
      }
      for (int j = 0; j < size*2; j++) {
        digitalWrite(columns[j], c == j ? HIGH:LOW);
      }
      delay(delay_time);
      columns_off();
    }
  }
  
  
  //все
   digitalWrite(rows[0], HIGH);
   digitalWrite(rows[1], LOW);
   delay(delay_time);
   digitalWrite(rows[1], HIGH);
   digitalWrite(rows[0], LOW);
   delay(delay_time);
   digitalWrite(rows[0], HIGH);
}

void all_combinations(){
  
}

void loop() {
  
  
}
