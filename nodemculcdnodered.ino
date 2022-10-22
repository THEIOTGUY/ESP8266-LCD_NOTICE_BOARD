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
