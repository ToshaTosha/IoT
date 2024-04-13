#define forward 2
#define backward 4

void setup()
{
  pinMode(forward, OUTPUT);
  pinMode(backward,OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter direction and speed separated by a space");
  Serial.println("f - forward; b - backward");
  Serial.println("speed in range [0; 255]");
}

void motor_control(String direction, int speed){
  if(direction == "f"){
  	analogWrite(backward, 0);
  	analogWrite(forward, speed);
    
  }else if(direction == "b"){
    analogWrite(forward, 0);
  	analogWrite(backward, speed);
  }
}

void loop()
{
  if(Serial.available()){
  	String user_input = Serial.readString();
    Serial.println(user_input);

    String direction = user_input.substring(0,1);
    user_input.remove(0,2);
    int speed = user_input.toInt();

    if(direction != "f" and direction != "b"){
    	Serial.println("Unknown direction");
    }else if(speed>255 || speed<0){
    	Serial.println("Speed must be in range [0; 255]");
    }else{
    	motor_control(direction, speed);
    }
  }
}
