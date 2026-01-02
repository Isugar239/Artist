#include <GyverOLED.h>
#include <EncButton.h>
#include "GyverOLEDMenu.h"
#include "cart.h"

// Энкодер для управления меню
EncButton eb(10, 11, 13, INPUT_PULLUP);
GyverOLED<SSD1306_128x64> oled;

// Меню с 6 пунктами
OledMenu<6, GyverOLED<SSD1306_128x64>> menu(&oled);

// Твои функции для каждого пункта меню
void func1() {
  // функция для пункта 1
}

void func2() {
  // функция для пункта 2
}

void func3() {
  // функция для пункта 3
}

void func4() {
  // функция для пункта 4
}

void func5() {
  // функция для пункта 5
}

void func6() {
  // функция для пункта 6
}

// Массив указателей на функции
void (*menuFuncs[6])() = {func1, func2, func3, func4, func5, func6};

// Массив строк для проверки (альтернативный способ)
const char* menuNames[6] = {
  "Функция 1", "Функция 2", "Функция 3",
  "Функция 4", "Функция 5", "Функция 6"
};

// Колбэк при выборе пункта меню
void onItemChange(const int index, const void* val, const byte valType) {
  if (valType == VAL_ACTION) {
    // Способ 1: Вызов по индексу (проще и быстрее)
    if (index >= 0 && index < 6) {
      menuFuncs[index]();
    }
    
    // Способ 2: Проверка по строке (если нужна проверка названия)
    // const char* selectedName = menuNames[index];
    // if (strcmp_P(selectedName, PSTR("Функция 1")) == 0) func1();
    // else if (strcmp_P(selectedName, PSTR("Функция 2")) == 0) func2();
    // и т.д.
  }
}

// Колбэк энкодера
void encoderCallback() {
  switch (eb.action()) {
    case EB_TURN:
      if (eb.dir() == 1) {
        menu.selectPrev(eb.fast());
      } else {
        menu.selectNext(eb.fast());
      }
      break;
    case EB_CLICK:
      menu.toggleChangeSelected();
      break;
  }
}

void setup() {
  oled.init();
  Wire.setClock(400000L);
  oled.clear();
  oled.update();

  // Настройка колбэка меню
  menu.onChange(onItemChange, false);

  // Добавляем 6 пунктов меню (каждый - действие)
  menu.addItem(PSTR("Функция 1"));
  menu.addItem(PSTR("Функция 2"));
  menu.addItem(PSTR("Функция 3"));
  menu.addItem(PSTR("Функция 4"));
  menu.addItem(PSTR("Функция 5"));
  menu.addItem(PSTR("Функция 6"));

  menu.showMenu(true);

  // Настройка энкодера
  eb.attach(encoderCallback);
}

void loop() {
  eb.tick();
}
