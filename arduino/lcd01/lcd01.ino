
/* 
 * Unknown chip, driving a 7 segment LCD and has three pins for interface.
 */

#define CS 7
#define CL 6
#define DA 5

void set(int pin, int val) {
  digitalWrite(pin,val);
}

void setup() {
  // put your setup code here, to run once:
  // digitalWrite(12,1);
  pinMode(13,OUTPUT);
  pinMode(CS,OUTPUT);
  pinMode(CL,OUTPUT);
  pinMode(DA,OUTPUT);
  
  delay(1000);
  set(CS,1);
  set(CL,1);
  set(DA,0);

  delay(1000);
  set(13,1);
  set(CS,0);
  delay(100);
  //set(DA,1);
  //delay(3);
  //set(DA,0);
  //delay(3);
  //set(DA,1);
  //delay(3);
  //set(DA,0);
  //delay(3);
    
    set(DA,1);
    delay(3);
    set(CL,0);
    delay(3);
    set(CL,1);
    delay(3);
    set(DA,0);
    delay(3); 

  set(CS,1);
  delay(3);
  set(DA,1);
  delay(3);
  set(DA,0);
  delay(3);
  set(CS,0);
  delay(3);


  for(int i=0;i<30;i++){
    set(DA,1);
    delay(3);
    set(CL,0);
    delay(3);
    set(CL,1);
    delay(3);
    set(DA,0);
    delay(3);    
  }
  
  set(CS,1);
  delay(3);
  set(DA,1);
  delay(3);
  set(DA,0);
  delay(3);
  set(CS,0);
  delay(3);
  /*for(int i=0;i<160;i++){
    set(CL,0);
    delay(3);
    set(CL,1);
    delay(3);
  }*/
  
  for(int i=0;i<232;i++){
    set(DA,1);
    delay(3);
    set(CL,0);
    delay(3);
    set(CL,1);
    delay(3);
    set(DA,0);
    delay(3);    
  }
/*
  for(int i=0;i<145;i++){
    set(CL,0);
    delay(3);
    set(CL,1);
    delay(3);  
  }
  */
  set(DA,1);
  delay(3);
  set(DA,0);
  delay(100);
  set(CS,1);
  set(13,0);
}



void loop() {
  // put your main code here, to run repeatedly:

}
