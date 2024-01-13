// 3. Hafta: 1.4. Uygula: IMU Sensörü Değerlerinin Ekrana Yazdırılması
#include "lsm6dsm.h"

LSM6DSM IMU;

void setup() 
{
  Serial.begin(115200);
  IMU.begin();
 }

void loop()
{
  Serial.print("accel_x: ");
  Serial.println(IMU.readFloatAccelX());
  Serial.print("accel_y: ");
  Serial.println(IMU.readFloatAccelY());
  Serial.print("accel_z: ");
  Serial.println(IMU.readFloatAccelZ());
  delay(500); 
}
