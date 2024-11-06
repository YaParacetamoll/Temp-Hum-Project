// Lib For LoRa
#include <SPI.h>
#include <LoRa.h>

#define ss 10
#define rst 7 // 7-12
#define dio0 2

// Lib For Sensor & LCD Display
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include <LCDI2C_Multilingual.h>

LCDI2C_Symbols lcd(0x27, 16, 2);  // I2C address: 0x27; Display size: 16x2

bool enableHeater = false;
uint8_t loopCnt = 0;

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setupTempSensor() {
  Serial.println("SHT31 test");
  if (!sht31.begin(0x44)) {  // Set to 0x44, 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }

  Serial.print("Heater Enabled State: ");
  if (sht31.isHeaterEnabled())
    Serial.println("ENABLED");
  else
    Serial.println("DISABLED");
}



int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;
  setupTempSensor();
  lcd.init();
  lcd.backlight();
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
}

void displayToLcd(String line1, String line2) {
  lcd.setCursor(0, 0);
  //lcd.println("Temperature:25°C" , line1);
  lcd.println(line1);
  lcd.println(line2);
}

struct tempAndHumStruct {
  float temp;
  float hum;
};

void getTempAndHum(struct tempAndHumStruct *source) {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if (!isnan(t) && !isnan(h)) {  // check if 'is not a number'

    // Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
    source->temp = t;
    source->hum = h;
  } else {
    // Serial.println("Failed to read temperature");
  }

  delay(1000);

  // Toggle heater enabled state every 30 seconds
  // An ~3.0 degC temperature increase can be noted when heater is enabled
  if (loopCnt >= 30) {
    enableHeater = !enableHeater;
    sht31.heater(enableHeater);
    Serial.print("Heater Enabled State: ");
    if (sht31.isHeaterEnabled())
      Serial.println("ENABLED");
    else
      Serial.println("DISABLED");

    loopCnt = 0;
  }
  loopCnt++;
}

void loop() {
  struct tempAndHumStruct tempAndHum;
  getTempAndHum(&tempAndHum);
  char buff1[20], buff2[20], buff3[50];
  snprintf(buff1, sizeof(buff1), "Temp:   %.2f°C", tempAndHum.temp);
  snprintf(buff2, sizeof(buff2), "Hum :   %.2f", tempAndHum.hum);
  displayToLcd(buff1, buff2);
  snprintf(buff3, sizeof(buff3), "{\"temp\":\"%.2f\",\"hum\":\"%.2f\"}", tempAndHum.temp, tempAndHum.hum);

  // send packet
  LoRa.beginPacket();
  LoRa.print(buff3);
  //LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
