
#include <Arduino.h>
#include <WiFi.h>
#include "esp_camera.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "laksi";
const char* password = "12345678";
const char* serverIP = "192.168.1.100";
const int serverPort = 8080;

// Telegram Bot Credentials
String BOTtoken = "8080113922:AAHvxqdQ54gYd2PdqgYPAj4dwZWtIpyOX7I";
String CHAT_ID = "1773456421";

WiFiClientSecure clientTCP;
UniversalTelegramBot bot(BOTtoken, clientTCP);
WiFiClient client;

void sendTelegramMessage(String message) {
    bot.sendMessage(CHAT_ID, message, "");
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    clientTCP.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    sendTelegramMessage("ESP32-CAM connected to WiFi");
}

void loop() {
    camera_fb_t* fb = esp_camera_fb_get();
    if (!fb) {
        sendTelegramMessage("Camera capture failed");
        return;
    }

    if (client.connect(serverIP, serverPort)) {
        client.write((const uint8_t*)fb->buf, fb->len); 
        esp_camera_fb_return(fb); 

        // Read response from Raspberry Pi server
        String response = client.readString();
        if (response.startsWith("1|")) {
            sendTelegramMessage("Recognized: " + response.substring(2));
        } else if (response.startsWith("0|")) {
            sendTelegramMessage("Unknown person detected.");
        }
        client.stop();
    } else {
        sendTelegramMessage("Connection to server failed");
    }
    delay(5000); 
}
