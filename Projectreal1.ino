int num = 0;

const int led1 = 2;
const int led2 = 3;

#include <Servo.h>
Servo servo1;

const int sencer = 8;

#include <TM1637Display.h>
#define cio 6
#define dlk 7
TM1637Display display(cio,dlk);

const int trigpin = 4;
const int esho = 5;

#include <DHT.h>
#define dhtpin 12
#define dhttype DHT11
DHT dht(dhtpin, dhttype);

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int sunsenser = 11;
int val = 0;


void setup(){
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  servo1.attach(9);
  pinMode(sencer, INPUT);

  display.setBrightness(0x0f);

  pinMode(trigpin, OUTPUT);
  pinMode(esho, INPUT);

  dht.begin();
  
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

pinMode(sunsenser,INPUT);

}

void loop() {

SenserAll();

val = digitalRead(sunsenser);
if (val == HIGH){
  digitalWrite(led1,1);
    servo1.write(0);
    delay(300);
    servo1.write(180);
    delay(300);
}
else {
  digitalWrite(led1,0);
}
delay(1000);

}

// void Servospeed(){
//   for (int pos = 0; pos<= 180; pos+=3){
//   servo1.write(pos);
//   delay(100);
//   }
//   for (int pos = 180; pos >= 0; pos -=3){
//   servo1.write(pos);
//   delay(100);
//   }
// }
void SenserAll(){


  int runsencer = digitalRead(sencer);
  if (runsencer == LOW) {
    digitalWrite(led1, 0);
    num++;
    display.showNumberDec(num, true);
  } else {
    digitalWrite(led2, 1);
    digitalWrite(led1, 0);
  }
  digitalWrite(trigpin, LOW);
  delayMicroseconds(20);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(60);
  digitalWrite(trigpin, LOW);
  delayMicroseconds(20);

  long T1 = pulseIn(esho, HIGH);
  long T2 = T1 * 0.034 / 2;
lcd.print(T2);
lcd.print("Cm and ");

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  if (isnan(temp) || isnan(hum)) {
    Serial.println("is not a number");
  }
  Serial.print(hum);
lcd.print(temp);
lcd.print("C");
  delay(1000);
}
