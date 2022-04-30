#define X_PIN A0
#define Y_PIN A1
#define Z_PIN A2
int a=0;
int flag=0;
#include <FileIO.h>
#include "DHT.h"
#define dhtPin 8 //讀取DHT11 Data
#define dhtType DHT11 //選用DHT11 
DHT dht(dhtPin, dhtType); // Initialize DHT sensor

void setup() {
  Serial.begin(9600);//設定鮑率9600
  dht.begin();//啟動DHT
  pinMode(7,INPUT);
  FileSystem.begin();
}
float toG(float v){
  return v * 6 / 1023 - 3;
}
void loop() {
  float g = analogRead(X_PIN);
  delay(1000);
  float x = analogRead(X_PIN);
  int y = analogRead(Y_PIN);
  int z = analogRead(Z_PIN);

  if(digitalRead(7)==1&&flag==0){
    flag=1;
  }
  if(fabs(x-g)>10)
  a++;

  delay(100);
  float h = dht.readHumidity();//讀取濕度
  float t = dht.readTemperature();//讀取攝氏溫度
  float f = dht.readTemperature(true);//讀取華氏溫度
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("無法從DHT傳感器讀取！");
    return;
  }
  if(flag==1){
    /*Serial.print("X: ");
    Serial.print(x);
    Serial.print(", Y: ");
    Serial.print(y);
    Serial.print(", Z: ");
    Serial.print(z);
    Serial.print("; X: ");
    Serial.print(toG(x));
    Serial.print("g, Y: ");
    Serial.print(toG(y));
    Serial.print("g, Z: ");
    Serial.print(toG(z));
    Serial.println("g");
    Serial.println("a");*/
    Serial.println(a);
    Serial.println("\n");
    Serial.print("moistrue: ");
    Serial.print(h);
    Serial.print("%\n");
    Serial.print("temperature(*c): ");
    Serial.print(t);
    Serial.print("*C\n");
    /*Serial.print("temperature(*f): ");
    Serial.print(f);
    Serial.print("*F\n");*/
    flag++;
    flag++;
  }
}
