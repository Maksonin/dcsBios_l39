/*
  Test DCS-BIOS whith LCD ST7920
 */

#define DCSBIOS_IRQ_SERIAL
//#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"
#include <PinChangeInterrupt.h>
#include "soiL39.h"
#include <SPI.h>

// #include <GyverTimers.h>

#define DEMO 0 // активация автоматической генерации параметров для структур данных (прерывание по таймеру 1)

Display soi(3);

void setup() {
  pinMode(7, INPUT_PULLUP);
  attachPCINT(digitalPinToPCINT(7), kadrNumAdd, FALLING);

  // #if (DEMO==1)
  //   Timer1.setFrequency(1);
  //   Timer1.enableISR();
  // #endif

  DcsBios::setup();
  soi.init();
}

// Прерывание А таймера 1 (тестовое заполнение структуры данных)
// ISR(TIMER1_A) {  // пишем  в сериал
  
//   soi.shData.speed < 999 ? soi.shData.speed += 100 : soi.shData.speed = 0;
//   soi.shData.height < 10999 ? soi.shData.height += 100 : soi.shData.height = 0;

//   soi.radioData.radioCh < 20 ? soi.radioData.radioCh++ : soi.radioData.radioCh = 0;
//   soi.radioData.rsbnCh < 40  ? soi.radioData.rsbnCh++  : soi.radioData.rsbnCh = 0;
//   soi.radioData.bprmCh < 999 ? soi.radioData.bprmCh++  : soi.radioData.bprmCh = 0;
//   soi.radioData.dprmCh < 999 ? soi.radioData.dprmCh++  : soi.radioData.bprmCh = 0;

//   soi.uprData.gearN ^= 1;
//   soi.uprData.gearR ^= 1;
//   soi.uprData.gearL ^= 1;
//   soi.uprData.airBreak ^= 1;
//   soi.uprData.flaps < 3 ? soi.uprData.flaps++ : soi.uprData.flaps = 0;
// }

// обработчик прерывания PCINT GPIO7
void kadrNumAdd(void) {
  soi.nextKadr();
}

void loop() {
  DcsBios::loop();
  
  //noInterrupts(); // отключение прерываний на время формирования изображения

  soi.setKadr();

  //interrupts(); // включение прерываний

}

/* ********************************************************************** */
// DcsBios::Switch2Pos frontFlaps0("FRONT_FLAPS_0", 6);
// DcsBios::LED frontFlapsUpLamp(0x332c, 0x1000, 2);

// DcsBios::Switch2Pos frontFlaps25("FRONT_FLAPS_25", 7);
// DcsBios::LED frontFlapsToLamp(0x332c, 0x2000, 3);

// DcsBios::Switch2Pos frontFlaps44("FRONT_FLAPS_44", 8);
// DcsBios::LED frontFlapsDnLamp(0x332c, 0x4000, 4);

//DcsBios::RotaryEncoder frontRadioChn("FRONT_RADIO_CHN", "DEC", "INC", 9, 8);

/* Радио параметры */
// void onBackRadioChnDisplayChange(unsigned int newValue) {
//   soi.radioData.radioCh = newValue;
// }
// DcsBios::IntegerBuffer backRadioChnDisplayBuffer(0x33ce, 0x007f, 0, onBackRadioChnDisplayChange);

// void onFrontRsbnChanNavDisplayChange(unsigned int newValue) {
//   soi.radioData.rsbnCh = newValue;
// }
// DcsBios::IntegerBuffer frontRsbnChanNavDisplayBuffer(0x33c4, 0x1fc0, 6, onFrontRsbnChanNavDisplayChange);

// void onFrontRsbnModeChange(unsigned int newValue) {
//      soi.radioData.rsbnRezh = newValue;
// }
// DcsBios::IntegerBuffer frontRsbnModeBuffer(0x335c, 0x0006, 1, onFrontRsbnModeChange);

/* **************************************** */
/* Закрылки */

// состояние лампы "Закрылки убраны"
void onFrontFlapsUpLampChange(unsigned int newValue) {
  soi.uprData.flapsUp = newValue;
}
DcsBios::IntegerBuffer frontFlapsUpLampBuffer(0x332c, 0x1000, 12, onFrontFlapsUpLampChange);

// состояние лампы "Закрылки во взлётном положении"
void onFrontFlapsToLampChange(unsigned int newValue) {
  soi.uprData.flapsV = newValue;
}
DcsBios::IntegerBuffer frontFlapsToLampBuffer(0x332c, 0x2000, 13, onFrontFlapsToLampChange);

// состояние лампы "Закрылки в посадочном положении"
void onFrontFlapsDnLampChange(unsigned int newValue) {
    soi.uprData.flapsP = newValue;
}
DcsBios::IntegerBuffer frontFlapsDnLampBuffer(0x332c, 0x4000, 14, onFrontFlapsDnLampChange);

/* **************************************** */
/* Шасси правое */

void onFrontRGearDownLampChange(unsigned int newValue) {
    soi.uprData.gearR = newValue;
}
DcsBios::IntegerBuffer frontRGearDownLampBuffer(0x3204, 0x1000, 12, onFrontRGearDownLampChange);

/* **************************************** */
/* Шасси носовое */

void onFrontNGearDownLampChange(unsigned int newValue) {
    soi.uprData.gearN = newValue;
}
DcsBios::IntegerBuffer frontNGearDownLampBuffer(0x3204, 0x0800, 11, onFrontNGearDownLampChange);

/* **************************************** */
/* Шасси левое */
void onFrontLGearDownLampChange(unsigned int newValue) {
    soi.uprData.gearL = newValue;
}
DcsBios::IntegerBuffer frontLGearDownLampBuffer(0x3204, 0x0400, 10, onFrontLGearDownLampChange);

/* **************************************** */
/* Воздушный тормоз */

void onFrontAirbrakeLampChange(unsigned int newValue) {
    soi.uprData.airBreak = newValue;
}
DcsBios::IntegerBuffer frontAirbrakeLampBuffer(0x3204, 0x8000, 15, onFrontAirbrakeLampChange);

/* **************************************** */
/* Воздушная скорость */

void onIasEuIntChange(unsigned int newValue) {
    soi.shData.speed = newValue;
}
DcsBios::IntegerBuffer iasEuIntBuffer(0x042c, 0xffff, 0, onIasEuIntChange);

/* **************************************** */
/* Высота */

void onAltMslFtChange(unsigned int newValue) {
    soi.shData.height = newValue;
}
DcsBios::IntegerBuffer altMslFtBuffer(0x0434, 0xffff, 0, onAltMslFtChange);