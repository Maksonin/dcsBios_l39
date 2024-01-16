/*
  Tell DCS-BIOS to use a serial connection and use interrupt-driven
  communication. The main program will be interrupted to prioritize
  processing incoming data.
  
  This should work on any Arduino that has an ATMega328 controller
  (Uno, Pro Mini, many others).
 */
#define DCSBIOS_IRQ_SERIAL

#include <U8g2lib.h>
#include <SPI.h>
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R2, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10);

//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define switchMod 0

#include "DcsBios.h"
//#include "l39.h"
//#include "y52.h"

void setup() {
  DcsBios::setup();
  u8g2.begin(); 
  u8g2.firstPage();
  do {
    u8g2.drawFrame(0,0,128,64);
    u8g2.setFont(u8g2_font_5x8_t_cyrillic );
    u8g2.drawStr(30,8,"DCS-BIOS L39");
    u8g2.drawStr(2,16,"Radio channel: ");
    u8g2.drawStr(2,24,"RSBN nav: ");
    u8g2.drawStr(2,32,"RSBN land: ");
  } while ( u8g2.nextPage() );
}

void loop() {
  DcsBios::loop();


}

