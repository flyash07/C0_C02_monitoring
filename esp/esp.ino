#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "tf u looking at";
const char* password = "2cwuua9vrwh97k6";
const char* serverIP = "192.168.173.125"; // Change this to the IP address of your server
const int serverPort = 12370; // Change this to the port number of your server
int count = 0;
WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
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

void loop() {
  // put your main code here, to run repeatedly:

  if (!client.connect(serverIP, serverPort)) {
    Serial.println("Connection failed.");
    delay(1000);
    return;
  }

  Serial.println("Connected to server");
  // Send a message to the server
  client.println("Hello from ESP8266");


  client.println(count++);
  // Read response from the server
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print("Response from server: ");
    Serial.println(line);
  }

  //client.stop();
  Serial.println("Connection closed");
  
  //delay(5000); // Wait for a few seconds before sending another message
}
