// 4. Hafta: 1.2. Uygula: Deneyap Geliştirme Kartı Üzerinde Kumanda kolu Çalıştırılması
#include "deneyap.h"
#define SW_pin D0
#define X_pin A0
#define Y_pin A1

// Program içerisinde kullanılacak değişkenler de tanımlanır.
int X_Val, Y_Val, Dig_Val;
void setup () 
{
  Serial.begin(115200);
  pinMode(SW_pin, INPUT_PULLUP);
  digitalWrite(SW_pin, HIGH);
  pinMode(X_pin, INPUT);
  pinMode(Y_pin, INPUT);
}
void loop ()
{
  X_Val = analogRead(X_pin);
  Y_Val = analogRead(Y_pin);
  Dig_Val =digitalRead(SW_pin);
  Serial.print("X_Val: ");
  Serial.println(X_Val);
  Serial.print("Y_Val: ");
  Serial.println(Y_Val);
  Serial.print("Dig_Val: ");
  Serial.println(Dig_Val);
  delay(100); 
} 
// NOT: Serial monitör üzerinde anlamsız karakterler görünmesi durumunda sağ alt kenarda bulunan baud ayarından uygun baud değeri seçilmelidir. 
