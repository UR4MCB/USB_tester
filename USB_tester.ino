#include "HID-Project.h"										                    // Подключаем библиотеку USB HID
                                                                // https://www.arduinolibraries.info/libraries/hid-project

#define LED_red 2												                        // Номер пина красного светодиода
#define LED_green 3												                      // Номер пина зелёного светодиода

uint32_t timer = millis();										                  // Переменная для работы таймера

bool L_red;														                          // Переменная хранящая состояние красного светодиода
bool L_green;													                          // Переменная хранящая состояние зелёного светодиода


void setup () {
  BootKeyboard.begin();											                    // Старт. Теперь Ардуино работает как ЮСБ клавиатура
  pinMode (LED_red, OUTPUT);									                  // Задаём режим работы (выход) для пинов Ардуины
  pinMode (LED_green, OUTPUT);									                // куда будут подключены светодиоды
}

void loop () {

                                                                
  if ((BootKeyboard.getLeds() & LED_CAPS_LOCK) == 0) {	        // Если светодиод Caps Lock не горит, то
label:                                                          // Метка, которая необходима дря работы оператора goto
    if (millis() - timer > 500) {								                // каждые 500 мс эмулируем нажатие на кнопку Caps Lock
      BootKeyboard.write(KEY_CAPS_LOCK);
      //delay (10);
      timer = millis();											                    // Сбрасываем таймер, ждём снова 500 мс.
    }
    L_red = true;												                        // Зажигаем красный светодиод
    L_green = false;											                      // Тушим зелёный светодиод
    digitalWrite (LED_red, L_red);
    digitalWrite (LED_green, L_green);
  }

  if ((BootKeyboard.getLeds() & LED_CAPS_LOCK) == 0x02) {		    // Если светодиод Caps Lock горит, то
    while (1) {													                        // уходим в бесконечный цикл
      L_red = false;											                      // Тушим красный светодиод
      L_green = true;											                      // Зажигаем зелёный
      digitalWrite (LED_red, L_red);
      digitalWrite (LED_green, L_green);
      if ((BootKeyboard.getLeds() & LED_CAPS_LOCK) == 0) {	    // Условие для выхода из бесконечного цикла. Если светодиод Caps Lock не горит,
        L_red = false;											                    // то тушим все светодиоды
        L_green = false;
        goto label;												                      // и переходим в начало программы.
      }
    }
  }
}
