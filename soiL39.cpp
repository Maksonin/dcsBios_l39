#include "Arduino.h"
#include "soiL39.h"

// инициализация дисплея и вывод начального кадра
void Display::init(){
  u8g2.begin();
}

void Display::setKadr(){
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);
  switch (_kadr){
    case 0: Display::navKadr(); break;
    case 1: Display::radioKadr(); break;
    case 2: Display::uprKadr(); break;
    default: break;
  }
  u8g2.sendBuffer();
}

void Display::nextKadr(){
  _kadr++;
  if(_kadr == _kadrNum)
    _kadr = 0;
}

void Display::helloKadr(){
  // u8g2.setFont(u8g2_font_ncenB10_tr);
  // u8g2.drawStr(1,15,"Hello World!");
}

// ****** ФОРМИРОВАНИЕ КАДРА НАВИГАЦИЯ ****** 
void Display::navKadr(){
  // u8g2.setFont(u8g2_font_6x12_t_cyrillic);
  // u8g2.drawUTF8(25,10,"--НАВИГАЦИЯ--");
}

// ****** ФОРМИРОВАНИЕ КАДРА РАДИО ****** 
void Display::radioKadr(){
  u8g2.setFont(u8g2_font_6x12_t_cyrillic);
  // u8g2.drawUTF8(37,10,"--РАДИО--");
  u8g2.drawUTF8(4,11,"Радио");
  u8g2.drawUTF8(38,11,"канал:");
  u8g2.setCursor(75, 12);u8g2.print(radioData.radioCh);

  u8g2.drawLine(0,15,128,15);

  u8g2.drawUTF8(4,36,"РСБН");
  u8g2.drawUTF8(38,30,"канал:");
  u8g2.setCursor(75, 30);u8g2.print(radioData.rsbnCh);
  u8g2.drawUTF8(38,42,"режим:");
  //
  if(radioData.rsbnRezh == 0)
    u8g2.drawUTF8(75,42,"ПРОБИВ");
  if(radioData.rsbnRezh == 1)
    u8g2.drawUTF8(75,42,"НАВ");
  if(radioData.rsbnRezh == 2)
    u8g2.drawUTF8(75,42,"ПОС");

  u8g2.drawLine(0,50,128,50);

  u8g2.setFont(u8g2_font_6x12_t_cyrillic);
  u8g2.drawUTF8(9,60,"БПРМ:");
  u8g2.setCursor(40, 60);u8g2.print(radioData.bprmCh);
  u8g2.drawUTF8(70,60,"ДПРМ:");
  u8g2.setCursor(100,60);u8g2.print(radioData.dprmCh);
}

// ****** ФОРМИРОВАНИЕ КАДРА УПР ****** 
void Display::uprKadr(){
  u8g2.setFont(u8g2_font_6x12_t_cyrillic);
  //u8g2.drawUTF8(20,10,"--МЕХАНИЗАЦИЯ--");
  u8g2.drawEllipse(64, 32, 7, 7); // фюзеляж
  u8g2.drawLine(64,25,64,15);
  u8g2.drawLine(20,32,57,32); // левое крыло
  u8g2.drawLine(71,32,108,32); // правое крыло

  // ** ШАССИ **
  if(uprData.gearN){
    // носовая стойка шасси
    u8g2.drawLine(64,39,64,50);
    u8g2.drawBox(63,50,3,6);  
  }
  if(uprData.gearL){
    // левая стойка шасси
    u8g2.drawLine(52,32,52,50);
    u8g2.drawBox(51,50,3,6);
  }
  if(uprData.gearR){
    // правая стойка шасси
    u8g2.drawLine(76,32,76,50);
    u8g2.drawBox(75,50,3,6);
  }

  // ** ВОЗДУШНЫЙ ТОРМОЗ **
  if(uprData.airBreak){
    // воздушный тормоз
    u8g2.drawBox(60,39,9,6);
  }

  // ** ЗАКРЫЛКИ **
  u8g2.setFont(u8g2_font_6x12_t_cyrillic);
  //uprData.flaps = 1;
  if((uprData.flapsV) || (uprData.flapsP)){
    u8g2.drawUTF8(15,42,"ВЗЛ_");
    u8g2.drawUTF8(15,52,"ПОС_");
    u8g2.drawFrame(33,32,6,22); // левые закрылки
    u8g2.drawFrame(91,32,6,22); // правые закрылки

    if(uprData.flapsV){
      // закрылки взлет
      u8g2.drawBox(33,32,6,12);
      u8g2.drawBox(91,32,6,12);
    }
    else if(uprData.flapsP){
      // закрылки посадка
      u8g2.drawBox(33,32,6,22);
      u8g2.drawBox(91,32,6,22);
    }
  }

  // ** ТРИММЕРЫ **
  u8g2.drawLine(34,5,94,5); // триммер по крену
  u8g2.drawLine(64,3,64,5); // центр триммера по крену
  u8g2.drawLine(123,10,123,55); // триммер по тангажу
  u8g2.drawLine(123,32,125,32); // центр триммера по тангажу

  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.drawGlyph(60, 13, 0x25b4); // символ положения триммера по крену
  u8g2.drawGlyph(115, 38, 0x25ba); // символ положения триммера по тангажу

  // ** СИГНАЛЫ ШАССИ/ЗАКРЫЛКИ **
  //u8g2.setFont(u8g2_font_5x7_t_cyrillic);
  u8g2.setFont(u8g2_font_6x12_t_cyrillic);
  if((!uprData.flapsUp) && (!uprData.flapsV) && (!uprData.flapsP) && (shData.speed < 300)){ // формирование сигнала о разрешении выпуска закрылков на скорости меньше 300
    u8g2.drawUTF8(3,20,"ЗКРЛК"); 
    u8g2.drawUTF8(3,29,"МОЖНО");
  }
  if((!uprData.gearL) && (!uprData.gearN) && (!uprData.gearR) && (shData.speed < 350)){ // формирование сигнала о разрешении выпуска шасси на скорости меньше 350
    u8g2.drawUTF8(50,53,"ШАССИ");
    u8g2.drawUTF8(50,62,"МОЖНО");
  }

  // ** СКОРОСТЬ/ВЫСОТА **
  u8g2.drawUTF8(74,20,"S:");
  u8g2.setCursor(86,20); u8g2.print(shData.speed); // вывод скорости
  u8g2.drawUTF8(74,29,"H:");
  u8g2.setCursor(86,29);u8g2.print((int)(shData.height * 0.3048)); // вывод высоты
}