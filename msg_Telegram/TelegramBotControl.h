#ifndef TELEGRAMBOTCONTROL_H
#define TELEGRAMBOTCONTROL_H

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

class TelegramBotControl {
public:
    // Constructor
    TelegramBotControl(const char* ssid, const char* password, const char* token, const String& chatID);

    // Setup method to initialize Wi-Fi and Telegram bot
    void setup();

    // Method to send a message via Telegram
    void sendMessage(const String& message);

private:
    const char* ssid;
    const char* password;
    const char* telegramToken;
    String chatID;

    WiFiClientSecure wifiClient;
    UniversalTelegramBot bot;
};

#endif // TELEGRAMBOTCONTROL_H
