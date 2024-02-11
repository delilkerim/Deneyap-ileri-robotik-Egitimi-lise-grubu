#include <Servo.h>
#include <Deneyap_Servo.h>// Eğer bu kütüphane çalışmaz ise <ESP32Servo.h> kütüphanesi denenebilir.
#define SW1_pin D0
#define SW2_pin D1
#define X1_pin A0
#define Y1_pin A1
#define X2_pin A2
#define Y2_pin A3
#define X3_pin A4
#define Y3_pin A5
#define SERVOPIN1 D4
#define SERVOPIN2 D9
#define SERVOPIN3 D12
#define SERVOPIN4 D13
#define SERVOPIN5 D14
#define SERVOPIN6 D15
//Aşağıdaki teta değerleri 0-3000 arasında kalibre edilmiştir. 3000 değeri 180 dereceye karşılık gelmektedir.
int teta1min = 0;
int teta1max = 3000;
int teta2min = 0;
int teta2max = 3000;
int teta3min = 500;
int teta3max = 2500;
int teta4min = 0;
int teta4max = 3000;
int teta5min = 0;
int teta5max = 3000;
int teta6min = 1500;
int teta6max = 2000;
int valin1, valin2, valin3, valin4, valin5, valin6;
int valcalc1 = 1500; //Başlangıç açı değerleri
int valcalc2 = 1500;
int valcalc3 = 1500;
int valcalc4 = 1500;
int valcalc5 = 1500;
int valcalc6 = 2000;
int jystp = 20;
bool playmode = false;
int ButtonMode = 0;
unsigned long CurrentMilliSec = millis();
long PreMilliSec = 0;
int NumMemory = 0;
int PreNumMemory = 0;
int Step = -1;
int joint1[50];
int joint2[50];
int joint3[50];
int joint4[50];
int joint5[50];
int joint6[50];
int maxarray = 49;
int prehiz = 10;
int normalhiz = 10;
// hiz=1 çok yavaş, 5 yavaş, 10 normal, 15 hızlı, 20+ çok hızlı
int hiz = 10;
int prepos1, prepos2, prepos3, prepos4, prepos5, prepos6;
int pos11, pos21, pos31, pos41, pos51, pos61;
Servo myservo1, myservo2, myservo3, myservo4, myservo5, myservo6;
void setup()
{
  myservo1.attach(SERVOPIN1); //Eğer <ESP32Servo.h> kütüphanesi kullanırsanız, bu ve aşağıdaki 5 satırda parantez içerisindeki 2’inci parametreyi silin, tek parametre yeterlidir.
  myservo2.attach(SERVOPIN2, 1);
  myservo3.attach(SERVOPIN3, 2);
  myservo4.attach(SERVOPIN4, 3);
  myservo5.attach(SERVOPIN5, 4);
  myservo6.attach(SERVOPIN6, 5);
  pinMode(SW1_pin, INPUT_PULLUP);
  pinMode(SW2_pin, INPUT_PULLUP);
  pinMode(X1_pin, INPUT);
  pinMode(Y1_pin, INPUT);
  pinMode(X2_pin, INPUT);
  pinMode(Y2_pin, INPUT);
  pinMode(X3_pin, INPUT);
  pinMode(Y3_pin, INPUT);
  digitalWrite(SW1_pin, HIGH);
  digitalWrite(SW2_pin, HIGH);
  Serial.begin(115200);
  Serial.println("Ready.");
}
void loop() {
  CurrentMilliSec = millis();
  Button();
  if (playmode == false && Step == -1) {
    ReadAnalog();
    myservo1.writeMicroseconds(valcalc1);
    myservo2.writeMicroseconds(valcalc2);
    myservo3.writeMicroseconds(valcalc3);
    myservo4.writeMicroseconds(valcalc4);
    myservo5.writeMicroseconds(valcalc5);
    myservo6.writeMicroseconds(valcalc6);
    delay(int(300. / hiz));
  }
  else {
    playit();
  }
}
void ReadAnalog() {
  valin1 = analogRead(Y1_pin);
  valin2 = analogRead(X1_pin);
  valin3 = analogRead(X2_pin);
  valin4 = analogRead(Y2_pin);
  valin5 = analogRead(X3_pin);
  valin6 = analogRead(Y3_pin);
  if (valin1 < 1000 && valcalc1 > teta1min) valcalc1 -= jystp;
  if (valin1 > 3000 && valcalc1 < teta1max) valcalc1 += jystp;
  if (valin2 < 1000 && valcalc2 > teta2min) valcalc2 += jystp;
  if (valin2 > 3000 && valcalc2 < teta2max) valcalc2 -= jystp;
  if (valin3 < 1000 && valcalc3 > teta3min) valcalc3 -= jystp;
  if (valin3 > 3000 && valcalc3 < teta3max) valcalc3 += jystp;
  if (valin4 < 1000 && valcalc4 > teta4min) valcalc4 -= jystp;
  if (valin4 > 3000 && valcalc4 < teta4max) valcalc4 += jystp;
  if (valin5 < 1000 && valcalc5 > teta5min) valcalc5 -= jystp;
  if (valin5 > 3000 && valcalc5 < teta5max) valcalc5 += jystp;
  if (valin6 < 1000 && valcalc6 > teta6min) valcalc6 -= jystp;
  if (valin6 > 3000 && valcalc6 < teta6max) valcalc6 += jystp;
}
void Button() {
  if (playmode == false) {
    if (digitalRead(SW1_pin) == 0) {
      delay(100);
      if (digitalRead(SW1_pin) == 1) {
        if (ButtonMode == 0)
        {
          ButtonMode = 1;
          PreMilliSec = CurrentMilliSec;
        }
        else if ((ButtonMode == 1) && (CurrentMilliSec - PreMilliSec < 500))
        {
          ButtonMode = 2;
        }
      }
    }
    if ((ButtonMode == 1) && (CurrentMilliSec - PreMilliSec > 600)) {
      saveit();
      NumMemory += 1;
      if (NumMemory > maxarray) NumMemory = maxarray;
      ButtonMode = 0;
      Serial.print("Saved: "); Serial.println(NumMemory);
    }
    else if (ButtonMode == 2 && (CurrentMilliSec - PreMilliSec > 600)) {
      if ((NumMemory > 1 || PreNumMemory > 1) && playmode == false) {
        Serial.println("Playmode...");
        playmode = true;
        ButtonMode = 0;
        if (NumMemory < 2) NumMemory = PreNumMemory; else
          PreNumMemory = NumMemory;
        joint1[0] = pos11;
        joint2[0] = pos21;
        joint3[0] = pos31;
        joint4[0] = pos41;
        joint5[0] = pos51;
        joint6[0] = pos61;
        Step = NumMemory - 1;
        ReadAnalog();
        prepos1 = valcalc1;
        prepos2 = valcalc2;
        prepos3 = valcalc3;
        prepos4 = valcalc4;
      }
    }
    if (ButtonMode < 3 && CurrentMilliSec - PreMilliSec > 1000) {
      ButtonMode = 0;
    }
  }
  else if (ButtonMode < 3 && digitalRead(SW1_pin) == 0) {
    ButtonMode = 3;
    Serial.println("Stopping.");
    ReadAnalog();
    NumMemory += 1;
    joint1[NumMemory - 1] = valcalc1;
    joint2[NumMemory - 1] = valcalc2;
    joint3[NumMemory - 1] = valcalc3;
    joint4[NumMemory - 1] = valcalc4;
    joint5[NumMemory - 1] = valcalc5;
    joint6[NumMemory - 1] = valcalc6;
  }
  if (digitalRead(SW2_pin) == 0) {
    if (prehiz == hiz) {
      if (hiz == normalhiz) {
        hiz = 2 * normalhiz;
        jystp = 40;
        Serial.println("High speed.");
        if (playmode == false) {
          delay(300);
        }
      } else {
        if (hiz == (2 * normalhiz)) {
          hiz = normalhiz / 2;
          jystp = 10;
          Serial.println("Low speed.");
          if (playmode == false) {
            delay(300);
          }
        }
        else if (hiz == (normalhiz / 2)) {
          hiz = normalhiz;
          jystp = 20;
          Serial.println("Normal speed.");
          if (playmode == false) {
            delay(300);
          }
        }
      }
    }
  }
  else {
    prehiz = hiz;
  }
}
void saveit() {
  joint1[NumMemory] = valcalc1;
  joint2[NumMemory] = valcalc2;
  joint3[NumMemory] = valcalc3;
  joint4[NumMemory] = valcalc4;
  joint5[NumMemory] = valcalc5;
  joint6[NumMemory] = valcalc6;
  prepos1 = valcalc1;
  prepos2 = valcalc2;
  prepos3 = valcalc3;
  prepos4 = valcalc4;
  prepos5 = valcalc5;
  prepos6 = valcalc6;
  if (NumMemory == 1) {
    pos11 = joint1[0];
    pos21 = joint2[0];
    pos31 = joint3[0];
    pos41 = joint4[0];
    pos51 = joint5[0];
    pos61 = joint6[0];
  }
}
void playit()
{
  float pos1 = prepos1;
  float pos2 = prepos2;
  float pos3 = prepos3;
  float pos4 = prepos4;
  float pos5 = prepos5;
  float pos6 = prepos6;
  float dif1 = abs(joint1[Step] - pos1);
  float dif2 = abs(joint2[Step] - pos2);
  float dif3 = abs(joint3[Step] - pos3);
  float dif4 = abs(joint4[Step] - pos4);
  float dif5 = abs(joint5[Step] - pos5);
  float dif6 = abs(joint6[Step] - pos6);
  float maxdif = 0.0;
  if (dif1 > maxdif) maxdif = dif1;
  if (dif2 > maxdif) maxdif = dif2;
  if (dif3 > maxdif) maxdif = dif3;
  if (dif4 > maxdif) maxdif = dif4;
  if (dif5 > maxdif) maxdif = dif5;
  if (dif6 > maxdif) maxdif = dif6;
  maxdif = maxdif / hiz;
  if (maxdif < 1.0) maxdif = 1.0;
  float stp1 = (joint1[Step] - pos1) / maxdif;
  float stp2 = (joint2[Step] - pos2) / maxdif;
  float stp3 = (joint3[Step] - pos3) / maxdif;
  float stp4 = (joint4[Step] - pos4) / maxdif;
  float stp5 = (joint5[Step] - pos5) / maxdif;
  float stp6 = (joint6[Step] - pos6) / maxdif;
  for (int i = 1; i <= int(maxdif); i++) {
    pos1 = pos1 + stp1;
    pos2 = pos2 + stp2;
    pos3 = pos3 + stp3;
    pos4 = pos4 + stp4;
    pos5 = pos5 + stp5;
    pos6 = pos6 + stp6;
    if (i == int(maxdif)) {
      pos1 = joint1[Step];
      pos2 = joint2[Step];
      pos3 = joint3[Step];
      pos4 = joint4[Step];
      pos5 = joint5[Step];
      pos6 = joint6[Step];
    }
    myservo1.writeMicroseconds(int(pos1));
    myservo2.writeMicroseconds(int(pos2));
    myservo3.writeMicroseconds(int(pos3));
    myservo4.writeMicroseconds(int(pos4));
    myservo5.writeMicroseconds(int(pos5));
    myservo6.writeMicroseconds(int(pos6));
    prepos1 = pos1;
    prepos2 = pos2;
    prepos3 = pos3;
    prepos4 = pos4;
    prepos5 = pos5;
    prepos6 = pos6;
    delay(10);
    if (ButtonMode < 3) Button();
    else delay(5);
  }
  if (ButtonMode == 3 && Step == NumMemory - 1) {
    NumMemory = 0;
    Step = -1;
    ButtonMode = 0;
    playmode = false;
    Serial.println("Stopped.");
  }
  else {
    Step += 1;
    if (Step > NumMemory - 1) Step = 0;
  }
}
