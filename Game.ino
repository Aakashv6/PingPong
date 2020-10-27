#include <avr/interrupt.h>

volatile boolean start = true;
volatile boolean prev_serve = true;

int timing = 1000;
int react_time = 1000;

void setup() {
  pinMode(2,INPUT);
  pinMode(3,INPUT);

  EIFR |= (1 << INTF0);
  attachInterrupt(digitalPinToInterrupt(2), player1, RISING);
  
  for(int i=8;i<14;i++){
    pinMode(i,OUTPUT);
  }
}

void loop() {
  game();
}

// Game logic
void game(){

  // Start state
  if(start){
    digitalWrite(13,HIGH);
  }

  // Player 1 -- serves right --pin 2
  else{
     detachInterrupt(digitalPinToInterrupt(2));
     
     if(!start && prev_serve){
      right();

      EIFR |= (1 << INTF1);
      attachInterrupt(digitalPinToInterrupt(3), player2, RISING);
      delay(react_time);
      detachInterrupt(digitalPinToInterrupt(3));
      
      if(prev_serve){
        reset();
      }
    }
    
    // Player 2 -- serves left --pin 3
    else{
      left();

      EIFR |= (1 << INTF0);
      attachInterrupt(digitalPinToInterrupt(2), player1, RISING); 
      delay(react_time);
      detachInterrupt(digitalPinToInterrupt(2));
      
      if(!prev_serve){
        reset();
      }
    }   
  }
  
}

// Interrupts
void player1(){
  start = false;
  prev_serve = true;
}

void player2(){
  prev_serve = false;
}

// Pong dynamics
void left(){

  for(int i=8;i<13;i++){
    digitalWrite(i,HIGH);
    delay(timing);
    digitalWrite(i,LOW);
  }

}

void right(){

  for(int i=13;i>8;i--){
    digitalWrite(i,HIGH);
    delay(timing);
    digitalWrite(i,LOW);
  }

}

// Game Reset
void reset(){

  timing = 50;
  
  if(prev_serve){
    right();
    left();
    
    for(int i=0;i<4;i++){
      digitalWrite(13,HIGH);
      delay(100);
      digitalWrite(13,LOW);
      delay(100);
    }
  }
  
  if(!prev_serve){
    left();
    right();       
    
    for(int i=0;i<4;i++){
      digitalWrite(8,HIGH);
      delay(100);
      digitalWrite(8,LOW);
      delay(100);
    }
  }
    timing = 1000;
    start = true;

    EIFR |= (1 << INTF0);
    attachInterrupt(digitalPinToInterrupt(2), player1, RISING);
}
