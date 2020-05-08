#include <DHT.h>
#include <DHT_U.h>
#include <BlynkSimpleStream.h>
#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

int led1 = 10, led2 = 11, led3 = 12, led4 = 13;
int LDR1, LDR2, LDR3, LDR4;
float suhu;
WidgetLCD lcd(V5);
BlynkTimer timer;

char auth[] = "NA6k2TOiX4gkZsD_rcP1s9-Bx5hjKfRv";

void setup() {
  lcd.clear();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, Serial);
  dht.begin();
  timer.setInterval(1000L, getSendData);
}

void loop() {
  timer.run();
  Blynk.run();
}

void getSendData() {
  lcd.print(2, 1, "Esa Kemal");
  LDR1 = analogRead(A0);
  LDR2 = analogRead(A1);
  LDR3 = analogRead(A2);
  LDR4 = analogRead(A3);

  Blynk.virtualWrite(1, LDR1);
  Blynk.virtualWrite(2, LDR2);
  Blynk.virtualWrite(3, LDR3);
  Blynk.virtualWrite(4, LDR4);
  
  if (LDR1 <= 71) {
    lcd.print(1, 0, "Kursi 1 diisi");
    digitalWrite(led1, HIGH);
  }
  else {
    lcd.clear();
    digitalWrite(led1, LOW);
  }
  if (LDR2 <= 71) {
    lcd.print(1, 0, "Kursi 2 diisi");
    digitalWrite(led2, HIGH);
  }
  else {
    lcd.clear();
    digitalWrite(led2, LOW);
  }
  if (LDR3 <= 71) {
    lcd.print(1, 0, "Kursi 3 diisi");
    digitalWrite(led3, HIGH);
  }
  else {
    lcd.clear();
    digitalWrite(led3, LOW);
  }
  if (LDR4 <= 71) {
    lcd.print(1, 0, "Kursi 4 diisi");
    digitalWrite(led4, HIGH);
  }
  else {
    lcd.clear();
    digitalWrite(led4, LOW);
  }
  if (LDR1 <= 71 && LDR2 <= 71 && LDR3 <= 71 && LDR4 <= 71) {
    lcd.print(0, 0, "AC ON | DHT11 ON");
    bacadht11();
  }
  else {
    lcd.clear();
  }
}
void bacadht11() {
  suhu = dht.readTemperature();
  Blynk.virtualWrite(V10, suhu);
  delay(1000);
}
