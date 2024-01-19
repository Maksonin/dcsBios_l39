#pragma once
#include <U8g2lib.h>
#include <SPI.h>  

class Display {
  private:
    U8G2_ST7920_128X64_F_SW_SPI u8g2 {U8G2_R0, 13, 11, 10};
    uint8_t _kadrNum = 0;
    uint8_t _kadr = 2;
  public:
    Display(uint8_t kadrNum = 1) : _kadrNum ( kadrNum ) {};
    
    void init();
    void setKadr();
    void nextKadr();
    void helloKadr();
    void navKadr();
    void radioKadr();
    void uprKadr();

    struct {
      int speed;
      int height;
    } shData;

    struct {
      int radioCh;
      int rsbnCh;
      int rsbnRezh;
      int bprmCh;
      int dprmCh;
    } radioData;

    struct {
      int flaps;
      int gears;
      int speedBreak;
    } uprData;
};
