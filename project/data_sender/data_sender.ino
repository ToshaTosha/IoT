//#include <SDS011.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//float p10, p25;
//int error;

//SDS011 my_sds;
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; 
unsigned long delayTime;

void setup() {
  //my_sds.begin(D3, D4); //RX, TX
    Serial.begin(9600);
    while(!Serial);

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
    
    Serial.println("-- Default Test --");
    delayTime = 1000;

    Serial.println();
}

void loop() { 
    printValues();
    delay(delayTime);
}

void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
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
