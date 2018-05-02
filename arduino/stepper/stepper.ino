/*
 * What? I'm trying to drive a stepper motor.
 * Apparently, I failed.
 */


char a;
int del = 500;
void setup(){

  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(8,0);
  digitalWrite(9,0);
  digitalWrite(10,0);
  a=1;
}

void loop(){

  delay(del);

  a=a<<1;
  if (a >= 8) {
    a=1;
    del=del-1;
    if (del<=20) {del=20; digitalWrite(13,0);};
    };

  PORTB=(PINB&B11110000)|a;
  
}

