#include "WiFi.h"
#include <Wire.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN "BOTQ9UAvkMbteZcqop5HIPhd3tosfAstgJZZJYuvzDL"

char ssid[] = "沒有wifi";
char password[] = "12345678";

int MPU_addr=0x68; // 12C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;  

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  Wire.begin();
  Wire.beginTransmission(true);
  Wire.write(0x68);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.println("Wrote to IMU");

  
  delay(1000);
  Serial.print("開始連線到:");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  int WifiTryCount = 0;
  while(WiFi.status()!= WL_CONNECTED){
    Serial.print(".");
    WiFi.begin(ssid, password);
    delay(2500);
    if (WifiTryCount++>=20) ESP.restart();
  }
  Serial.println("setup done");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8 | Wire.read();
  AcY=Wire.read()<<8 | Wire.read();
  AcZ=Wire.read()<<8 | Wire.read();


//  if(G(AcX)>1 || G(AcY)>1 || G(AcZ)>1 || G(AcX)<-1 || G(AcY)<-1 || G(AcZ)<-1){
//    
//  }
  Serial.print(" Accelerometer Values:");
  Serial.print("\nAcX: ");
  Serial.print(AcX);
  Serial.print("\nAcY: ");
  Serial.print(AcY);
  Serial.print("\nAcZ:");
  Serial.print(float(AcZ/16000.0));

  if (float(AcZ/16000.0) < 0.3){
    LINE.setToken(LINE_TOKEN);
    LINE.notify("仆街了 注意!!!!");
  }
  
  delay(1000);
}
