// #include <SoftwareSerial.h>
// SoftwareSerial mySerial(10, 11); // RX TX

#ifndef bitRead
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#endif

byte z0, z1, z2, z3;
byte x0, x1, x2, x3, x4;
byte d0, d1, d2, d3;
byte intra = 1, inter = 7;
String hexval;

// TODO: melkkoffie, twee koffie, twee espressi
// TODO: make this an array and iterate all functions over it
int t_koffie, t_ristretto, t_cappuccino, t_espresso, t_latte_macchiato, t_macchiato;
int o_koffie, o_ristretto, o_cappuccino, o_espresso, o_latte_macchiato, o_macchiato;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Starting Q42 coffeehacker");
}

int getCounter(int offset)
{
  if(offset > 0x800) return -1;

  hexval = String(offset, HEX);
  while(hexval.length() < 3) hexval = "0" + hexval;

  toCoffeemaker('R'); delay(inter);
  toCoffeemaker('E'); delay(inter);
  toCoffeemaker(':'); delay(inter);
  toCoffeemaker('0'); delay(inter);
  toCoffeemaker(hexval[0]); delay(inter);
  toCoffeemaker(hexval[1]); delay(inter);
  toCoffeemaker(hexval[2]); delay(inter);
  toCoffeemaker(0x0D); delay(inter);
  toCoffeemaker(0x0A); delay(100);

  String r = "";

  while(Serial1.available()) {
    delay (intra); d0 = Serial1.read();
    delay (intra); d1 = Serial1.read();
    delay (intra); d2 = Serial1.read();
    delay (intra); d3 = Serial1.read();
    delay (inter);
    r += char(fromCoffeemaker(d0,d1,d2,d3));
  }

  if (r.length() == 9) {
    String hex = r.substring(3,7);
    int number = (int)strtol(hex.c_str(), NULL, 16);
    return number;
  } else {
    return -1;
  }
}

void loop() {
  o_koffie = t_koffie;
  o_ristretto = t_ristretto;
  o_cappuccino = t_cappuccino;
  o_espresso = t_espresso;
  o_latte_macchiato = t_latte_macchiato;
  o_macchiato = t_macchiato;

  Serial.println("------ reading values");
  t_koffie = getCounter(0x282);
  t_ristretto = getCounter(0x281);
  t_cappuccino = getCounter(0x284);
  t_espresso = getCounter(0x280);
  t_latte_macchiato = getCounter(0x285);
  t_macchiato = getCounter(0x286);

  Serial.print("koffie:.........."); Serial.println(t_koffie);
  Serial.print("cappuccino:......"); Serial.println(t_cappuccino);
  Serial.print("espresso:........"); Serial.println(t_espresso);
  Serial.print("ristretto:......."); Serial.println(t_ristretto);
  Serial.print("latte macchiato:."); Serial.println(t_latte_macchiato);
  Serial.print("macchiato:......."); Serial.println(t_macchiato);

  if(t_koffie == o_koffie + 1) trigger("koffie");
  if(t_ristretto == o_ristretto + 1) trigger("ristretto");
  if(t_cappuccino == o_cappuccino + 1) trigger("cappuccino");
  if(t_espresso == o_espresso + 1) trigger("espresso");
  if(t_latte_macchiato == o_latte_macchiato + 1) trigger("latte_macchiato");
  if(t_macchiato == o_macchiato + 1) trigger("macchiato");

  delay(5 * 1000);
}

void trigger(String ctype)
{
  Serial.println(" -- triggering webhook for a " + ctype);
  Spark.publish("coffeecups", ctype, 60, PRIVATE);
}

byte fromCoffeemaker(byte x0, byte x1, byte x2, byte x3) {
  bitWrite(x4, 0, bitRead(x0,2));
  bitWrite(x4, 1, bitRead(x0,5));
  bitWrite(x4, 2, bitRead(x1,2));
  bitWrite(x4, 3, bitRead(x1,5));
  bitWrite(x4, 4, bitRead(x2,2));
  bitWrite(x4, 5, bitRead(x2,5));
  bitWrite(x4, 6, bitRead(x3,2));
  bitWrite(x4, 7, bitRead(x3,5));
  return x4;
}

byte toCoffeemaker(byte z) {
  z0 = 255;
  z1 = 255;
  z2 = 255;
  z3 = 255;

  bitWrite(z0, 2, bitRead(z,0));
  bitWrite(z0, 5, bitRead(z,1));
  bitWrite(z1, 2, bitRead(z,2));
  bitWrite(z1, 5, bitRead(z,3));
  bitWrite(z2, 2, bitRead(z,4));
  bitWrite(z2, 5, bitRead(z,5));
  bitWrite(z3, 2, bitRead(z,6));
  bitWrite(z3, 5, bitRead(z,7));

  delay(intra); Serial1.write(z0);
  delay(intra); Serial1.write(z1);
  delay(intra); Serial1.write(z2);
  delay(intra); Serial1.write(z3);
  delay(inter);
}
