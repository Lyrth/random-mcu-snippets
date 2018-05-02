/* 
 * PT6313. Supposed to be a vacuum fluorescent driver, but I think
 * thos would also work with LED segdisplays with resistors :D
 *
 * Datasheet:
 *   http://www.ic72.com/pdf_file/p/63821.pdf
 */


#define DIO 2
#define CLK 3
#define STB 4

void setup() {
  int i;
  
  pinMode(A0,OUTPUT);
  pinMode(DIO,OUTPUT);
  pinMode(CLK,OUTPUT);
  pinMode(STB,OUTPUT);
  digitalWrite(STB,HIGH);
  digitalWrite(CLK,HIGH);
  digitalWrite(A0,HIGH);
  
  delay(200);
  
  digitalWrite(STB,LOW);
  
  tx(B01000000);        //Data Set
  strobe();

/////////////////
  tx(B11000000);        //Addr. Set
  
  digitalWrite(A0,LOW);
  for(i=0;i<14;i++){   //Reset
    delay(100);
    tx(B00000000);
  }
  strobe();
/////////////////
  tx(B11000000);        //Addr. Set
  
  
  for(i=0;i<14;i++){   //Set
    digitalWrite(A0,HIGH);
    delay(500);
    tx(B11111111);
    digitalWrite(A0,LOW);
    delay(500);
  }
  strobe();
  digitalWrite(A0,HIGH);
//////////////////
  tx(B00000010);        //Disp. Mode
  strobe();
  
  
  
  tx(B10001111);        //Disp. Ctrl.
  strobe();
  
  delay(1000);
  
  tx(B10001000);        //Disp. Ctrl.
  strobe();
  
  delay(1000);
  
  //tx(B10000000);        //Disp. Ctrl.
  //strobe();

  digitalWrite(STB,HIGH);
  
  
  digitalWrite(A0,LOW);
}

void loop() {

}

void strobe(){
  delayMicroseconds(3);
  digitalWrite(CLK,HIGH);
  delayMicroseconds(3);
  digitalWrite(STB,HIGH);
  delayMicroseconds(3);
  digitalWrite(STB,LOW);
}

void tx(unsigned int data){
  delayMicroseconds(3);
  for(byte i=0;i<8;i++){
    if( (1<<i) & data ) digitalWrite(DIO,HIGH); else digitalWrite(DIO,LOW);
     digitalWrite(CLK,LOW);
     delayMicroseconds(3);
     digitalWrite(CLK,HIGH);
     delayMicroseconds(3);
  }

}
