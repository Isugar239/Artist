#include <GyverOLED.h>
#include "GyverOLEDMenu.h"
#include "cart.h"
#include "encoder.h"

Encoder enc(10, 11, 13);
GyverOLED<SSD1306_128x64> oled;

OledMenu<6, GyverOLED<SSD1306_128x64>> menu(&oled);

void func1() {
}

void func2() {
}

void func3() {
}

void func4() {
}

void func5() {
}

void func6() {
}

void (*menuFuncs[6])() = {func1, func2, func3, func4, func5, func6};

const char* menuNames[6] = {
  "Функция 1", "Функция 2", "Функция 3",
  "Функция 4", "Функция 5", "Функция 6"
};

// Колбэк при выборе пункта меню
void onItemChange(const int index, const void* val, const byte valType) { //чтобы просто прокрутка не вызывала функцию, а именно тык по ней
  if (valType == VAL_ACTION) {
    if (index >= 0 && index < 6) {
      menuFuncs[index](); // указатель вызывает функцию
    }
  }
}

void encoderCallback() {
  if (enc.dir != 0) {
    if (enc.dir == 1) {
      menu.selectPrev(false); //false значит без скипов элементов
    } else {
      menu.selectNext(false);
    }
  }
  
  if (enc.clicked) {
    menu.toggleChangeSelected();
  }
}

void setup() {
  oled.init();
  Wire.setClock(400000L);
  oled.clear();
  oled.update();

  menu.onChange(onItemChange, false);

  menu.addItem(PSTR("Функция 1"));
  menu.addItem(PSTR("Функция 2"));
  menu.addItem(PSTR("Функция 3"));
  menu.addItem(PSTR("Функция 4"));
  menu.addItem(PSTR("Функция 5"));
  menu.addItem(PSTR("Функция 6"));

  menu.showMenu(true);
}

void loop() {
  enc.tick();
  encoderCallback();
}
