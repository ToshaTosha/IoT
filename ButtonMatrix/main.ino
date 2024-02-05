//unsigned long lastDebounceTime = 0; // последнее время
//unsigned long debounceDelay = 50; // задержка
int buttonStates[2][2]={ //состояния кнопок
   {0, 0}, //1 2
   {0, 0}  //3 4
};

void setup() {
  	pinMode(8, OUTPUT);
  	pinMode(9, OUTPUT);
  	pinMode(10, INPUT_PULLUP);
  	pinMode(11, INPUT_PULLUP);
    Serial.begin(9600);
}

void clear_states(){
  for(int i = 0; i < 2; i++){
      for(int j = 0; j < 2; j++){
        buttonStates[i][j]= 0;
      }
    }
}

bool is_any_button_pressed(){
  for(int i = 0; i < 2; i++){
      for(int j = 0; j < 2; j++){
        if(buttonStates[i][j] == 1){
          return true;
        }
      }
    }
  return false;
}

void print_button_states(){
  //распечатать какие из кнопок нажаты
  //если ни одна не нажата то ничего не выводить
  if(is_any_button_pressed()){
  	Serial.println("---Buttons states---");
    for(int i = 0; i < 2; i++){
      for(int j = 0; j < 2; j++){
        Serial.print(buttonStates[i][j]);
        Serial.print(" ");
      }
      Serial.println();
    }
  }
}

void loop() {
  
  for(int i = 0; i < 2; i++){
    digitalWrite(8, i);
    digitalWrite(9, abs(i-1));
    
    //выводит все 1(((((((((
  	/*if(digitalRead(10) == LOW){//btn1 or btn3 
      buttonStates[i][0] = 1; //нажата
    }else{
      buttonStates[i][0] = 0; //не нажата
    }
    
  	if(digitalRead(11) == LOW){//btn2 or btn4
      buttonStates[i][1] = 1; 
    }else{
      buttonStates[i][1] = 0; 
    }*/
  }
  
  print_button_states();
  clear_states();
  delay(100);
}
