#include <Wire.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <TridentTD_LineNotify.h>
#include "WiFi.h"
#define LINE_TOKEN "BOTQ9UAvkMbteZcqop5HIPhd3tosfAstgJZZJYuvzDL"

char ssid[] = "沒有wifi";
char password[] = "12345678";

int MPU_addr=0x68; // 12C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int16_t beforeX = 0,beforeY = 0;

const int buttonPin = 17;     // the number of the pushbutton pin
const int ledPin =  18;
int buttonState = 0;

void setTimeout(int milliseconds)
{
    // If milliseconds is less or equal to 0
    // will be simple return from function without throw error
    if (milliseconds <= 0) {
        fprintf(stderr, "Count milliseconds for timeout is less or equal to 0\n");
        return;
    }

    // a current time of milliseconds
    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;

    // needed count milliseconds of return from this timeout
    int end = milliseconds_since + milliseconds;

    // wait while until needed time comes
    do {
        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    } while (milliseconds_since <= end);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR MGMT 1 register
  Wire.write(0);
  // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.println("Wrote to IMU");
  Serial.println("Connecting to ");
  Serial.println("");

  //connect led and button
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

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

void loop(){
  delay(10000);
  LINE.setToken(LINE_TOKEN);
  LINE.notify("開始做操囉!!!");
  delay(5000);

  LINE.notify("開始第一個動作");
  Pose1();
  LINE.notify("結束第一個動作");

  delay(5000);

  LINE.notify("開始第二個動作");
  Pose2();
  LINE.notify("結束第二個動作");

  delay(5000);

  LINE.notify("開始第三個動作");
  Pose3();
  LINE.notify("結束第三個動作");
}

void Pose1(){
  int Delay = 10;
  beforeX = 0,beforeY = 0;
  do{
    LINE.setToken(LINE_TOKEN);
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);
    beforeX = AcX;
    beforeY = AcY;
    AcX=Wire.read()<<8 | Wire.read();
    AcY=Wire.read()<<8 | Wire.read();
    AcZ=Wire.read()<<8 | Wire.read();

    if ((abs(beforeX - AcX) > 1000)&&(abs(beforeY)>4000)){
      LINE.notify("動作很標準喔!!!!");
    }else{
      LINE.notify("動作再大一點 加油~~~");
    }
    setTimeout(1000);
    Delay--;
    Serial.println(Delay);
  }while(Delay >= 0);
  return;
}

void Pose2(){
  int Delay = 10;
  beforeX = 0,beforeY = 0;
  do{
    LINE.setToken(LINE_TOKEN);
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);
    beforeX = AcX;
    beforeY = AcY;
    AcX=Wire.read()<<8 | Wire.read();
    AcY=Wire.read()<<8 | Wire.read();
    AcZ=Wire.read()<<8 | Wire.read();

    if ((abs(beforeX - AcX) > 2000)&&(abs(beforeY)> 3000)){
      LINE.notify("動作很標準喔!!!!");
    }else{
      LINE.notify("動作再大一點 加油~~~");
    }
    setTimeout(1000);
    Delay--;
    Serial.println(Delay);
  }while(Delay >= 0);
  return;
}

void Pose3(){
  int Delay = 10;
  beforeX = 0,beforeY = 0;
  do{
    LINE.setToken(LINE_TOKEN);
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);
    beforeX = AcX;
    beforeY = AcY;
    AcX=Wire.read()<<8 | Wire.read();
    AcY=Wire.read()<<8 | Wire.read();
    AcZ=Wire.read()<<8 | Wire.read();

    if ((abs(beforeX - AcX) > 4000)&&(abs(beforeY)>6000)){
      LINE.notify("動作很標準喔!!!!");
    }else{
      LINE.notify("動作再大一點 加油~~~");
    }
    setTimeout(1000);
    Delay--;
    Serial.println(Delay);
  }while(Delay >= 0);
  return;
}
