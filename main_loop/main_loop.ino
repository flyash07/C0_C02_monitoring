/******************************************************************************
  Read basic CO2 and TVOCs

  Marshall Taylor @ SparkFun Electronics
  Nathan Seidle @ SparkFun Electronics

  April 4, 2017

  https://github.com/sparkfun/CCS811_Air_Quality_Breakout
  https://github.com/sparkfun/SparkFun_CCS811_Arduino_Library

  Read the TVOC and CO2 values from the SparkFun CSS811 breakout board

  A new sensor requires at 48-burn in. Once burned in a sensor requires
  20 minutes of run in before readings are considered good.

  Hardware Connections (Breakoutboard to Arduino):
  3.3V to 3.3V pin
  GND to GND pin
  SDA to A4
  SCL to A5

******************************************************************************/
#include <Wire.h>
#include "DHT11.h"
#include "ccs811.h" //Click here to get the library: http://librarymanager/All#SparkFun_CCS811
#include "buzzer.h"
#include "led.h"
#include <SoftwareSerial.h>
//#define CCS811_ADDR 0x5B //Default I2C Address
#define CCS811_ADDR 0x5A //Alternate I2C Address
#define BuzzerPin 7
#define LedPin 8
#define RX 3
#define TX 2
CCS811 mySensor(CCS811_ADDR);
DHT11 dht11(6);
SoftwareSerial ArduinoUno(3,2);
void setup()
{
  Serial.begin(115200);
  //Serial.println("CCS811 Basic Example");
  ArduinoUno.begin(9600);
  pinMode(RX,INPUT);
  pinMode(TX,OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  Wire.begin(); //Inialize I2C Hardware
  while(mySensor.begin() == false)
  {
    Serial.print("CCS811 error. Please check wiring. Freezing...");
  }
}

void loop()
{
  //Check to see if data is ready with .dataAvailable()
  float temperature;
  float avg_co2,avg_tvoc;
  
    if (mySensor.dataAvailable())
    {
      //If so, have the sensor read and calculate the results.
      //Get them later
      mySensor.readAlgorithmResults();
      //Returns calculated CO2 reading
      avg_co2 = mySensor.getCO2();
      //Returns calculated TVOC reading
      avg_tvoc = mySensor.getTVOC();
    }
  
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
        temperature = dht11.readTemperature();
    } else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(temperature));
    } 
  Serial.print("CO2[");
  Serial.print(avg_co2);
  Serial.print("] tVOC[");
  Serial.print(avg_tvoc);
  Serial.println("]");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Send_To_Esp(avg_co2,avg_tvoc,temperature);
  if(avg_co2>1000)
    {
      int t = 1000;
      while(t--)
      {
        BuzzerRing(BuzzerPin);
        LedOn(LedPin);
      }
    }  
    LedOff(LedPin);
  delay(1000); 
}
void Send_To_Esp(int co2,int tvoc,int temp)
{
  ArduinoUno.println(co2);
  ArduinoUno.println(tvoc);
  ArduinoUno.println(temp);
}
