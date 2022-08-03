#include "setting.h"


void setup()
{
  stat = 0;
  Serial.begin(9600);

  pinMode(coinSensorPin, INPUT);
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(relay_pin, OUTPUT);

  digitalWrite(relay_pin, LOW);

  attachInterrupt(digitalPinToInterrupt(coinSensorPin), doCounter, FALLING);
  Wire.begin();
  Wire.beginTransmission(0x27);
  lcd.begin(20, 4);
  lcd.setBacklight(255);


  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  pzem.resetEnergy();

  lcd.setCursor(0, 0);
  lcd.print("Connecting WIFI To");
  lcd.setCursor(0, 2);
  lcd.print(ssid);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    lcd.setCursor(pos, 3);
    lcd.print(".");
    pos++;
    skip++;
    if (skip == 100) {
      break;
    }
    if (pos == 16) {
      pos = 0;
    }
  }
  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.print("WiFi connected");
  delay(3000);
  lcd.clear();

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  lcd.setCursor(2, 1);
  lcd.print("NetPie Connected");
  delay(3000);
  lcd.clear();


  lcd.setCursor(4, 1);
  lcd.print("System Ready");
  lcd.setCursor(1, 2);
  lcd.print("Please Coin To Use");

}

void loop()
{
  button_stat = digitalRead(button_pin);

  //sendData_toNetpie();



  if (stat == 0 ) {
    moneyCounter();
    digitalWrite(relay_pin, LOW);

    if (button_stat == LOW) {
      //digitalWrite(relay_pin, HIGH);
      lcd.clear();
      stat = 1;
    }
  }

  if (stat == 1) {
    digitalWrite(relay_pin, HIGH);
    get_pzem_data();
    if (userPowerCount == 0) {
      digitalWrite(relay_pin, LOW);
      lcd.setCursor(0, 3);
      lcd.print("Status    : ");
      lcd.print("__OFF__");
      stat = 0;
      pzem.resetEnergy();
      lcd.setCursor(4, 1);
      lcd.print("System Ready");
      lcd.setCursor(1, 2);
      lcd.print("Please Coin To Use");
    }

  }


}
