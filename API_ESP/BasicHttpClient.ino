#include <Arduino.h>
#include "ArduinoJson.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

const char* CLI_SSID = "me";
const char* CLI_PASS = "123456780";

String LOCATION = "kitchen";

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(CLI_SSID, CLI_PASS);
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    //POST
    if (Serial.available() > 0){//user value input
      String user_input = Serial.readString();
      float value = user_input.toFloat();

      StaticJsonDocument<200> doc;
      doc["value"] = value;
      doc["location"] = LOCATION;
      doc["device_id"] = 1;
      doc["timestamp"] = "2024-03-21 10:10:10";//СДЕЛАТЬ ПОЛУЧЕНИЕ ТЕКУЩЕЙ ДАТЫ

      String serialized_json;
      serializeJson(doc, serialized_json);
      Serial.print("serialized json: ");
      Serial.println(serialized_json);

      // configure traged server and url
      http.begin(client, "http://192.168.32.34:8005/temperature");  // HTTP
      http.addHeader("Content-Type", "application/json");

      Serial.print("[HTTP] POST...\n");
      // start connection and send HTTP header and body
      int httpCode = http.POST(serialized_json);

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK) {
          const String& payload = http.getString();
          Serial.println("received payload:\n<<");
          Serial.println(payload);
          Serial.println(">>");
        }
      } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    }
    
    //GET
    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://192.168.32.34:8005/temperature/"+LOCATION)) {  // HTTP

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
          //get json
          DynamicJsonDocument doc(1024);
          deserializeJson(doc, payload);

          ////РАССЧИТАТЬ СРЕДНЕЕ
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.println("[HTTP] Unable to connect");
    }
  }

  delay(10000);
}
