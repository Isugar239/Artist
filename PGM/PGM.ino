#include <GyverOLED.h>
#include <Wire.h>
#include "GyverOLEDMenu.h"
#include "cart.h"
#include "encoder.h"
#include "rgb.h"
#include "sensor.h"
#include "marker.h"
Sensor sensor;
GyverOLED<SSD1306_128x64> oled;
Encoder enc(10, 11, 12);
cart IvanTM(1, 2, 4, 3, 5);
rgb<8, 3> fara(3, 100);
marker black(9, 90, 270, IvanTM);
OledMenu<6, GyverOLED<SSD1306_128x64>> menu(&oled);


void func1() {
  oled.clear();
  oled.setScale(2);
  oled.setCursor(20, 25);
  oled.print("ДВИЖЕНИЕ");
  oled.update();
  fara.green();
  // Едем вперед 200 мм
  IvanTM.gotoPos(200);
  black.down();

  delay(500);
  black.up();
  fara.red();

  // Едем назад 200 мм (возвращаемся в 0)
  IvanTM.gotoPos(0);
  
  oled.clear();
  oled.setScale(2);
  oled.setCursor(15, 25);
  oled.print("ГОТОВО!");
  oled.update();
  delay(2000);
  oled.setScale(1);
  fara.clear();
  menu.showMenu(true);
  oled.update();
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
  "1", "2", "3",
  "4", "5", "6"
};

// Колбэк при выборе пункта меню
void onItemChange(const int index, const void* val, const byte valType) { //чтобы просто прокрутка не вызывала функцию, а именно тык по ней
  if (valType == VAL_ACTION) {
    if (index >= 0 && index < 6) {
      Serial.println(index);
      menuFuncs[index](); // указатель вызывает функцию
    }
  }
}

void encoderCallback() {
  if (enc.dir != 0) {
    if (enc.dir == 1) {
      menu.selectNext(false); //false значит без скипов элементов
    } else {
      menu.selectPrev(false);
    }
    oled.update(); // Обновляем экран для надежности
  }
  
  if (enc.clicked) {
    menu.toggleChangeSelected();
    oled.update();
  }
}

void setup() {
  oled.init();
  Wire.setClock(400000L);
  oled.clear();
  oled.update();
  Serial.begin(9600);
  black.begin();
  menu.onChange(onItemChange, false);

  menu.addItem(PSTR("1"));
  menu.addItem(PSTR("2"));
  menu.addItem(PSTR("3"));
  menu.addItem(PSTR("4"));
  menu.addItem(PSTR("5"));
  menu.addItem(PSTR("6"));

  menu.showMenu(true);
  fara.begin();
  Serial.println("inited");
  
  
}

void loop() {
  enc.tick();
  encoderCallback();
  sensor.tick();
  IvanTM.tick(); // Обновление двигателей
}
