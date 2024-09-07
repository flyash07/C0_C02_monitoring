#include "DHT11.h"
#include "ccs811.h"
#include<Wire.h>
#include <SoftwareSerial.h>
#include"MQ7.h"
#define LedPin 4
#define Led_Calib 10
#define BuzzerPin 9
#define RX 3
#define TX 2
#define WAKE 5
#define CCS811_ADDR 0x5A
DHT11 dht11(6);
CCS811 mySensor(CCS811_ADDR);
MQ7 mq7(A0, 5.0);
int flag = 0, count = 0;
float mq7_limit = 0;                //calibration will set the base CO reading of the environment
SoftwareSerial ArduinoUno(RX, TX);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ArduinoUno.begin(9600);
  Serial.println("Hello");
  calibration();
}

void loop() {
  float temperature;
  float avg_co2 = 0, avg_tvoc = 0;
  float mq_data = 0;
  digitalWrite(LedPin, LOW);
  if (mySensor.dataAvailable())
  {
    mySensor.readAlgorithmResults();              //If so, have the sensor read and calculate the results. Get them later
    avg_co2 = mySensor.getCO2();                  //Returns calculated CO2 reading
    avg_tvoc = mySensor.getTVOC();                //Returns calculated TVOC reading
  }
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
    temperature = dht11.readTemperature();
  } else {
    Serial.println(DHT11::getErrorString(temperature));         // Print error message based on the error code.
  }
  Serial.print("CO2[");
  Serial.print(avg_co2);
  Serial.print("] tVOC[");
  Serial.print(avg_tvoc);
  Serial.println("]");
  Serial.println("Temperature: ");
  Serial.println(temperature);
  mq_data = mq7.getPPM();
  Serial.println(mq_data);
  String my_mq7 = String(mq_data, 2);
  if (ArduinoUno.available() > 0) {
    Send_To_Esp(avg_co2, avg_tvoc, temperature, mq_data);
  }
  if (avg_co2 > 500 || mq_data >= mq7_limit) {
    flag = 1;
  }
  else {
    flag = 0;
    analogWrite(BuzzerPin, 0);
    count = 0;
  }
  if (flag == 1) {
    count++;
  }
  if (count == 100) {
    flag = 0;
    count = 0;
    analogWrite(BuzzerPin, 0);
  }
  delay(2000);
}
void LedOn(int pin) {
  digitalWrite(pin, HIGH);
}
void LedOff(int pin) {
  digitalWrite(pin, LOW);
}
void BuzzerOff(int pin) {
  digitalWrite(pin, HIGH);
}
void BuzzerOn(int pin) {
  digitalWrite(pin, LOW);
}
void BuzzerRing(int buzzerPin) {
  BuzzerOn(buzzerPin);
  delay(10);
  BuzzerOff(buzzerPin);
  delay(10);
}
void Send_To_Esp(int co2, int tvoc, int temp, int mq_data) {
  char buffer[128];
  sprintf(buffer, "CO2:%d TVOC:%d temp:%d MQ7:%d", co2 , tvoc, temp, mq_data);
  ArduinoUno.println(buffer);
  delay(200);
  if (flag == 1) {
    analogWrite(BuzzerPin, 127);
  }
}
void calibration() {
  Serial.println("Hello");
  pinMode(Led_Calib,OUTPUT);
  digitalWrite(Led_Calib,1);
//  Serial.begin(9600);
//  ArduinoUno.begin(9600);
  pinMode(LedPin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);
  analogWrite(BuzzerPin, 0);
  TCCR1B = TCCR1B & B11111000 | B00000101;
  Wire.begin();
  uint32_t period = 5 * 60000L;       // 5 minutes
  int counter = 0;
   for( uint32_t tStart = millis();  (millis()-tStart) < period;  )
   {
      if(mq7.getPPM()){
        Serial.println("Hello");
      }
      counter++;
   }
   Serial.println(counter);
  while (mySensor.begin() == false) {
    Serial.println("CCS811 error. Please check wiring. Freezing...");
    delay(100);
  }
  mq7_limit = 2;        // setting the vlaue code
  digitalWrite(Led_Calib,0);
}
