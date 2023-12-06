#define BLYNK_TEMPLATE_ID "TMPL6S-_PxGxV"
#define BLYNK_TEMPLATE_NAME "MOTORCONTROL"
#define BLYNK_AUTH_TOKEN "KPKXYZPx1owWFyqbypjUKUVXM_AJvk1L"

#include <Arduino.h>
#include "functions.h"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MOTORPWM D7
#define OPTO D5

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void displayMotorRPM();

int setmotorspeed = 0;
int motorspeed = 0;

float RPM = 0;
unsigned long millisBefore;
volatile int gaps;

char auth[] = "KPKXYZPx1owWFyqbypjUKUVXM_AJvk1L"; // Enter your Blynk Auth token
char ssid[] = "AndroidAP";                        // Enter your WIFI SSID
char pass[] = "88880000";                         // Enter your WIFI Password

BlynkTimer timer;

void IRAM_ATTR count()
{
  gaps++;
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  attachInterrupt(digitalPinToInterrupt(D6), count, FALLING);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 15);
  display.print("CONNECTING SERVER");
  display.setCursor(10, 25);
  display.print("SERVER READY");
  display.setCursor(10, 35);
  display.print("MOTOR READY");
  display.display();
  delay(5000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 15);
  display.print("WEB CONTROLLED");
  display.setCursor(10, 25);
  display.print("HAND MADE MOTOR");
  display.setCursor(10, 40);
  display.print("GROUP_1(1-6)");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 10);
  display.print("INPUT RPM : ");
  display.print(setmotorspeed);
  display.setCursor(5, 20);
  display.print("MOTOR RPM : ");
  display.print(motorspeed);
  display.display();

  pinMode(MOTORPWM, OUTPUT);
  pinMode(OPTO, INPUT);

  analogWrite(MOTORPWM, 255);

  timer.setInterval(500L, displayMotorRPM);
}

BLYNK_WRITE(V1)
{
  setmotorspeed = param.asInt();
  Serial.println(setmotorspeed);
  int x = map(setmotorspeed, 0, 6000, 0, 255);
  analogWrite(MOTORPWM, x);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 10);
  display.print("INPUT RPM : ");
  display.print(setmotorspeed);
  display.setCursor(5, 20);
  display.print("MOTOR RPM : ");
  display.print(RPM);
  display.display();
}
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V1);
}
void displayMotorRPM()
{
  motorspeed = checkRPM();
  Blynk.virtualWrite(V2, RPM);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 10);
  display.print("INPUT RPM : ");
  display.print(setmotorspeed);
  display.setCursor(5, 20);
  display.print("MOTOR RPM : ");
  display.print(RPM);
  display.display();
}
void loop()
{

  if (millis() - millisBefore > 1000)
  {
    RPM = (gaps / 20.0) * 60;
    gaps = 0;
    millisBefore = millis();
  }

  Serial.println(RPM);

  Blynk.run();
  timer.run();
}
