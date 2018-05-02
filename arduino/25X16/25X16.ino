/*
 * 25x16 flash memory interface.
 * It just reads things.
 */


#include <SPI.h>

void write(int pin,int val){

  if (pin>13) return;
  if (pin<0) return;

  if (pin>7){
    pin=pin-8;
    if (val==1) {
      PORTB |= _BV(pin);
    } else {
      PORTB &= ~_BV(pin);
    }
  } else if (pin<8) {
    if (val==1) {
      PORTD |= _BV(pin);
    } else {
      PORTD &= ~_BV(pin);
    }
  }
}

const int CS = 10;

void setup() {
  
  Serial.begin(9600);
  SPI.begin();
  send(0x03);
  rawsend(0xE00,24);
  Serial.println(val,BIN);

  
}

void loop() {
  
}

void rawsend(addr,bits){
  write(CS,0);
  
}

void send(int address){
  write(CS,0);
  SPI.transfer(address);
  write(CS,1);
}

void tx(int address, int value) {
  write(CS,0);
  SPI.transfer(address);
  SPI.transfer(value);
  write(CS,1);
}

unsigned int rx(int address) {
  unsigned int value;
  byte inByte;
  write(CS,0);
  SPI.transfer(address);
  for (int i=0;i<8;i++) {
    write(13,0);
    delayMicroseconds(3);
    write(13,1);
    inByte = digitalRead(12);
    value = value | (inByte<<i);
    delayMicroseconds(3);
  }
  write(CS,1);
  return value;
}

unsigned int receive(){
  write(CS,0);
  unsigned int inByte;
  unsigned int value;
  for (int i=0;i<8;i++) {
    write(13,0);
    delayMicroseconds(3);
    write(13,1);
    inByte = digitalRead(12);
    value = value | (inByte<<i);
    delayMicroseconds(3);
  }
  return value;
  //write(CS,1);
}

