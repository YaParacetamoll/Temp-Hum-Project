// Lib For LED Matrix Display
#include "Arduino_LED_Matrix.h"
#include "grid_matrix.h"
ArduinoLEDMatrix matrix;

// Lib For MQTT
#include <ArduinoMqttClient.h>
#include <WiFiS3.h>
#include "arduino_secrets.h"

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

//// Lib lora server
#include <SPI.h>
#include <RH_RF95.h>
#define RFM95_CS 10
#define RFM95_RST 7
#define RFM95_INT 2
#define RF95_FREQ 909.56
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
RH_RF95 rf95(RFM95_CS, RFM95_INT);

const char broker[] = "phycom.it.kmitl.ac.th"; //"broker.hivemq.com";
int port = 1883;
const char send_topic[] = "temp-hum-pj/send";

//set interval for sending messages (milliseconds)
const long interval = 500;
unsigned long previousMillis = 0;

int status = WL_IDLE_STATUS;  // the WiFi radio's status


// Lib For Sensor & LCD Display
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include <LCDI2C_Multilingual.h>


Adafruit_SHT31 sht31 = Adafruit_SHT31();

void loadding(){
  matrix.renderBitmap(wifi_icon_connecting, 8, 12);
}

void setupNetwork() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    loadding();
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
}


void setupMQTT() {
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  setupNetwork();

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1)
      ;
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.clear();

  while (!Serial)
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens
  setupMQTT();
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  while (!Serial);
  Serial.begin(9600);
  delay(10);

  Serial.println("Arduino LoRa RX Test!");
  
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);

  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}




void checkWifiIsConnecting() {
  if (WiFi.status() == WL_CONNECTED) {
    matrix.renderBitmap(wifi_icon, 8, 12);
  } else {
    matrix.renderBitmap(wifi_icon_not_connected, 8, 12);
  }
}

void publishMessageMQTT(const String &message) {
  mqttClient.poll();
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    mqttClient.beginMessage(send_topic);
    mqttClient.print(message);
    mqttClient.endMessage();
    Serial.print("Published to MQTT: ");
    Serial.println(message);
  }
}
void loop() {
  checkWifiIsConnecting();
  char buff1[20], buff2[20], buff3[50];
   if (rf95.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    
    if (rf95.recv(buf, &len))
    {
      // แปลงข้อความจาก uint8_t buffer เป็น String
    String receivedMessage = String((char*)buf);  // แปลงข้อมูลจาก uint8_t array เป็น String
    
    Serial.print("Got: ");
    Serial.println(receivedMessage);  // แสดงผลข้อความที่ได้รับ

    Serial.print("RSSI: ");
    Serial.println(rf95.lastRssi(), DEC);  // แสดงค่า RSSI ของการส่ง

    // ส่งข้อมูลที่ได้รับจาก LoRa ไปยัง MQTT broker
    publishMessageMQTT(receivedMessage);

    // ส่งข้อความตอบกลับ
    uint8_t data[] = "And hello back to you";
    rf95.send(data, sizeof(data));
    rf95.waitPacketSent();
    Serial.println("Sent a reply");
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
}