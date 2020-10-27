volatile boolean state = LOW;
int a,b;
void setup() {
  pinMode(13,OUTPUT);
  pinMode(2,INPUT);
  attachInterrupt(digitalPinToInterrupt(2), player1, RISING);
}

void loop() {
}

void player1(){
  state = !state;
  digitalWrite(13,state);
}
