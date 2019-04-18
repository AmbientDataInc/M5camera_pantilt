/*
 * JoyStickでSG90を制御
 */
#include <M5Stack.h>
#include <WiFi.h>
#include "Wire.h"
#include "JoyStick.h"

const char* ssid = "ssid";
const char* password = "password";
String m5camera_ipaddr = "192.168.11.22";

WiFiClient client;

#define JOY_ADDR 0x52

JOYSTICK js = JOYSTICK();

void setup() {
    M5.begin();
    M5.Lcd.clear();
    //disable the speak noise
    dacWrite(25, 0);

    WiFi.begin(ssid, password);  // Wi-Fiネットワークに接続する
    while (WiFi.status() != WL_CONNECTED) {  // 接続したか調べる
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  // ローカルIPアドレスをプリントする

    Wire.begin(21, 22, 400000);
    js.begin(JOY_ADDR);

    M5.Lcd.setTextSize(3);
    M5.Lcd.print("Ready");
}

#define PAN 0
#define TILT 1

void send_req(String cmd) {
    String url = "/control?var=pantilt&val=";
    Serial.println(url + cmd);

    if (!client.connect(m5camera_ipaddr.c_str(), 80)) {
        Serial.println("connection faile");
        return;
    }
    client.print(String("GET ") + url + cmd + " HTTP/1.1\r\n" +
                        "Host: " + m5camera_ipaddr + "\r\n" + 
                        "Connection: close\r\n\r\n");

    while(client.available()){
        String line = client.readStringUntil('\r');
    }
}

void loop() {
    js.read();
    if (js.x() || js.y()) {
        String cmd = "p";
        if (js.x() > 0) cmd += "+";
        else if (js.x() < 0) cmd += "-";
        else cmd += "0";
        if (js.y() > 0) cmd += "t+";
        else if (js.y() < 0) cmd += "t-";
        else cmd += "t0";
        send_req(cmd);
    }
    delay(200);
}
