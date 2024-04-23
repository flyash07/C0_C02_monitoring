#include "TelegramBotControl.h"

// Define your Wi-Fi network credentials and Telegram Bot API token
const char* ssid = "TanSpot";
const char* password = "ahyesthepassword";
const char* telegramToken = "7047406355:AAHCg-j70NBcowforzydCf6zgBaKBFEwqK0";
const String chatID = "6642708288";
int i=1;

// Create an instance of TelegramBotControl
TelegramBotControl telegramBot(ssid, password, telegramToken, chatID);

void setup() {
    // Setup the bot and connect to Wi-Fi
    telegramBot.setup();
}

void loop() {
    // Format the message by converting the integer 'i' to a string and concatenating it with the message
    String message = "index " + String(i) + ": Hello from ESP8266!";
    
    // Send the formatted message via Telegram
    telegramBot.sendMessage(message);
    
    // Wait for 5 seconds before sending another message
    delay(5000);
    
    // Increment the index 'i' for each loop iteration (if desired)
    i++;
}
