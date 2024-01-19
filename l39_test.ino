/*
  Test DCS-BIOS whith LCD ST7920
 */

#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"
#include <PinChangeInterrupt.h>
#include "soiL39.h"
#include <SPI.h>

#include <GyverTimers.h>

#define DEMO 1 // активация автоматической генерации параметров для структур данных (прерывание по таймеру 1)

Display soi(3);

void setup() {
  pinMode(7, INPUT_PULLUP);
  attachPCINT(digitalPinToPCINT(7), kadrNumAdd, FALLING);

  #if (DEMO==1)
    Timer1.setFrequency(1);
    Timer1.enableISR();
  #endif

  DcsBios::setup();
  soi.init();
}

// Прерывание А таймера 1 (тестовое заполнение структуры данных)
ISR(TIMER1_A) {  // пишем  в сериал
  soi.radioData.radioCh < 20 ? soi.radioData.radioCh++ : soi.radioData.radioCh = 0;
  soi.radioData.rsbnCh < 40  ? soi.radioData.rsbnCh++  : soi.radioData.rsbnCh = 0;
  soi.radioData.bprmCh < 999 ? soi.radioData.bprmCh++  : soi.radioData.bprmCh = 0;
  soi.radioData.dprmCh < 999 ? soi.radioData.dprmCh++  : soi.radioData.bprmCh = 0;

  soi.uprData.gears ^= 1;
  soi.uprData.speedBreak ^= 1;
  soi.uprData.flaps < 3 ? soi.uprData.flaps++ : soi.uprData.flaps = 0;
}

// обработчик прерывания PCINT GPIO7
void kadrNumAdd(void) {
  soi.nextKadr();
}

void loop() {
  DcsBios::loop();
  soi.setKadr();
}


/* ********************************************************************** */
// DcsBios::Switch2Pos frontFlaps0("FRONT_FLAPS_0", 6);
// DcsBios::LED frontFlapsUpLamp(0x332c, 0x1000, 2);

// DcsBios::Switch2Pos frontFlaps25("FRONT_FLAPS_25", 7);
// DcsBios::LED frontFlapsToLamp(0x332c, 0x2000, 3);

// DcsBios::Switch2Pos frontFlaps44("FRONT_FLAPS_44", 8);
// DcsBios::LED frontFlapsDnLamp(0x332c, 0x4000, 4);

//DcsBios::RotaryEncoder frontRadioChn("FRONT_RADIO_CHN", "DEC", "INC", 9, 8);

void onBackRadioChnDisplayChange(unsigned int newValue) {
  soi.radioData.radioCh = newValue;
}
DcsBios::IntegerBuffer backRadioChnDisplayBuffer(0x33ce, 0x007f, 0, onBackRadioChnDisplayChange);

void onFrontRsbnChanNavDisplayChange(unsigned int newValue) {
  soi.radioData.rsbnCh = newValue;
}
DcsBios::IntegerBuffer frontRsbnChanNavDisplayBuffer(0x33c4, 0x1fc0, 6, onFrontRsbnChanNavDisplayChange);