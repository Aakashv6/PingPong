volatile boolean flag = false;

int t;
float dt;

void setup(){
  Serial.begin(9600);
  
  pinMode(2,INPUT);
  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);

  t = millis();
}

void loop() {
  timer();
}

void isr(){
  flag = true;
}

void timer(){
  if(flag){
    dt = millis() - t;
    Serial.println(dt);
    flag = false;
  }
}
