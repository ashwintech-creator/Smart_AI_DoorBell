# **ESP32-CAM Motion Detection with Telegram Bot**  

## **Welcome to Project Mayhem**  
You don’t talk about this project. You build it. You run it. You own it. This isn’t some toy—you’re setting up a real-time motion detection system that sends alerts straight to your Telegram. Surveillance. Security. Control.  

---  

## **Hardware Requirements**  
- **ESP32-CAM** – The eye that never blinks.  
- **PIR Motion Sensor** – Detects movement. No false promises. Just signals.  
- **Telegram Bot API** – Pushes alerts straight to you. No delays. No excuses.  
- **MicroSD Card (optional)** – Store images if you’re the paranoid type.  
- **FTDI Programmer** – Because the ESP32-CAM doesn’t come with training wheels.  
- **Jumper Wires** – Solder if you have to. Adapt. Overcome.  

---  

## **How It Works**  
1. **Motion Detected:** PIR sensor picks up movement. No second chances.  
2. **Image Captured:** ESP32-CAM snaps a shot. Proof in pixels.  
3. **Instant Telegram Alert:** The bot sends the image to your chat. Real-time. No buffering.  
4. **Act or Ignore:** Your call. Monitor. React. Secure.  

---  

## **Installation & Setup**  
### **1. Flash the ESP32-CAM**  
- Install **Arduino IDE** or **ESP-IDF**. Choose your weapon.  
- Add ESP32 board support (Preferences > Additional Board Manager URL).  
- Select **AI-Thinker ESP32-CAM** in Board Manager.  
- Flash the firmware using an **FTDI Programmer**.  

### **2. Wiring the PIR Sensor**  
| PIR Sensor | ESP32-CAM |  
|------------|-----------|  
| VCC        | 3.3V      |  
| GND        | GND       |  
| OUT        | GPIO 13   |  

### **3. Configure Telegram Bot**  
- Open Telegram. Talk to **BotFather**. Create a bot. Get your API token.  
- Use `@userinfobot` to get your Telegram Chat ID.  
- Update your ESP32-CAM script with `BOT_TOKEN` and `CHAT_ID`.  

### **4. Deploy & Monitor**  
- Power up the ESP32-CAM.  
- Open the serial monitor. Debug like a pro.  
- Walk into the detection zone. Watch the bot send the image.  
- Celebrate. You just built your own security system.  

---  

## **Code Overview**  
- **`camera_init()`** – Sets up the ESP32-CAM module.  
- **`motion_detect()`** – Reads PIR sensor output.  
- **`capture_image()`** – Captures and stores the image.  
- **`send_telegram_alert()`** – Pushes alerts to Telegram.  
- **`loop()`** – Runs the entire workflow.  

---  

## **Test the System**  
- Send `/start` to your Telegram bot to view available commands.  
- Use `/photo` to manually capture an image.  
- Use `/flash` to toggle the LED flash.  
- When motion is detected, the ESP32-CAM will automatically send a photo.  

---  

## **Rules of This Project**  
1. If this is your first time working with ESP32-CAM, you *have* to flash the right firmware.  
2. You do not overcomplicate it. Simplicity is key.  
3. Debug like your life depends on it.  
4. If it doesn’t work, you make it work.  

---  

## **Why?**  
Because knowledge is power, and power should be in your hands—not some corporation’s. Build it. Use it. Own it.  

---  

**License:** Do whatever you want with this. Just don’t be stupid.  

