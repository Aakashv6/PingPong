int timing = 1000;
int pin = 8;
boolean turn = true;

void setup() {
  for(int i=8;i<14;i++){
    pinMode(i,OUTPUT);
  }
}

void loop() {

 if(turn){
  left();
 }
 else{
  right();
 }
 
}

void left(){
  digitalWrite(pin,HIGH);
  delay(timing);
  digitalWrite(pin,LOW);
  pin = pin + 1;
  if(pin == 14){
    turn = false;
  }
}

void right(){
  pin = pin - 1;
  digitalWrite(pin,HIGH);
  delay(timing);
  digitalWrite(pin,LOW);
  if(pin == 8){
    turn = true;
  }
}
