// 4. Hafta: 1.6. Uygula: Kumanda kolu ve IMU Sensörü ile Servo Motor Kontrolü ( writeMicroSecond() fonksiyonu ile)
#include <Deneyap_Servo.h> // Eğer bu kütüphane çalışmaz ise <ESP32Servo.h> kütüphanesi denenebilir.
#include "lsm6dsm.h"

#define SERVOPIN1 D14
#define SERVOPIN2 D9
#define X_pin A0
#define Y_pin A1

int X_Val, Y_Val;
int dly = 5;
// writeMicroseconds fonksiyonuna girilen değer normal açı değerinden çok yüksek olduğundan stp değeri 10 kat fazla girilir.
int stp = 10; 			
int X_jys=0, Y_jys=0;

int teta1min=0;
int teta1max=3000;		// 180 dereceye karşılık gelmektedir.
int teta2min=0;
int teta2max=3000;
float accAngleX=0.;
float accAngleY=0.;

LSM6DSM IMU;

Servo myservo1;
Servo myservo2;

int pos1 = 1500; 			// 90 dereceye karşılık gelmektedir.
int pos2 = 1500;

void setup() 
{
  IMU.begin();
  myservo1.attach(SERVOPIN1);
  myservo2.attach(SERVOPIN2,1); //Eğer <ESP32Servo.h> kütüphanesi kullanırsanız, bu satırda parantez içerisindeki 2’inci parametreyi silin, tek parametre yeterlidir.

  pinMode(BUILTIN_KEY, INPUT);
  pinMode(X_pin, INPUT);
  pinMode(Y_pin, INPUT);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  digitalWrite(LEDR, LOW);		
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
 }

void loop()
{
  X_Val = analogRead(X_pin);
  Y_Val = analogRead(Y_pin);

  uint8_t buttonState = digitalRead(BUILTIN_KEY);

  if(buttonState == LOW)
  {
    if (dly==5) {
      dly=10;
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, LOW);
    }
    else {
      if(dly==10) {
        dly=20;
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, LOW); 
      }
      else if (dly==20) {
        dly=5;
        digitalWrite(LEDR, LOW);
        digitalWrite(LEDB, HIGH);
      }
    }
    delay(300);
  }
  if (X_Val<1000 && pos1>teta1min) X_jys-=stp;
  if (X_Val>3000 && pos1<teta1max) X_jys+=stp;
  if (Y_Val<1000 && pos2>teta2min) Y_jys-=stp;
  if (Y_Val>3000 && pos2<teta2max) Y_jys+=stp; 

  accAngleX = atan(IMU.readFloatAccelX() / sqrt(pow(IMU.readFloatAccelY(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;
  accAngleY = atan(-1 * IMU.readFloatAccelY() / sqrt(pow(IMU.readFloatAccelX(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;

  // writeMicroseconds fonksiyonu için revize edildi.
  pos1=1500+int(accAngleX*3000./180.)+X_jys;
  pos2=1500+int(accAngleY*3000./180.)+Y_jys;

  myservo1.write(pos1);
  myservo2.write(pos2);

  delay(dly);
}
