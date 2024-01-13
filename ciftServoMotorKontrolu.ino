// 4. Hafta: 1.3. Uygula: Deneyap Geliştirme Kartı ile Çift Servo Motor Kontrolü
#include <Deneyap_Servo.h>
#define SERVOPIN1 D14
#define SERVOPIN2 D9

Servo myservo1, myservo2;

int pos = 0;

void setup() 
{
  myservo1.attach(SERVOPIN1);
  myservo2.attach(SERVOPIN2,1);
}
void loop()
{
  // Servo motorların kontrol girişlerine kontrol sinyallerin gönderilmesi işlemi genel döngü (loop) içerisine yazılan kodlar ile yapılır.
    for (pos = 0; pos <= 180; pos += 1) {
	    myservo1.write(pos);
    	myservo2.write(pos);
    	delay (10);
     }
     for (pos = 180; pos >= 0; pos -= 1) {
    	myservo1.write(pos);
	    myservo2.write(pos);
    	delay (10);
    }
}
// NOT: Motorların kararlı çalışabilmesi için her konum bilgisi gönderimi işleminden sonra 10 ms bekleme verilmiştir. 
