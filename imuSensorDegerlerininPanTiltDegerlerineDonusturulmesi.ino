// 3. Hafta: 1.5. Uygula: IMU Sensör Değerlerinin Pan-Tilt Açı Değerlerine Dönüştürülmesi
#include "lsm6dsm.h"

LSM6DSM IMU;

float accAngleX;
float accAngleY;

void setup() 
{
  Serial.begin(115200);
  IMU.begin();
}

void loop()
{
  accAngleX = atan(IMU.readFloatAccelX() / sqrt(pow(IMU.readFloatAccelY(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;
  accAngleY = atan(-1 * IMU.readFloatAccelY() / sqrt(pow(IMU.readFloatAccelX(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;

  Serial.print("accAngleX: ");
  Serial.println(accAngleX);
  Serial.print("accAngleY: ");
  Serial.println(accAngleY);

  delay(500); 
}
