
void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection…");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password))
    {
      Serial.println("connected");
      client.subscribe("@msg/power");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }
  Serial.println(message);
  if (String(topic) == "@msg/set_ft/ft") {
    int Ft = message.toInt();
    delay(15);
    String data = "{\"data\": {\"set_ft\":" + String(Ft) + "}}";
    Serial.println(data);
    data.toCharArray(msg, (data.length() + 1));
    client.publish("@shadow/data/update", msg);
  }
}


void sendData_toNetpie()
{
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();

  unsigned long currentMillis = millis();

  if (currentMillis - Millis_netpie >= 2000)
  {
    Millis_netpie = currentMillis;
   
    // jason format = { “data”:{ “field name 1”: value 1, “field name 2”: value 2, …, “field name n”: value n }}

    String data = "{\"data\": {\"Voltage\":" + String(voltage) + ", \"Current\":" + String(current) +
                  ", \"Power\":" + String(power) + ", \"Energy\":" + String(energy) + ", \"Frequency\":" + String(frequency) +
                  ", \"Pf\":" + String(pf) + ", \"Electric_bill\":" + String(Electric_bill) + ", \"FT\":" + String(Ft) + "}}";

    Serial.println(data);
    data.toCharArray(msg, (data.length() + 1));
    client.publish("@shadow/data/update", msg);

    Serial.println("Send All Data To Netpie Complete");
    Serial.println("");
  }
}
