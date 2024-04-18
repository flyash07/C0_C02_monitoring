#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>


//d2 is rx
//d3 is tx
//connect vin
//connect grnd
SoftwareSerial NodeMCU(D2, D3);

void setup() {
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(9600);
  NodeMCU.begin(9600); // Use the same baud rate as Serial
}

void send_to_arduino() {
  int i = 10;
  NodeMCU.print(i);
  NodeMCU.println("\n");
  delay(30);
}


void receive_from_arduino(){
  while(1){
    if (NodeMCU.available() > 0) {
      String receivedData = NodeMCU.readStringUntil('\n'); // Read until newline
      Serial.println(receivedData); // Print received data to serial monitor
    }
    delay(30); 
  }  
}
