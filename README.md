# ESP8266-lcd_notice_board
this project is node-red based lcd notice-board where you can display any text on lcd using node-red dashboard and esp8266, you can display text of 
32-character, 16 character per line, this project works with node-red using MQTT protocol.

## COMPONENTS USED :-

1. 16x2 lcd
2. I2C driver
3. nodemcu/ESP8266
4. 5v power supply

## CIRCUIT DIAGRAM

![image](https://user-images.githubusercontent.com/102857010/197333289-b3bf131d-da17-4a32-b580-52129fd4fd51.png)

## CODE

`````
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <MQTT.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

WiFiClient net;
MQTTClient client;
String ssid="Vaidande_2";
String pass="960647@vaidande";
unsigned long lastMillis = 0;
void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
   Serial.print("\nconnecting...");
  while (!client.connect("nodemcu_client")) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");

  client.subscribe("nodemcu/lcd");
 
 
}
void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
    if(topic=="nodemcu/lcd"){
      lcd.clear();
   lcd.print(payload); // Start Printing

            
    }
    }
void setup(){
  Wire.begin(2,0);
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.print("hello sir");
   client.begin("192.168.0.105", net);
  client.onMessage(messageReceived);

  connect();
}
void loop(){
  // Nothing Absolutely Nothing!
 client.loop();
  delay(200); // <- fixes some issues with WiFi stability
  if (!client.connected()) {
    connect();
       }
}
`````

https://user-images.githubusercontent.com/102857010/197333406-94ff4aad-ee83-42ee-8ef7-ad7f0847dfbd.mp4


## WORKING :-

