/* 
 * An attempt to interface with the Avago ADNS-7050 optical sensor.
 * Datasheet found here:
 *   http://www.efo.ru/components/avago/catalog/files/pdf/AV01-0036EN.pdf
 * 
 * [Discontinued]
 */

 
#define STB 12 //NCS   - Gray
#define DO 11  //MISO  - Blue
#define CLK 10 //SCLK  - Yellow
#define DI 9   //MOSI  - Orange
#define MOT 8  //MOT   - Brown

void setup() {
  digitalWrite(2,LOW);
  digitalWrite(13,0);
  Serial.begin(9600);
  int i;
  unsigned int ret;
  pinMode(DO,OUTPUT);
  pinMode(DI,INPUT);
  pinMode(CLK,OUTPUT);
  pinMode(STB,OUTPUT);
  pinMode(MOT,INPUT);

  delay(1000);
  digitalWrite(STB,HIGH);
  digitalWrite(2,HIGH);
  delay(1000);
  digitalWrite(STB,LOW);
  delay(1000); /*
  tx(0x3A,0x5a);
  delay(2000);
  tx(0x28,0xfe);
  rx(2);
  rx(3);
  rx(4);
  delay(1000);
  // digitalWrite(CLK,HIGH);

*/
  ret = rx(0);
  Serial.println(ret);
  Serial.println(digitalRead(MOT));
  digitalWrite(STB,HIGH);

  delay(10);
  digitalWrite(13,1);
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

void tx(unsigned int addr,unsigned int data){
  delayMicroseconds(30);
  for(byte i=0;i<8;i++){
    if( (1<<i) & addr ) digitalWrite(DI,HIGH); else digitalWrite(DI,LOW);
     delayMicroseconds(3);
     digitalWrite(CLK,LOW); 
     delayMicroseconds(3);
     digitalWrite(CLK,HIGH); 
     delayMicroseconds(3);
  }
  for(byte i=0;i<8;i++){
    if( (1<<i) & data ) digitalWrite(DI,HIGH); else digitalWrite(DI,LOW);
     delayMicroseconds(3);
     digitalWrite(CLK,LOW); 
     delayMicroseconds(3);
     digitalWrite(CLK,HIGH); 
     delayMicroseconds(3);
  }
  delayMicroseconds(30);
}

unsigned int rx(unsigned int addr){
  unsigned int value=0;
  unsigned int naddr;
  /*
  for(byte i=0;i<8;i++){
    // naddr=naddr + (( (1<<i) & addr )<<(7-i)) ;
    if( (1<<i) & addr ) {
      naddr=naddr + (1<<(7-i));
    }
  }
  Serial.println("/ / /");
  Serial.println(addr,BIN);
  Serial.println("/ / /");
  Serial.println(naddr,BIN);
  Serial.println("/ / /");
  */ //
  
  delayMicroseconds(30);
  for(byte i=0;i<8;i++){
    if( (B10000000>>i) & addr ) {
      digitalWrite(DI,HIGH); 
      Serial.print("1");
      }
      else {
        digitalWrite(DI,LOW);
        Serial.print("0");
      }
    
     delayMicroseconds(3);
     digitalWrite(CLK,LOW); 
     delayMicroseconds(3);
     digitalWrite(CLK,HIGH); 
     delayMicroseconds(3);
  }
  delayMicroseconds(30);
  for(byte i=0;i<8;i++){ //shift out
     digitalWrite(CLK,LOW); 
     delayMicroseconds(3);
     digitalWrite(CLK,HIGH);
     delayMicroseconds(3);
     if(digitalRead(DO) == HIGH) value += 1<<i; //sample PGD
     delayMicroseconds(3);
  }
  Serial.println(" ");
  delayMicroseconds(30);
  return value;
}



