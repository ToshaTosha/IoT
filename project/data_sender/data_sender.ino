#include <SDS011.h>
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

SDS011 my_sds;
Adafruit_BME280 bme; 

const char* CLI_SSID = "me";
const char* CLI_PASS = "123456780";

//float p10, p25; //sds011
//int error;

float temperature, pressure, altitude, humidity; //bme280

unsigned long delayTime;

void setup() {
    //my_sds.begin(D3, D4); //RX, TX
    Serial.begin(9600);
    Serial.println("START");

    for (uint8_t t = 4; t > 0; t--) {
      Serial.printf("[SETUP] WAIT %d...\n", t);
      Serial.flush();
      delay(1000);
    }
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(CLI_SSID, CLI_PASS);

    unsigned status;
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
    delayTime = 10000;

    Serial.println();
}

void loop() { 
    // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    //POST
    read_bme280();

    StaticJsonDocument<200> doc;
    doc["temperature"] = temperature;
    doc["pressure"] = pressure;
    doc["altitude"] = altitude;
    doc["humidity"] = humidity;

    String serialized_json;
    serializeJson(doc, serialized_json);
    Serial.print("serialized json: ");
    Serial.println(serialized_json);

    // configure traged server and url
    http.begin(client, "http://192.168.10.48:8005/items");
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
  delay(delayTime);
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

    Serial.println();
}

// void loop(){
  
  
  // if (sds.available()) {
  //   byte buffer[10];
  //   sds.readBytes(buffer, 10);

  //   // Считываем данные PM2.5 и PM10
  //   unsigned int pm25 = (buffer[3] * 256 + buffer[2]);
  //   unsigned int pm10 = (buffer[5] * 256 + buffer[4]);

  //   // Выводим данные в монитор последовательного порта
  //   Serial.print("PM2.5: ");
  //   Serial.print(pm25);
  //   Serial.println(" PM10: ");
  //   Serial.println(pm10);
  // }
  // else{
  //   Serial.println("sds not available");
  // }
  // delay(1000);
  
//}
