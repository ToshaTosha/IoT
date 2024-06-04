#include <SoftwareSerial.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define SEALEVELPRESSURE_HPA (1013.25)

ESP8266WiFiMulti WiFiMulti;

SoftwareSerial sds(0, 2);
Adafruit_BME280 bme; 

const char* CLI_SSID = "me";
const char* CLI_PASS = "123456780";

int pm10, pm25; //sds011

float temperature, pressure, altitude, humidity; //bme280

unsigned long delayTime;

void setup() {
    sds.begin(9600);
    Serial.begin(9600);

    for (uint8_t t = 4; t > 0; t--) {
      Serial.printf("[SETUP] WAIT %d...\n", t);
      Serial.flush();
      delay(1000);
    }
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(CLI_SSID, CLI_PASS);

    if (!bme.begin(0x76)) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
    }
    delayTime = 10000;

    Serial.println();
}

void loop() { 
    // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    read_sds011();
    read_bme280();

   //POST
    StaticJsonDocument<200> doc;
    doc["pm10"] = pm10;
    doc["pm25"] = pm25;

    doc["temperature"] = temperature;
    doc["pressure"] = pressure;
    doc["altitude"] = altitude;
    doc["humidity"] = humidity;

    String serialized_json;
    serializeJson(doc, serialized_json);
    Serial.print("serialized json: ");
    Serial.println(serialized_json);

    http.begin(client, "http://192.168.250.48:8005/items");
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    int httpCode = http.POST(serialized_json);

    if (httpCode > 0) {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
  delay(delayTime);
}

void read_sds011(){
  while (sds.available() && sds.read() != 0xAA) { }
  if (sds.available()) {
    byte buffer[10];
    buffer[0] = 0xAA;
    if (sds.available() >= 9) {
      sds.readBytes(&buffer[1], 9);
      if (buffer[9] == 0xAB) {
        pm25 = (buffer[3] << 8) | buffer[2];
        pm10 = (buffer[5] << 8) | buffer[4];
        Serial.print("PM2.5: ");
        Serial.print(pm25);
        Serial.print(" PM10: ");
        Serial.println(pm10);
      } else {
        Serial.println("Invalid ending byte from SDS011.");
      }
    }
  }
}
void read_bme280() {
    temperature = bme.readTemperature();
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" °C");

    pressure = bme.readPressure() / 100.0F;
    Serial.print("Pressure = ");
    Serial.print(pressure);
    Serial.println(" hPa");

    altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    Serial.print("Approx. Altitude = ");
    Serial.print(altitude);
    Serial.println(" m");

    humidity = bme.readHumidity();
    Serial.print("Humidity = ");
    Serial.print(humidity);
    Serial.println(" %");

    
