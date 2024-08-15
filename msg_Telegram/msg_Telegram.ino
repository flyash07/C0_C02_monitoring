#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "TelegramBotControl.h"

// Define your Wi-Fi network credentials 
const char* ssid = "TanSpot";
const char* password = "ahyesthepassword";

// Define the Telegram Bot API Token
const char* telegramToken = ""; //redacted
const String chatID = ""; //redacted

// Define the Server IP and Port
const char* serverIP = "192.168.95.124"; // Change this to the IP address of your server
const int serverPort = 12371; // Change this to the port number of your server
int count = 0;

// Create instances
WiFiClient client;
TelegramBotControl telegramBot(ssid, password, telegramToken, chatID);

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
  telegramBot.setup();
  
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void send_to_arduino() {
  int i = 10;
  NodeMCU.print(i);
  NodeMCU.println("\n");
  delay(300);
}

void receive_from_arduino(){
  while(1){
    if (NodeMCU.available() > 0) {
      float receivedData = NodeMCU.parseFloat(); // Read until newline
      Serial.println(receivedData); // Print received data to serial monitor
    }
    delay(30);
  }  
}

void loop() {
    if (!client.connect(serverIP, serverPort)) {
    Serial.println("Connection failed.");
    delay(1000);
    return;
  }
   client.println("Hi I am esp8266");
    while(1){
      delay(5000);
      send_to_arduino();
      delay(2000);
      if (NodeMCU.available() > 0) {
        String receivedData = NodeMCU.readStringUntil('\n'); // Read until newline
        receivedData.trim();
        if (receivedData.length() > 0) {
          Serial.println(receivedData); // Print received data to serial monitor
          telegramBot.sendMessage(receivedData);
          client.println(receivedData);
          Serial.println("Message sent to server");
          NodeMCU.flush(); // Clear buffer
        }
      }
 
      else{
        //Serial.println("nothinggg\n");
      }
    delay(30);
    }
}
