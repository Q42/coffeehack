/* This Arduino sketch is intended for use with coffeemakers with toptronic control (e.g. my Jura Impressa S95) and allows to communicate with the coffeemaker for diagnosis, testing and modifying purposes.
and was written in December 2014 by Oliver Krohn. Serial console should be set to include CR and NL. Hardware needed: Arduino, 4 male/female jumper wires, coffeemaker with service port.
Here are some commands (valid for Jura Impressa S90/95 only! Use at your own risk!):
AN:01 switches coffeemaker on
AN:02 switches coffeemaker off
FA:04 small cup
FA:05 two small cups
FA:06 large cup
FA:07 two large cups
FA:08 steam
FA:09 steam
FA:0C XXL cup
?M1  Inkasso mode off
?M3  Inkasso mode on
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX TX

byte z0;
byte z1;
byte z2;
byte z3;
byte x0;
byte x1;
byte x2;
byte x3;
byte x4;
byte intra = 1;
byte inter = 7;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  
  /*if(Serial.available()) {
    byte c = Serial.read();
    toCoffeemaker(c);
  }*/
  
  toCoffeemaker('I'); delay(inter);
  toCoffeemaker('C'); delay(inter);
  toCoffeemaker(':'); delay(inter);
  toCoffeemaker(0x0D);delay(inter);
  toCoffeemaker(0x0A);delay(inter);

  byte d0; byte d1; byte d2; byte d3;
  while(mySerial.available()) {
    delay (intra); byte d0 = mySerial.read();
    delay (intra); byte d1 = mySerial.read();
    delay (intra); byte d2 = mySerial.read();
    delay (intra); byte d3 = mySerial.read();
    delay (inter);

    // Print hex and bin values of received UART bytes
    //Serial.print(d0, HEX); Serial.print(" ");
    //Serial.print(d1, HEX); Serial.print(" ");
    //Serial.print(d2, HEX); Serial.print(" ");
    //Serial.print(d3, HEX); Serial.print("\t");

    //Serial.print(d0, BIN); Serial.print(" ");
    //Serial.print(d1, BIN); Serial.print(" ");
    //Serial.print(d2, BIN); Serial.print(" ");
    //Serial.print(d3, BIN); Serial.print("\t");
    fromCoffeemaker(d0,d1,d2,d3);
  }
  //Serial.println();
  delay(25);

}

// fromCoffeemaker receives a 4 byte UART package from the coffeemaker and translates them to a single ASCII byte
byte fromCoffeemaker(byte x0, byte x1, byte x2, byte x3) {
  // Print received UART bytes on console
  //    Serial.write(x0);
  //    Serial.write(x1);
  //    Serial.write(x2);
  //    Serial.write(x3);
  //    Serial.println();

  // Reads coding Bits of the 4 byte package and writes them into a new character (translates to ASCII)
  bitWrite(x4, 0, bitRead(x0,2));
  bitWrite(x4, 1, bitRead(x0,5));
  bitWrite(x4, 2, bitRead(x1,2));
  bitWrite(x4, 3, bitRead(x1,5));
  bitWrite(x4, 4, bitRead(x2,2));
  bitWrite(x4, 5, bitRead(x2,5));
  bitWrite(x4, 6, bitRead(x3,2));
  bitWrite(x4, 7, bitRead(x3,5));
  // Print translated ASCII character
  Serial.print(char(x4));
  //Serial.print(x4, BIN);
}

// toCoffeemaker translates an ASCII character to 4 UART bytes and sends them to the coffeemaker
byte toCoffeemaker(byte zeichen) {
  z0 = 255;
  z1 = 255;
  z2 = 255;
  z3 = 255;

  // Reads bits of ASCII byte and writes it into coding bits of 4 UART bytes
  bitWrite(z0, 2, bitRead(zeichen,0));
  bitWrite(z0, 5, bitRead(zeichen,1));
  bitWrite(z1, 2, bitRead(zeichen,2));
  bitWrite(z1, 5, bitRead(zeichen,3));
  bitWrite(z2, 2, bitRead(zeichen,4));
  bitWrite(z2, 5, bitRead(zeichen,5));
  bitWrite(z3, 2, bitRead(zeichen,6));
  bitWrite(z3, 5, bitRead(zeichen,7));

  // Prints hex and bin values of translated UART bytes and the source ASCII character
  //Serial.print(z0, HEX); Serial.print(" ");
  //Serial.print(z1, HEX); Serial.print(" ");
  //Serial.print(z2, HEX); Serial.print(" ");
  //Serial.print(z3, HEX); Serial.print("\t");

  //Serial.print(z0, BIN); Serial.print(" ");
  //Serial.print(z1, BIN); Serial.print(" ");
  //Serial.print(z2, BIN); Serial.print(" ");
  //Serial.print(z3, BIN); Serial.print("\t");

  //Serial.write(zeichen);
  //Serial.println();

  // Sends a 4 byte package to the coffeemaker
  delay (intra); mySerial.write(z0);
  delay (intra); mySerial.write(z1);
  delay (intra); mySerial.write(z2);
  delay (intra); mySerial.write(z3);
  delay(inter);
}
