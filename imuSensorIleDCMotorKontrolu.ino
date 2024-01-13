// 3. Hafta: 1.6. Uygula: IMU Sensörü ile DC Motor Kontrolü
#include "lsm6dsm.h"
#define MOT_ENA   D12      // Motor hız kontrol pini
#define MOT_DIR1  D13      // Motor yon secme pin1
#define MOT_DIR2  D14      // Motor yon secme pin2

float angle_x=0.; 		//x açısı

int hiz=0;  			
LSM6DSM IMU;  		//Deneyap Geliştirme Kartı üzerinde bulunan IMU sensörü modeli
void setup() {  
IMU.begin();
  pinMode(MOT_ENA, OUTPUT);         // Motor hız kontrol pini cikis olarak ayarlandi
  pinMode(MOT_DIR1, OUTPUT);        // Motor yon secme pin1 cikis olarak ayarlandi
  pinMode(MOT_DIR2, OUTPUT);        // Motor yon secme pin2 cikis olarak ayarlandi
}
void loop() {
//açı hesaplama denklemi (sqrt: karekök alma işlemi, pow: üs alma işlemi, PI: pi (π) sayısı)
angle_x = atan(IMU.readFloatAccelX() / sqrt(pow(IMU.readFloatAccelY(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;    
hiz= abs(angle_x);
    if(angle_x > 0)               // Ileri yon
  {   
    digitalWrite(MOT_DIR1, HIGH);
    digitalWrite(MOT_DIR2, LOW);    
  }
  else if(angle_x < 0)          // Geri yon
  {
    digitalWrite(MOT_DIR1, LOW);
    digitalWrite(MOT_DIR2, HIGH);
  }
  
  digitalWrite(MOT_ENA, LOW);
  delay(100/hiz);
  digitalWrite(MOT_ENA, HIGH);
  delay(100/hiz);   
} 
