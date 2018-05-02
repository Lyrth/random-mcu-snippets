/* 
 * ILI9163 LCD controller interface
 * Datasheet:
 *   https://www.rockbox.org/wiki/pub/Main/SonyNWZE370/ILI9163.pdf
 * 
 * [wire connections to the chip broke, sooo... yeah]
 */


#define D7 B00000001
#define D6 B00000010
#define D5 B00000100
#define D4 B00001000
#define D3 B00010000
#define D2 B00100000
#define D1 B01000000
#define D0 B10000000

#define RD  B000001
#define WR  B000010
#define RS  B000100
#define RST B001000
#define CS  B010000
#define LED B100000

void db(unsigned char x)
{
  byte y = (
            ( (x & (D0)) >> 7 ) |
            ( (x & (D1)) >> 5 ) |
            ( (x & (D2)) >> 3 ) |
            ( (x & (D3)) >> 1 ) |
            ( (x & (D4)) << 1 ) |
            ( (x & (D5)) << 3 ) |
            ( (x & (D6)) << 5 ) |
            ( (x & (D7)) << 7 ) );
  PORTD = x;
};

void lo(unsigned char x) {
  PORTB &= ~(x);
};

void hi(unsigned char x) {
  PORTB |= (x);
};

void cmd(unsigned char x) {
  delay(10);
  lo(RS);
  delay(10);
  lo(WR);
  hi(RD);
  db(x);
  delay(3);
  hi(WR);
  delay(200);
}

void par(unsigned char x) {
  delay(10);
  hi(RS);
  delay(10);
  lo(WR);
  hi(RD);
  db(x);
  delay(3);
  hi(WR);
  delay(200);
}

void dat(unsigned char x,unsigned char y) {
  delay(10);
  hi(RS);
  delay(10);
  
  lo(WR);
  db(x);
  delay(3);
  hi(WR);

  delay(3);

  lo(WR);
  db(x);
  delay(3);
  hi(WR);
  
  delay(200);
}

void setup() {
  // put your setup code here, to run once:
  
  DDRB |= B00111111;
  DDRD |= B11111111;

  db(0);

  hi(RST|CS|RS|RD|WR|LED);
  delay(200);
  lo(RST|LED);
  delay(200);
  hi(RST);
  delay(2000);
  lo(CS);
  lo(LED);
//*/
  cmd(0x01); //SOFTRESET
 
  cmd(0x11); //SLEEPOUT

  cmd(0x28); //DISP 28OFF 29ON
 
  cmd(0x21); //COLORINV 20OFF 21ON
 
  cmd(0x3a); //PIXELFORMAT
  par(0x05);

  cmd(0xc0); //PWRCTRL1
  par(0x0a);
  par(0x02);

  cmd(0xc1); //PWRCTRL2
  par(0x02);

  cmd(0x2a); //2A COL_ADDRESS
  par(0x00); // XSH
  par(0x00); // XSL
  par(0x00); // XEH
  par(0x7f); // XEL (128 pixels x)
   
  cmd(0x2b); //2B PAGE_ADDRESS
  par(0x00);
  par(0x00);
  par(0x00);
  par(0x7f); // 128 pixels y

  cmd(0x36); //2B ADDR_MODE
  par(0x00);
  
  cmd(0x29); //DISP 28OFF 29ON

  cmd(0x2C);

  
//*/

/*/

  db(0xFF);
  delay(1000);
  db(0x00);
  delay(1000);
//*/
  hi(LED);
}

void loop() {
}

