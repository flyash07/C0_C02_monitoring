#include"buzzer.h"
const int buzzerPin = 13;
int count = 0;
void setup()
{
  pinMode(buzzerPin, OUTPUT);
}
void loop()
{
  if(count < 10)
  {
    for(int i=0;i<10;i++)
    {
      BuzzerRing(buzzerPin);
    }
    count++;
  }
}
