// 4. Hafta: 1.5. Uygula: IMU Sensörü ile Çift Servo Motor Konum Kontrolü
#include <Deneyap_Servo.h>
#include "lsm6dsm.h"

#define SERVOPIN1 D14
#define SERVOPIN2 D9

LSM6DSM IMU;

Servo myservo1;
Servo myservo2;

float accAngleX=0.;
float accAngleY=0.;
int pos1 = 90;
int pos2 = 90;

void setup() 
{
  IMU.begin();
  myservo1.attach(SERVOPIN1);
  myservo2.attach(SERVOPIN2,1);
 }

void loop()
{
  accAngleX = atan(IMU.readFloatAccelX() / sqrt(pow(IMU.readFloatAccelY(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;
  accAngleY = atan(-1 * IMU.readFloatAccelY() / sqrt(pow(IMU.readFloatAccelX(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;

  pos1=90+int(accAngleX);
  pos2=90+int(accAngleY);

  myservo1.write(pos1);
  myservo2.write(pos2);
  delay(10);
}
// NOT: Programın Deneyap Geliştirme Kartına yüklemesi bittiğinde motorların IMU sensöründen gelen değerlere göre davranış gösterdiği görülecektir. 
// Basit bir gimbal uygulaması olarak, çift motorlu mekanizmanın gülen yüzlü yüzeyi her zaman yukarı yöne bakacaktır. 
