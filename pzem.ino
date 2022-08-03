
void get_pzem_data()
{
  unsigned long currentMillis = millis();

  if (currentMillis - Millis_pzem >= 2000)
  {
    Millis_pzem = currentMillis;

    voltage = pzem.voltage();
    current = pzem.current();
    power = pzem.power();
    energy = pzem.energy();
    frequency = pzem.frequency();
    pf = pzem.pf();

    if (isnan(voltage)) {
      Serial.println("Error reading voltage");
    } else if (isnan(current)) {
      Serial.println("Error reading current");
    } else if (isnan(power)) {
      Serial.println("Error reading power");
    } else if (isnan(energy)) {
      Serial.println("Error reading energy");
    } else if (isnan(frequency)) {
      Serial.println("Error reading frequency");
    } else if (isnan(pf)) {
      Serial.println("Error reading power factor");
    } else {

      Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
      Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
      Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
      Serial.print("Energy: ");       Serial.print(energy, 3);     Serial.println("kWh");
      Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
      Serial.print("PF: ");           Serial.println(pf);
      Serial.print("test : ");

      userPowerCount = result - (energy * 1000);

      lcd.setCursor(0, 0);
      lcd.print("TotalWatt : ");
      lcd.print(userPowerCount);
      lcd.print(" W.  ");

      lcd.setCursor(0, 1);
      lcd.print("Current : ");
      lcd.print(current);
      lcd.print(" A. ");

      lcd.setCursor(0, 2);
      lcd.print("Power : ");
      lcd.print(power);
      lcd.print(" W.  ");

      lcd.setCursor(0, 3);
      lcd.print("Status : ");
      lcd.print("___ON___ ");
    }

    Serial.println("");



  }
}


float cal_cost() {
  if (energy >= 1 && energy <= 150) {
    kWh_1 = energy * 3.2484;
  }
  if (energy > 150) {
    kWh_1 = 150 * 3.2484;
  }

  //หน่วยที่  151    -  400 หน่วยละ 4.2218  บาท

  if (energy >= 151 && energy <= 400) {
    kWh_2 = energy * 4.2218;
  }
  if (energy > 400) {
    kWh_2 = 250 * 4.2218;
    //401        -- >   หน่วยละ 4.4217  บาท
    kWh_3 = (energy - 400) * 4.4217;
  }

  //รวมค่าใช้จ่ายทั้งหมด
  total_kWh = kWh_1 + kWh_2 + kWh_3;
  final_kWh = total_kWh + 38.22 + (energy * Ft);

  Electric_bill = final_kWh + (final_kWh * 0.07);

  return Electric_bill;
}
