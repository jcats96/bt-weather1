#include <Arduino.h>
#include <string.h>

#include "SFE_BMP180.h"
#include <Wire.h>

SFE_BMP180 sensor;
String bt_Str;
double T;
double F;
double P;
double temp();
double pressure();
char status;
void light(String);

void blink();
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  // initialize LED digital pin as an output.
  pinMode(8, OUTPUT);
  Serial.println("hello");
  if (sensor.begin())
   Serial.println("BMP180 init success");
   sensor.startTemperature();
   sensor.getTemperature(T);
   sensor.startPressure(1);

}

void loop()
{

  if (Serial1.available())
  {
  bt_Str = Serial1.readString();
  temp();
  pressure();
  light(bt_Str);
  }
  delay(100);


}


double temp()
{
  if (bt_Str == "temp\n")
  {
    status = sensor.startTemperature();
    if (status!=0) delay (5);
    sensor.getTemperature(T);
    F = 1.8*T+32;
    Serial.println(F);
    Serial.println("temp");
  }
}
double pressure()
{
  if (bt_Str == "pressure\n")
  {
    sensor.startPressure(1);
    delay(10);
    sensor.getPressure(P,T);
    Serial.println(P);
  }
}

void light(String input)
{
  if (input== "light on\n") digitalWrite(8, HIGH);
  if (input == "light off\n") digitalWrite(8, LOW);
}
