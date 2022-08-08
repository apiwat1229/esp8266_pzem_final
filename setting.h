#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <PZEM004Tv30.h>
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

const byte  PZEM_RX_PIN =   D6;
const byte  PZEM_TX_PIN =   D5;
const byte  coinSensorPin   =   D3;
const byte  button_pin =  D4;
const byte  relay_pin =  D7;

bool button_stat = false;

const char* ssid = "Kiti_2.4G_EXT";
const char* password = "0624368558";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "1db944a6-7422-41a4-9465-7245b1ed3812";
const char* mqtt_username = "3e6nw1Tkp2vf6zV7STrCt4n9RZMcxyqy";
const char* mqtt_password = "utbvJiqVcIoL2uCH_Coky3ciYxClg-hd";

float Ft =  4.95;

char msg[150];
String payload;

float voltage, current, power, energy, frequency, pf;
float kWh_1 = 0, kWh_2 = 0,  kWh_3 = 0;
float total_kWh = 0, final_kWh = 0 , Electric_bill = 0;

unsigned long Millis_netpie = 0, Millis_pzem = 0, timer1 = 0;

byte pos = 0;
byte stat = 0;
byte skip = 0;
int pwm = 0;
bool sysStatus = false;

int userPowerCount = 0;
int one = 0;            // ตัวแปรที่ใช้แทนมูลค่าเหรียญ ในที่นี้ใช้แทนเหรียญ 1 บาท
int one_count = 0;      // ตัวแปรที่ใช้แทนขนิดเหรียญ ในที่นี้ใช้แทนเหรียญ 1 บาท
int total_one = 0;      // ตัวแปรสำหรับนับจำนวนเหรียญแต่ละชนิด ในที่นี้ใช้แทนเหรียญ 1 บาท

int five = 0;           // ตัวแปรที่ใช้แทนมูลค่าเหรียญ ในที่นี้ใช้แทนเหรียญ 5 บาท
int five_count = 0;     // ตัวแปรที่ใช้แทนขนิดเหรียญ ในที่นี้ใช้แทนเหรียญ 5 บาท
int total_five = 0;     // ตัวแปรสำหรับนับจำนวนเหรียญแต่ละชนิด ในที่นี้ใช้แทนเหรียญ 5 บาท

int ten = 0;            // ตัวแปรที่ใช้แทนมูลค่าเหรียญ ในที่นี้ใช้แทนเหรียญ 10 บาท
int ten_count = 0;      // ตัวแปรที่ใช้แทนขนิดเหรียญ ในที่นี้ใช้แทนเหรียญ 10 บาท
int total_ten = 0;      // ตัวแแแปรสำหรับนับจำนวนเหรียญแต่ละชนิด ในที่นี้ใช้แทนเหรียญ 10 บาท

int all_total = 0;      // ตัวแแแปรสำหรับเก็บผลรวมจำนวนเงินทั้งหมด
int money_to_watt = 236;
int result;

boolean isCounter = false;
int count = 0;

void ICACHE_RAM_ATTR doCounter();

LiquidCrystal_PCF8574 lcd(0x27);
WiFiClient espClient;
PubSubClient client(espClient);
SoftwareSerial pzemSWSerial(PZEM_RX_PIN, PZEM_TX_PIN);
PZEM004Tv30 pzem(pzemSWSerial);
