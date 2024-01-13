// 2. Hafta: 1.4. Uygula: LDR Sensörünün Dijital Çıkışı ile Servo Motor Kontrolü
#include <Deneyap_Servo.h>		// Servo motor kütüphanesinin programa eklenmesi
#define SERVOPIN D0  		      // servo motorun bağlandığı D0 pininin tanımlaması
#define L1_pin D14   			    // sağ ışık sensörünün bağlandığı D14 pininin tanımlaması
#define L2_pin D15   			    // sol ışık sensörünün bağlandığı D15 pininin tanımlaması
Servo myservo;			          // servo motora ilişkin değişken tanımlaması
int sensor1, sensor2;			    // LDR’lerin değişkenlerinin tanımlanması
int pos = 0;				          // servo motor pozisyonuna ilişkin değişken tanımlaması

void setup(){
  myservo.attach(SERVOPIN);		
  pinMode(L1_pin, INPUT);    
  pinMode(L2_pin, INPUT);  
}

void loop(){
  sensor1 = digitalRead(L1_pin);	//sağ ışık sensöründen gelen dijital verinin okunması
  sensor2 = digitalRead(L2_pin);	//sol ışık sensöründen gelen dijital verinin okunması
    if (sensor1>sensor2)			//sağ LDR’ye düşen ışık > sol LDR’ye düşen ışık
    {
      pos=0;
      myservo.write(pos);		//pozisyon değeri 0 derece olarak motora gönderilir.
    }
    else if(sensor2>sensor1) 		//sol LDR’ye düşen ışık  > sağ LDR’ye düşen ışık
    {
      pos=180;				
      myservo.write(pos);		//pozisyon değeri 180 derece olarak motora gönderilir.
    }
    else if(sensor2=sensor1)		//sağ LDR’ye düşen ışık = sol LDR’ye düşen ışık
    {
      pos=90;
      myservo.write(pos);		//pozisyon değeri 90 derece olarak motora gönderilir.
    }
  delay(5);
}


