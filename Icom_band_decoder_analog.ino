#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//icom band decoder
//Marios Nicolaou 5B4WN (c) 2009 7 24
//Use the code at your OWN risk
//GPL licence

int icomBandPin = 1;    // select the input pin for the potentiometer
int realVoltage = 8;  // variable to store the value coming from the sensor Volts
int sensedVoltage=0;
/*
int D=9;
int C=10;
int B=11;
int A=12;
*/
int AntA=2;
int AntB=3;
int AntC=4;
int AntD=5;
int AntE=6;
int AntF=7;
int AntG=8;
int AntH=9;

float calculatedVoltage=0;
int band=0;
int counter =0;
int previousValue=0;

LiquidCrystal_I2C lcd(0x27,20,4);

 void setup() {
   Serial.begin(9600);
   pinMode(AntA, OUTPUT);
   pinMode(AntB, OUTPUT);
   pinMode(AntC, OUTPUT);
   pinMode(AntD, OUTPUT);
   pinMode(AntE, OUTPUT);
   pinMode(AntF, OUTPUT);
   pinMode(AntG, OUTPUT);
   pinMode(AntH, OUTPUT);

   lcd.init();
   lcd.backlight();
   lcd.clear();

   lcd.setCursor(0, 0);
  lcd.print("  Commutation auto.");
  lcd.setCursor(1, 1);
  lcd.print("d'antenne by F4GMU");
  lcd.setCursor(0, 2);
  lcd.print("Bande:");
  lcd.setCursor(0, 3);
  lcd.print("Antenne: ");
  lcd.setCursor(13, 3);
  lcd.print("/F4JND");
  
 }
 void loop() {
   // read the value from the sensor:
   sensedVoltage = analogRead(icomBandPin);    
   
   
   //get 5 consecutive values
//  counter++;
   
   if (counter==5) {
   
   calculatedVoltage = float(sensedVoltage)*5/1024;
   
   Serial.print (sensedVoltage);
   Serial.print (" - ");
   Serial.print (calculatedVoltage);
   Serial.println (" - ");
   band=getBand(calculatedVoltage);
   
   Serial.println(band, DEC);
   delay (1000);
                  
 } else {
   if (abs(previousValue-sensedVoltage)>10) {
    //means change or spurious number
     previousValue=sensedVoltage;
   } else {
     counter++;
     previousValue=sensedVoltage;
   }
   
   
 }
 
}
 
int  getBand(float voltage) {
   int band=0;

 
if (voltage>3.5 && voltage<4.3) {
 band=160;
 digitalWrite(AntA, LOW);
 digitalWrite(AntB, HIGH);
 digitalWrite(AntC, HIGH);
 digitalWrite(AntD, HIGH);
 digitalWrite(AntE, HIGH);
 digitalWrite(AntF, HIGH);
 digitalWrite(AntG, HIGH);
 digitalWrite(AntH, HIGH);
 Serial.println("160 ");
 lcd.setCursor(7, 2);
 lcd.print("160 metres");
 lcd.setCursor(9, 3);
 lcd.print("A");
 
} else if (voltage>3 && voltage<3.4) {
 band=80;
 digitalWrite(AntA, HIGH);
 digitalWrite(AntB, LOW);
 digitalWrite(AntC, HIGH);
 digitalWrite(AntD, HIGH);
 digitalWrite(AntE, HIGH);
 digitalWrite(AntF, HIGH);
 digitalWrite(AntG, HIGH);
 digitalWrite(AntH, HIGH);
 Serial.println("80 ");
 lcd.setCursor(7, 2);
 lcd.print(" 80 metres");
 lcd.setCursor(9, 3);
 lcd.print("B");

} else if (voltage>=2.3 && voltage<3.3) {
  band=40;
 digitalWrite(AntA, HIGH);
 digitalWrite(AntB, HIGH);
 digitalWrite(AntC, LOW);
 digitalWrite(AntD, HIGH);
 digitalWrite(AntE, HIGH);
 digitalWrite(AntF, HIGH);
 digitalWrite(AntG, HIGH);
 digitalWrite(AntG, HIGH);
 Serial.println("40 ");
 lcd.setCursor(7, 2);
 lcd.print(" 40 metres");
 lcd.setCursor(9, 3);
 lcd.print("C");

} else if(voltage>=1.9 && voltage<2.25) {
  band=20;
 digitalWrite(AntA, HIGH);
 digitalWrite(AntB, HIGH);
 digitalWrite(AntC, HIGH);
 digitalWrite(AntD, HIGH);
 digitalWrite(AntE, LOW);
 digitalWrite(AntF, HIGH);
 digitalWrite(AntG, HIGH);
 digitalWrite(AntH, HIGH);
 Serial.println("20 ");
 lcd.setCursor(7, 2);
 lcd.print(" 20 metres");
 lcd.setCursor(9, 3);
 lcd.print("E");
 
} else if (voltage>=1.4 && voltage<1.8) {
  band=15;
 digitalWrite(AntA, HIGH);
 digitalWrite(AntB, HIGH);
 digitalWrite(AntC, HIGH);
 digitalWrite(AntD, HIGH);
 digitalWrite(AntE, HIGH);
 digitalWrite(AntF, LOW);
 digitalWrite(AntG, HIGH);
 digitalWrite(AntH, HIGH);
 Serial.println("15 ");
 lcd.setCursor(7, 2);
 lcd.print(" 15 metres");
 lcd.setCursor(9, 3);
 lcd.print("F");
 
} else if (voltage>=1.0 && voltage<1.3) {
  band=10;
 digitalWrite(AntA, HIGH);
 digitalWrite(AntB, HIGH);
 digitalWrite(AntC, HIGH);
 digitalWrite(AntD, HIGH);
 digitalWrite(AntE, HIGH);
 digitalWrite(AntF, HIGH);
 digitalWrite(AntG, LOW);
 digitalWrite(AntH, HIGH);
 Serial.println("10 ");
 lcd.setCursor(7, 2);
 lcd.print(" 10 metres");
 lcd.setCursor(9, 3);
 lcd.print("G");

} else if (voltage>=0.85 && voltage<0.99) {
  band=6;
 digitalWrite(AntA, HIGH);
 digitalWrite(AntB, HIGH);
 digitalWrite(AntC, HIGH);
 digitalWrite(AntD, HIGH);
 digitalWrite(AntE, HIGH);
 digitalWrite(AntF, HIGH);
 digitalWrite(AntG, HIGH);
 digitalWrite(AntH, LOW);
 Serial.println("6 ");
 lcd.setCursor(7, 2);
 lcd.print("  6 metres");
 lcd.setCursor(9, 3);
 lcd.print("H");

} else if (voltage  <0.5) {
  band=30;
 digitalWrite(AntA, HIGH);
 digitalWrite(AntB, HIGH);
 digitalWrite(AntC, HIGH);
 digitalWrite(AntD, LOW);
 digitalWrite(AntE, HIGH);
 digitalWrite(AntF, HIGH);
 digitalWrite(AntG, HIGH);
 digitalWrite(AntH, HIGH);
 Serial.println("30 ");
 lcd.setCursor(7, 2);
 lcd.print(" 30 metres");
 lcd.setCursor(9, 3);
 lcd.print("D");
}
 return band;
 
}