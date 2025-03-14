#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "laksi";
const char* password = "12345678";
const char* serverIP = "192.168.1.100";
const int serverPort = 8080;

// Initialize Telegram BOT
String BOTtoken = "8080113922:AAHvxqdQ54gYd2PdqgYPAj4dwZWtIpyOX7I";  
String CHAT_ID = "1773456421"; 

WiFiClientSecure clientTCP;
UniversalTelegramBot bot(BOTtoken, clientTCP);
WiFiClient client;

#define FLASH_LED_PIN 4
#define PIR_PIN 13  // PIR sensor pin
bool flashState = LOW;
bool sendPhoto = false;

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

// CAMERA_PIN CONFIGURATION
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

void configInitCamera() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    if (psramFound()) {
        config.frame_size = FRAMESIZE_QVGA;
        config.jpeg_quality = 8;
        config.fb_count = 2;
    } else {
        config.frame_size = FRAMESIZE_QVGA;
        config.jpeg_quality = 8;
        config.fb_count = 1;
    }

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        delay(1000);
        ESP.restart();
    }

    sensor_t * s = esp_camera_sensor_get();
    s->set_framesize(s, FRAMESIZE_QVGA);
}

void sendTelegramMessage(String message) {
    bot.sendMessage(CHAT_ID, message, "");
}

void setup() {
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
    Serial.begin(115200);

    pinMode(FLASH_LED_PIN, OUTPUT);
    pinMode(PIR_PIN, INPUT);
    digitalWrite(FLASH_LED_PIN, flashState);

    configInitCamera();

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
    int motionDetected = digitalRead(PIR_PIN);

    if (motionDetected == HIGH && !sendPhoto) {
        sendPhoto = true;
        sendTelegramMessage("Motion detected! Preparing photo...");
    }

    camera_fb_t* fb = esp_camera_fb_get();
    if (!fb) {
        sendTelegramMessage("Camera capture failed");
        return;
    }

    if (client.connect(serverIP, serverPort)) {
        client.write((const uint8_t*)fb->buf, fb->len);
        esp_camera_fb_return(fb);

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
