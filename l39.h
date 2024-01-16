#if (switchMod == 0)
  DcsBios::Switch2Pos frontFlaps0("FRONT_FLAPS_0", 6);
  DcsBios::LED frontFlapsUpLamp(0x332c, 0x1000, 2);

  DcsBios::Switch2Pos frontFlaps25("FRONT_FLAPS_25", 7);
  DcsBios::LED frontFlapsToLamp(0x332c, 0x2000, 3);

  DcsBios::Switch2Pos frontFlaps44("FRONT_FLAPS_44", 8);
  DcsBios::LED frontFlapsDnLamp(0x332c, 0x4000, 4);

  //DcsBios::RotaryEncoder frontRadioChn("FRONT_RADIO_CHN", "DEC", "INC", 9, 8);

  void onBackRadioChnDisplayChange(unsigned int newValue) {
    lcd.setCursor(15,1);
    lcd.print("     ");
    lcd.setCursor(15,1);
    lcd.print(newValue);
  }
  DcsBios::IntegerBuffer backRadioChnDisplayBuffer(0x33ce, 0x007f, 0, onBackRadioChnDisplayChange);

  void onFrontRsbnChanNavDisplayChange(unsigned int newValue) {
    lcd.setCursor(11,2);
    lcd.print("     ");
    lcd.setCursor(11,2);
    lcd.print(newValue);
  }
  DcsBios::IntegerBuffer frontRsbnChanNavDisplayBuffer(0x33c4, 0x1fc0, 6, onFrontRsbnChanNavDisplayChange);

  void onFrontRsbnChanLandDisplayChange(unsigned int newValue) {
    lcd.setCursor(11,3);
    lcd.print("     ");
    lcd.setCursor(11,3);
    lcd.print(newValue);
  }
  DcsBios::IntegerBuffer frontRsbnChanLandDisplayBuffer(0x33c8, 0x007f, 0, onFrontRsbnChanLandDisplayChange);

#endif