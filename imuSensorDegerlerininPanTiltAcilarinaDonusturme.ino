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
  // Deneyap Kartı üzerindeki IMU sensöründen alınan ivmesel X ve Y eksenlerinin değerlerinin açısal değerlere döndüren hesaplamalar aşağıdadır.
  accAngleX = atan(IMU.readFloatAccelX() / sqrt(pow(IMU.readFloatAccelY(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;
  accAngleY = atan(-1 * IMU.readFloatAccelY() / sqrt(pow(IMU.readFloatAccelX(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;

  // X ve Y eksenlerindeki açısal değerlerin Seri Monitörde gösterilmesi için gerekli kodlar
  Serial.print("accAngleX: ");
  Serial.println(accAngleX);
  Serial.print("accAngleY: ");
  Serial.println(accAngleY);
  delay(500); 
}

// NOT: Kod içerisindeki “0.001” değerleri, olası herhangi bir tekillik (sıfıra bölme) durumunu bertaraf etmek için kullanılmıştır.
