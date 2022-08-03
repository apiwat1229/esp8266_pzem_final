
void doCounter() {
  isCounter = true;
  count++;
}

void moneyCounter() {
  if (isCounter == true) {
    isCounter = false;
    //Serial.println(count);
    delay(500);
  }
  if (pwm != 1000 && count != 0 ) {
    pwm = pwm + 1;
  }
  if (pwm == 1000) {
    pwm = 0;
    if (count == 10) {
      total_ten = total_ten + 1;
      ten = total_ten * 10; // มูลค่าเหรียญ
      ten_count = 10; // ขนิดเหรียญ
      Serial.print("ชนิดเหรียญล่าสุด: ");
      Serial.print(ten_count); Serial.println(" บาท");
      Serial.println();
    }
    if (count == 5) {
      total_five = total_five + 1;
      five = total_five * 5;
      five_count = 5;
      Serial.print("ชนิดเหรียญล่าสุด: ");
      Serial.print(five_count); Serial.println(" บาท");
      Serial.println();
    }
    if (count == 1) {
      total_one = total_one + 1;
      one = total_one * 1;
      one_count = 1;
      Serial.print("ชนิดเหรียญล่าสุด: ");
      Serial.print(one_count); Serial.println(" บาท");
      Serial.println();
    }

    all_total = one + five + ten;
    count  = 0;

    Serial.print("   รวมชนิดเหรียญ 10 บาท: ");
    Serial.print(total_ten); Serial.println(" เหรียญ");
    Serial.print("   รวมชนิดเหรียญ  5 บาท: ");
    Serial.print(total_five); Serial.println(" เหรียญ");
    Serial.print("   รวมชนิดเหรียญ  1 บาท: ");
    Serial.print(total_one); Serial.println(" เหรียญ");
    Serial.println();
    Serial.print("   ยอดเงินรวมทั้งหมด: ");
    Serial.print(all_total); Serial.println(" บาท");
    Serial.println();



    result = all_total * money_to_watt;
    sysStatus = true;
    
    Serial.print("จำนวนวัตต์ที่ใช้ได้ : ");
    Serial.print(result);
    Serial.print(" วัตต์");

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Amount  : ");
    lcd.print(all_total);
    lcd.print(" Bath");
    lcd.setCursor(0, 1);
    lcd.print("TotalWatt : ");
    lcd.print(result);
    lcd.print(" W.");
    lcd.setCursor(0, 3);
    lcd.print("Press Button To Use!");

    Serial.println();



  }
}


float moneyToWatt(int money) {

  result = money * money_to_watt;

  return result;

}

void stat_Working () {
  float wattCoundown = result - energy;
  Serial.println (wattCoundown);
}
