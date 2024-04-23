#include "TelegramBotControl.h"

TelegramBotControl::TelegramBotControl(const char* ssid, const char* password, const char* token, const String& chatID)
    : ssid(ssid), password(password), telegramToken(token), chatID(chatID), bot(token, wifiClient) {
    // Constructor implementation
}

void TelegramBotControl::setup() {
    Serial.begin(115200);

    // Attempt to connect to Wi-Fi
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Still trying to connect to Wi-Fi...");
    }
    Serial.println("Successfully connected to Wi-Fi!");

    // Set the WiFiClientSecure to insecure if you are not using SSL certificates
    wifiClient.setInsecure();

    // Send a test message via Telegram
    sendMessage("Hello from ESP8266!");
}

void TelegramBotControl::sendMessage(const String& message) {
    // Use UniversalTelegramBot to send a message
    bot.sendMessage(chatID, message, "");
    Serial.println("Message sent via Telegram.");
}
