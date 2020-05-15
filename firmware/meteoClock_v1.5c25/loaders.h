#include "configuration.h"

void loadClock() {
  if (bigDig && (DISPLAY_TYPE == 1)) {              // для четырехстрочных цифр (с)НР
    lcd.createChar(0, UT);
    lcd.createChar(1, row3);
    lcd.createChar(2, UB);
    lcd.createChar(3, row5);
    lcd.createChar(4, KU);
    lcd.createChar(5, KD);
  }
  else {                                            // для двустрочных цифр (с)НР
    lcd.createChar(0, row2);
    lcd.createChar(1, UB);
    lcd.createChar(2, row3);
    lcd.createChar(3, UMB);
    lcd.createChar(4, LMB);
    lcd.createChar(5, LM2);
  }

  if (now.dayOfTheWeek() == 4)  {          // Для четверга в ячейку запоминаем "Ч", для субботы "Б", иначе "П" (с)НР
    lcd.createChar(7, CH);  // Ч (с)НР
  } else if (now.dayOfTheWeek() == 6) {
    lcd.createChar(7, BB);  // Б (с)НР
  } else {
    lcd.createChar(7, PP);  // П (с)НР
  }
}

void loadPlot() {
  lcd.createChar(0, rowS);      // Стрелка вниз для индикатора пределов (с)НР
  lcd.createChar(1, row1);
  lcd.createChar(2, row2);
  lcd.createChar(3, row3);
  lcd.createChar(4, row4);
  lcd.createChar(5, row5);
  lcd.createChar(6, row6);
  lcd.createChar(7, row7);
}