#include "loaders.h"

void digSeg(byte x, byte y, byte z1, byte z2, byte z3, byte z4, byte z5, byte z6) {   // отображение двух строк по три символа с указанием кодов символов (с)НР
  lcd.setCursor(x, y);
  lcd.write(z1); lcd.write(z2); lcd.write(z3);
  if (x <= 11) lcd.print(" ");
  lcd.setCursor(x, y + 1);
  lcd.write(z4); lcd.write(z5); lcd.write(z6);
  if (x <= 11) lcd.print(" ");
}

void drawDig(byte dig, byte x, byte y) {        // рисуем цифры (с)НР ---------------------------------------
  if (bigDig && DISPLAY_TYPE == 1) {
    switch (dig) {            // четырехстрочные цифры (с)НР
      case 0:
        digSeg(x, y, 255, 0, 255, 255, 32, 255);
        digSeg(x, y + 2, 255, 32, 255, 255, 3, 255);
        break;
      case 1:
        digSeg(x, y, 32, 255, 32, 32, 255, 32);
        digSeg(x, y + 2, 32, 255, 32, 32, 255, 32);
        break;
      case 2:
        digSeg(x, y, 0, 0, 255, 1, 1, 255);
        digSeg(x, y + 2, 255, 2, 2, 255, 3, 3);
        break;
      case 3:
        digSeg(x, y, 0, 0, 255, 1, 1, 255);
        digSeg(x, y + 2, 2, 2, 255, 3, 3, 255);
        break;
      case 4:
        digSeg(x, y, 255, 32, 255, 255, 1, 255);
        digSeg(x, y + 2, 2, 2, 255, 32, 32, 255);
        break;
      case 5:
        digSeg(x, y, 255, 0, 0, 255, 1, 1);
        digSeg(x, y + 2, 2, 2, 255, 3, 3, 255);
        break;
      case 6:
        digSeg(x, y, 255, 0, 0, 255, 1, 1);
        digSeg(x, y + 2, 255, 2, 255, 255, 3, 255);
        break;
      case 7:
        digSeg(x, y, 0, 0, 255, 32, 32, 255);
        digSeg(x, y + 2, 32, 255, 32, 32, 255, 32);
        break;
      case 8:
        digSeg(x, y, 255, 0, 255, 255, 1, 255);
        digSeg(x, y + 2, 255, 2, 255, 255, 3, 255);
        break;
      case 9:
        digSeg(x, y, 255, 0, 255, 255, 1, 255);
        digSeg(x, y + 2, 2, 2, 255, 3, 3, 255);
        break;
      case 10:
        digSeg(x, y, 32, 32, 32, 32, 32, 32);
        digSeg(x, y + 2, 32, 32, 32, 32, 32, 32);
        break;
    }
  }
  else {
    switch (dig) {            // двухстрочные цифры
      case 0:
        digSeg(x, y, 255, 1, 255, 255, 2, 255);
        break;
      case 1:
        digSeg(x, y, 32, 255, 32, 32, 255, 32);
        break;
      case 2:
        digSeg(x, y, 3, 3, 255, 255, 4, 4);
        break;
      case 3:
        digSeg(x, y, 3, 3, 255, 4, 4, 255);
        break;
      case 4:
        digSeg(x, y, 255, 0, 255, 5, 5, 255);
        break;
      case 5:
        digSeg(x, y, 255, 3, 3, 4, 4, 255);
        break;
      case 6:
        digSeg(x, y, 255, 3, 3, 255, 4, 255);
        break;
      case 7:
        digSeg(x, y, 1, 1, 255, 32, 255, 32);
        break;
      case 8:
        digSeg(x, y, 255, 3, 255, 255, 4, 255);
        break;
      case 9:
        digSeg(x, y, 255, 3, 255, 4, 4, 255);
        break;
      case 10:
        digSeg(x, y, 32, 32, 32, 32, 32, 32);
        break;
    }
  }
}

void drawPPM(int dispCO2, byte x, byte y) {     // Уровень СО2 крупно на главном экране (с)НР ----------------------------
  if (dispCO2 / 1000 == 0) drawDig(10, x, y);
  else drawDig(dispCO2 / 1000, x, y);
  drawDig((dispCO2 % 1000) / 100, x + 4, y);
  drawDig((dispCO2 % 100) / 10, x + 8, y);
  drawDig(dispCO2 % 10 , x + 12, y);
  lcd.setCursor(15, 0);
#if (DISPLAY_TYPE == 1)
  lcd.print("ppm");
#else
  lcd.print("p");
#endif
}

void drawPres(int dispPres, byte x, byte y) {   // Давление крупно на главном экране (с)НР ----------------------------
  drawDig((dispPres % 1000) / 100, x , y);
  drawDig((dispPres % 100) / 10, x + 4, y);
  drawDig(dispPres % 10 , x + 8, y);
  lcd.setCursor(x + 11, 1);
  if (bigDig) lcd.setCursor(x + 11, 3);
  lcd.print("mm");
}

void drawAlt(float dispAlt, byte x, byte y) {   // Высота крупно на главном экране (с)НР -----------------------------
  if (dispAlt >= 1000) {
    drawDig((int(dispAlt) % 10000) / 1000, x , y);
    x += 4;
  }
  drawDig((int(dispAlt) % 1000) / 100, x , y);
  drawDig((int(dispAlt) % 100) / 10, x + 4, y);
  drawDig(int(dispAlt) % 10 , x + 8, y);
  if (dispAlt < 1000) {       // десятые доли метра, если высота ниже 1000 м. (с)НР
    //   drawDig((int(dispAlt * 10.0)) % 10 , x + 12, y);         // десятые крупными цифрами (тогда буква m наезжает на последнюю цифру)
    lcd.setCursor(x + 12, y + 1 + (bigDig && DISPLAY_TYPE) * 2);  // десятые мелкими цифрами
    lcd.print((int(dispAlt * 10.0)) % 10);
    if (bigDig && DISPLAY_TYPE == 1) lcd.setCursor(x + 11, y + 3);
    else lcd.setCursor(x + 11, y + 1);
    lcd.print(".");
    x -= 1; // сдвинуть букву m левее
  }  else {
    x -= 4;
  }
  if (bigDig && DISPLAY_TYPE == 1) lcd.setCursor(x + 14, 3);
  else lcd.setCursor(x + 14, 1);
  lcd.print("m");
}

void drawTemp(float dispTemp, byte x, byte y) { // Температура крупно на главном экране (с)НР ----------------------------
  if (dispTemp / 10 == 0) drawDig(10, x, y);
  else drawDig(dispTemp / 10, x, y);
  drawDig(int(dispTemp) % 10, x + 4, y);
  drawDig(int(dispTemp * 10.0) % 10, x + 9, y);

  if (bigDig && DISPLAY_TYPE == 1) {
    lcd.setCursor(x + 7, y + 3);
    lcd.write(1);             // десятичная точка
  }
  else {
    lcd.setCursor(x + 7, y + 1);
    lcd.write(0B10100001);    // десятичная точка
  }
  lcd.setCursor(x + 13, y);
  lcd.write(223);             // градусы
}

void drawHum(int dispHum, byte x, byte y) {   // Влажность крупно на главном экране (с)НР ----------------------------
  if (dispHum / 100 == 0) drawDig(10, x, y);
  else drawDig(dispHum / 100, x, y);
  if ((dispHum % 100) / 10 == 0) drawDig(0, x + 4, y);
  else drawDig(dispHum / 10, x + 4, y);
  drawDig(int(dispHum) % 10, x + 8, y);
  if (bigDig && DISPLAY_TYPE == 1) {
    lcd.setCursor(x + 12, y + 1);
    lcd.print("\245\4");
    lcd.setCursor(x + 12, y + 2);
    lcd.print("\5\245");
  }
  else {
    lcd.setCursor(x + 12, y + 1);
    lcd.print("%");
  }
}

void drawClock(byte hours, byte minutes, byte x, byte y) {    // рисуем время крупными цифрами -------------------------------------------
  if (hours > 23 || minutes > 59) return;
  if (hours / 10 == 0) drawDig(10, x, y);
  else drawDig(hours / 10, x, y);
  drawDig(hours % 10, x + 4, y);
  // тут должны быть точки. Отдельной функцией
  drawDig(minutes / 10, x + 8, y);
  drawDig(minutes % 10, x + 12, y);
}

void drawData() {                     // выводим дату -------------------------------------------------------------
  int Y = 0;
  if (DISPLAY_TYPE == 1 && mode0scr == 1) Y = 2;
  if (!bigDig) {              // если 4-х строчные цифры, то дату, день недели (и секунды) не пишем - некуда (с)НР
    lcd.setCursor(15, 0 + Y);
    if (now.day() < 10) lcd.print(0);
    lcd.print(now.day());
    lcd.print(".");
    if (now.month() < 10) lcd.print(0);
    lcd.print(now.month());

    if (DISP_MODE == 0) {
      lcd.setCursor(16, 1);
      lcd.print(now.year());
    } else {
      loadClock();              // принудительно обновляем знаки, т.к. есть жалобы на необновление знаков в днях недели (с)НР
      lcd.setCursor(18, 1);
      int dayofweek = now.dayOfTheWeek();
      lcd.print(dayNames[dayofweek]);
      // if (hrs == 0 && mins == 0 && secs <= 1) loadClock();   // Обновляем знаки, чтобы русские буквы в днях недели тоже обновились. (с)НР
    }
  }
}

void drawPlot(byte pos, byte row, byte width, byte height, int min_val, int max_val, int *plot_array, String label1, String label2, int stretch) {  // график ---------------------------------
  int max_value = -32000;
  int min_value = 32000;

  for (byte i = 0; i < 15; i++) {
    max_value = max(plot_array[i] , max_value);
    min_value = min(plot_array[i] , min_value);
  }

  // меняем пределы графиков на предельные/фактические значения, одновременно рисуем указатель пределов (стрелочки вверх-вниз) (с)НР
  lcd.setCursor(15, 0);
  if ((MAX_ONDATA & (1 << (stretch - 1))) > 0) {    // побитовое сравнение 1 - растягиваем, 0 - не растягиваем (по указанным пределам) (с)НР
    //    max_val = min(max_value, max_val);
    //    min_val = max(min_value, min_val);
    max_val = max_value;
    min_val = min_value;
#if (DISPLAY_TYPE == 1)
    lcd.write(0b01011110);
    lcd.setCursor(15, 3);
    lcd.write(0);
#endif
  }  else {
#if (DISPLAY_TYPE == 1)
    lcd.write(0);
    lcd.setCursor(15, 3);
    lcd.write(0b01011110);
#endif
  }

  if (min_val >= max_val) max_val = min_val + 1;
#if (DISPLAY_TYPE == 1)
  lcd.setCursor(15, 1); lcd.write(0b01111100);
  lcd.setCursor(15, 2); lcd.write(0b01111100);

  //Serial.println(max_val);Serial.println(min_val);  // отладка (с)НР

  lcd.setCursor(16, 0); lcd.print(max_value);
  lcd.setCursor(16, 1); lcd.print(label1); lcd.print(label2);
  lcd.setCursor(16, 2); lcd.print(plot_array[14]);
  lcd.setCursor(16, 3); lcd.print(min_value);
#else
  lcd.setCursor(12, 0); lcd.print(label1);
  lcd.setCursor(13, 0); lcd.print(max_value);
  lcd.setCursor(12, 1); lcd.print(label2);
  lcd.setCursor(13, 1); lcd.print(min_value);
#endif
  for (byte i = 0; i < width; i++) {                  // каждый столбец параметров
    int fill_val = plot_array[i];
    fill_val = constrain(fill_val, min_val, max_val);
    byte infill, fract;
    // найти количество целых блоков с учётом минимума и максимума для отображения на графике
    if ((plot_array[i]) > min_val)
      infill = floor((float)(plot_array[i] - min_val) / (max_val - min_val) * height * 10);
    else infill = 0;
    fract = (float)(infill % 10) * 8 / 10;            // найти количество оставшихся полосок
    infill = infill / 10;

    for (byte n = 0; n < height; n++) {     // для всех строк графика
      if (n < infill && infill > 0) {       // пока мы ниже уровня
        lcd.setCursor(i, (row - n));        // заполняем полными ячейками
        lcd.write(255);
      }
      if (n >= infill) {                    // если достигли уровня
        lcd.setCursor(i, (row - n));
        if (n == 0 && fract == 0) fract++;      // если нижний перел графика имеет минимальное значение, то рисуем одну полоску, чтобы не было пропусков (с)НР
        if (fract > 0) lcd.write(fract);        // заполняем дробные ячейки
        else lcd.write(16);                     // если дробные == 0, заливаем пустой
        for (byte k = n + 1; k < height; k++) { // всё что сверху заливаем пустыми
          lcd.setCursor(i, (row - k));
          lcd.write(16);
        }
        break;
      }
    }
  }
}

void drawSensors() {
#if (DISPLAY_TYPE == 1)
  // дисплей 2004 ----------------------------------

  if (mode0scr != 2) {                        // Температура (с)НР ----------------------------
    lcd.setCursor(0, 2);
    if (bigDig) {
      if (mode0scr == 1) lcd.setCursor(15, 2);
      if (mode0scr != 1) lcd.setCursor(15, 0);
    }
    lcd.print(String(dispTemp, 1));
    lcd.write(223);
  } else {
    drawTemp(dispTemp, 0, 0);
  }

  if (mode0scr != 4) {                        // Влажность (с)НР ----------------------------
    lcd.setCursor(5, 2);
    if (bigDig) lcd.setCursor(15, 1);
    lcd.print(" " + String(dispHum) + "% ");
  } else {
    drawHum(dispHum, 0, 0);
  }

#if (CO2_SENSOR == 1)
  if (mode0scr != 1) {                       // СО2 (с)НР ----------------------------

    if (bigDig) {
      lcd.setCursor(15, 2);
      lcd.print(String(dispCO2) + "p");
    } else {
      lcd.setCursor(11, 2);
      lcd.print(String(dispCO2) + "ppm ");
    }
  } else {
    drawPPM(dispCO2, 0, 0);
  }
#endif

  if (mode0scr != 3) {                      // Давление (с)НР ---------------------------
    lcd.setCursor(0, 3);
    if (bigDig && mode0scr == 0) lcd.setCursor(15, 3);
    if (bigDig && (mode0scr == 1 || mode0scr == 2)) lcd.setCursor(15, 0);
    if (bigDig && mode0scr == 4) lcd.setCursor(15, 1);
    if (!(bigDig && mode0scr == 1)) lcd.print(String(dispPres) + "mm");
  } else {
    drawPres(dispPres, 0, 0);
  }

  if (mode0scr != 5) {                      // Высота (с)НР ----------------------------
  } else {                                  // мелко высоту не выводим (с)НР
    drawAlt(dispAlt, 0, 0);
  }

  if (!bigDig) {                            // дождь (с)НР -----------------------------
    lcd.setCursor(5, 3);
    lcd.print(" rain     ");
    lcd.setCursor(11, 3);
    if (dispRain < 0) lcd.setCursor(10, 3);
    lcd.print(String(dispRain) + "%");
    //  lcd.setCursor(14, 3);
    //  lcd.print(bme.readAltitude(SEALEVELPRESSURE_HPA));  // высота над уровнем моря (с)НР
  }

  if (mode0scr != 0) {                      // время (с)НР ----------------------------
    lcd.setCursor(15, 3);
    if (hrs / 10 == 0) lcd.print(" ");
    lcd.print(hrs);
    lcd.print(":");
    if (mins / 10 == 0) lcd.print("0");
    lcd.print(mins);
  } else {
    drawClock(hrs, mins, 0, 0); //, 1);
  }
#else

  // дисплей 1602 ----------------------------------
  if (!bigDig) {              // если только мелкими цифрами (с)НР
    lcd.setCursor(0, 0);
    lcd.print(String(dispTemp, 1));
    lcd.write(223);
    lcd.setCursor(6, 0);
    lcd.print(String(dispHum) + "% ");

#if (CO2_SENSOR == 1)
    lcd.print(String(dispCO2) + "ppm");
    if (dispCO2 < 1000) lcd.print(" ");
#endif

    lcd.setCursor(0, 1);
    lcd.print(String(dispPres) + " mm  rain ");
    lcd.print(String(dispRain) + "% ");
  } else {                    // для крупных цифр (с)НР
    switch (mode0scr) {
      case 0:
        drawClock(hrs, mins, 0, 0);
        break;
      case 1:
#if (CO2_SENSOR == 1)
        drawPPM(dispCO2, 0, 0);
#endif
        break;
      case 2:
        drawTemp(dispTemp, 2, 0);
        break;
      case 3:
        drawPres(dispPres, 2, 0);
        break;
      case 4:
        drawHum(dispHum, 0, 0);
        break;
      case 5:
        drawHum(dispAlt, 0, 0);
        break;
    }
  }
#endif
}


void redrawPlot() {
  lcd.clear();
#if (DISPLAY_TYPE == 1)       // для дисплея 2004
  switch (mode) {             // добавлена переменная для "растягивания" графика до фактических максимальных и(или) минимальных значений(с)НР
    case 1: drawPlot(0, 3, 15, 4, CO2_MIN, CO2_MAX, (int*)co2Hour, "c ", "hr", mode);
      break;
    case 2: drawPlot(0, 3, 15, 4, CO2_MIN, CO2_MAX, (int*)co2Day, "c ", "da", mode);
      break;
    case 3: drawPlot(0, 3, 15, 4, HUM_MIN, HUM_MAX, (int*)humHour, "h%", "hr", mode);
      break;
    case 4: drawPlot(0, 3, 15, 4, HUM_MIN, HUM_MAX, (int*)humDay, "h%", "da", mode);
      break;
    case 5: drawPlot(0, 3, 15, 4, TEMP_MIN, TEMP_MAX, (int*)tempHour, "t\337", "hr", mode);
      break;
    case 6: drawPlot(0, 3, 15, 4, TEMP_MIN, TEMP_MAX, (int*)tempDay, "t\337", "da", mode);
      break;
    //    case 7: drawPlot(0, 3, 15, 4, RAIN_MIN, RAIN_MAX, (int*)rainHour, "r ", "hr", mode);
    //      break;
    //    case 8: drawPlot(0, 3, 15, 4, RAIN_MIN, RAIN_MAX, (int*)rainDay, "r ", "da", mode);
    //      break;
    case 7: drawPlot(0, 3, 15, 4, PRESS_MIN, PRESS_MAX, (int*)pressHour, "p ", "hr", mode);
      break;
    case 8: drawPlot(0, 3, 15, 4, PRESS_MIN, PRESS_MAX, (int*)pressDay, "p ", "da", mode);
      break;
    case 9: drawPlot(0, 3, 15, 4, ALT_MIN, ALT_MAX, (int*)altHour, "m ", "hr", mode);
      break;
    case 10: drawPlot(0, 3, 15, 4, ALT_MIN, ALT_MAX, (int*)altDay, "m ", "da", mode);
      break;
  }
#else                         // для дисплея 1602
  switch (mode) {
    case 1: drawPlot(0, 1, 12, 2, CO2_MIN, CO2_MAX, (int*)co2Hour, "c", "h", mode);
      break;
    case 2: drawPlot(0, 1, 12, 2, CO2_MIN, CO2_MAX, (int*)co2Day, "c", "d", mode);
      break;
    case 3: drawPlot(0, 1, 12, 2, HUM_MIN, HUM_MAX, (int*)humHour, "h", "h", mode);
      break;
    case 4: drawPlot(0, 1, 12, 2, HUM_MIN, HUM_MAX, (int*)humDay, "h", "d", mode);
      break;
    case 5: drawPlot(0, 1, 12, 2, TEMP_MIN, TEMP_MAX, (int*)tempHour, "t", "h", mode);
      break;
    case 6: drawPlot(0, 1, 12, 2, TEMP_MIN, TEMP_MAX, (int*)tempDay, "t", "d", mode);
      break;
    //    case 7: drawPlot(0, 1, 12, 2, RAIN_MIN, RAIN_MAX, (int*)rainHour, "r", "h", mode);
    //      break;
    //    case 8: drawPlot(0, 1, 12, 2, RAIN_MIN, RAIN_MAX, (int*)rainDay, "r", "d", mode);
    //      break;
    case 7: drawPlot(0, 1, 12, 2, PRESS_MIN, PRESS_MAX, (int*)pressHour, "p", "h", mode);
      break;
    case 8: drawPlot(0, 1, 12, 2, PRESS_MIN, PRESS_MAX, (int*)pressDay, "p", "d", mode);
      break;
    case 9: drawPlot(0, 1, 12, 2, ALT_MIN, ALT_MAX, (int*)altHour, "m", "h", mode);
      break;
    case 10: drawPlot(0, 1, 12, 2, ALT_MIN, ALT_MAX, (int*)altDay, "m", "d", mode);
      break;
  }
#endif
}

void drawChangeDateTimeMenu() {
  lcd.createChar(3, curs);  //Курсор
#if (WEEK_LANG == 1)
    lcd.createChar(1, BM);  //Ь
    lcd.createChar(2, YY);  //Ы
    lcd.createChar(4, II);  //И
    lcd.createChar(5, DD);  //Д
    lcd.createChar(6, GG);  //Г
    lcd.createChar(7, CH);  //Ч
#endif

#if (DISPLAY_TYPE == 1) //2004 (большой) - все помещается на одном экране
    lcd.setCursor(0, 0);
#if (WEEK_LANG == 1)
    lcd.print("\7:");
#else
    lcd.print("H:")
#endif
    lcd.print(String(currentHrs));
    if(dateTimeCursorPos == 0) {
      lcd.print("\3");
    }
    
    lcd.setCursor(0, 1);
    lcd.print("M:");
    lcd.print(String(currentMins));
    if(dateTimeCursorPos == 1) {
      lcd.print("\3");
    }

    lcd.setCursor(0, 2);
#if (WEEK_LANG == 1)
    lcd.print("\5EH\1:");
#else
    lcd.print("DAY:")
#endif
    lcd.print(String(currentDay));
    if(dateTimeCursorPos == 2) {
      lcd.print("\3");
    }

    lcd.setCursor(0, 3);
#if (WEEK_LANG == 1)
    lcd.print("MEC.:");
#else
    lcd.print("MO:")
#endif
    lcd.print(String(currentMonth));
    if(dateTimeCursorPos == 3) {
      lcd.print("\3");
    }

    lcd.setCursor(10, 0);
#if (WEEK_LANG == 1)
    lcd.print("\6O\5:");
#else
    lcd.print("YEAR:")
#endif
    lcd.print(String(currentYear));
    if(dateTimeCursorPos == 4) {
      lcd.print("\3");
    }

    //--------------------------
    
    lcd.setCursor(10, 2);
#if (WEEK_LANG == 1)
    lcd.print("COXPAH\4T\1");
#else
    lcd.print("SAVE")
#endif
    if(dateTimeCursorPos == 5) {
      lcd.print("\3");
    }

    lcd.setCursor(10, 3);
#if (WEEK_LANG == 1)
    lcd.print("B\2XO\5");
#else
    lcd.print("EXIT")
#endif
    if(dateTimeCursorPos == 6) {
      lcd.print("\3");
    }

#else //1602 (маленький) - рисуем частями. Отображение пунктов зависит от курсора
    if(dateTimeCursorPos <= 3) {
      lcd.setCursor(0, 0);
#if (WEEK_LANG == 1)
      lcd.print("\7:");
#else
      lcd.print("H:")
#endif
      lcd.print(String(currentHrs));
      if(dateTimeCursorPos == 0) {
        lcd.print("\3");
      }
      
      lcd.setCursor(0, 1);
      lcd.print("M:");
      lcd.print(String(currentMins));
      if(dateTimeCursorPos == 1) {
        lcd.print("\3");
      }

      lcd.setCursor(10, 0);
#if (WEEK_LANG == 1)
      lcd.print("\5EH\1:");
#else
      lcd.print("DAY:")
#endif
      lcd.print(String(currentDay));
      if(dateTimeCursorPos == 2) {
        lcd.print("\3");
      }

      lcd.setCursor(10, 1);
#if (WEEK_LANG == 1)
      lcd.print("MEC.:");
#else
      lcd.print("MO:")
#endif
      lcd.print(String(currentMonth));
      if(dateTimeCursorPos == 3) {
        lcd.print("\3");
      }
    } else if(dateTimeCursorPos > 3 && dateTimeCursorPos <= 7) {
      lcd.setCursor(0, 0);
#if (WEEK_LANG == 1)
      lcd.print("\6O\5:");
#else
      lcd.print("YEAR:")
#endif
      lcd.print(String(currentYear));
      if(dateTimeCursorPos == 4) {
        lcd.print("\3");
      }

      lcd.setCursor(0, 1);
#if (WEEK_LANG == 1)
      lcd.print("COXPAH\4T\1");
#else
      lcd.print("SAVE")
#endif
      if(dateTimeCursorPos == 5) {
        lcd.print("\3");
      }

      lcd.setCursor(10, 0);
#if (WEEK_LANG == 1)
      lcd.print("B\2XO\5");
#else
      lcd.print("EXIT")
#endif
      if(dateTimeCursorPos == 6) {
        lcd.print("\3");
      }
    }
#endif
}

void redrawScreen(byte subMode, byte subPodMode) {
    if (subMode >= 240) {
      lcd.clear();
      lcd.createChar(1, BM);  //Ь
      lcd.createChar(2, IY);  //Й
      lcd.createChar(3, DD);  //Д
      lcd.createChar(4, II);  //И
      lcd.createChar(5, IA);  //Я
      lcd.createChar(6, YY);  //Ы
      lcd.createChar(7, AA);  //Э
      lcd.createChar(0, ZZ);  //Ж
      lcd.setCursor(0, 0);
    }
    if (subMode == 255) {          // Перебираем варианты в главном меню (с)НР
#if (WEEK_LANG == 1)
      lcd.print("HACTPO\2K\4:");              // ---Настройки
#else
      lcd.print("Setup:");
#endif
      lcd.setCursor(0, 1);
      switch (subPodMode) {
        case 1:
#if (WEEK_LANG == 1)
          lcd.print("COXPAH\4T\1");     // ---Сохранить
#else
          lcd.print("Save");
#endif
          break;
        case 2:
#if (WEEK_LANG == 1)
          lcd.print("B\6XO\3");         // --- Выход
#else
          lcd.print("Exit");
#endif
          break;
        case 5:
#if (WEEK_LANG == 1)
          lcd.print("PE\10.\4H\3\4KATOPA");  // ---Реж.индик.
#else
          lcd.print("indicator mode");
#endif
          break;
        case 3:
#if (WEEK_LANG == 1)
          lcd.print("\5PK.\4H\3\4KATOPA");  // ---Ярк.индик.
#else
          lcd.print("indicator brt.");
#endif
          break;
        case 4:
#if (WEEK_LANG == 1)
          lcd.print("\5PK.\7KPAHA");    // ---Ярк.экрана
#else
          lcd.print("Bright LCD");
#endif
          break;
          case 6:
#if (WEEK_LANG == 1)
          lcd.print("BPEM\5/\3ATA");  // Изменение времени.
#else
          lcd.print("date/time");
#endif
          break;
      }
      if (subPodMode >= 7 && subPodMode <= 18) {
        lcd.createChar(8, FF);  //ф
        lcd.createChar(7, GG);  //Г
        lcd.createChar(5, LL);  //Л
        lcd.setCursor(10, 0);
#if (WEEK_LANG == 1)
        lcd.print("\7PA\10\4KOB");            // ---графиков
#else
        lcd.print("Charts  ");
#endif
        lcd.setCursor(0, 1);
        if ((3 & (1 << (subPodMode - 7))) != 0) lcd.print("CO2 ");
        if ((12 & (1 << (subPodMode - 7))) != 0) {
#if (WEEK_LANG == 1)
          lcd.print("B\5,% ");
#else
          lcd.print("Hum,%");
#endif
        }
        if ((48 & (1 << (subPodMode - 7))) != 0) lcd.print("t\337 ");
        if ((192 & (1 << (subPodMode - 7))) != 0) {
          if (PRESSURE) lcd.print("p,rain ");
          else lcd.print("p,mmPT ");
        }
        if ((768 & (1 << (subPodMode - 7))) != 0) {
#if (WEEK_LANG == 1)
          lcd.print("B\6C,m  ");
#else
          lcd.print("hgt,m  ");
#endif
        }

        if ((1365 & (1 << (subPodMode - 7))) != 0) {
          lcd.createChar(3, CH);  //Ч
          lcd.setCursor(8, 1);
#if (WEEK_LANG == 1)
          lcd.print("\3AC:");
#else
          lcd.print("Hour:");
#endif
        } else {
          lcd.setCursor(7, 1);
#if (WEEK_LANG == 1)
          lcd.print("\3EH\1:");
#else
          lcd.print("Day: ");
#endif
        }
        if ((VIS_ONDATA & (1 << (subPodMode - 7))) != 0) {
#if (WEEK_LANG == 1)
          lcd.print("BK\5 ");
#else
          lcd.print("On  ");
#endif
        }
        else {
#if (WEEK_LANG == 1)
          lcd.print("B\6K\5");
#else
          lcd.print("Off ");
#endif
        }
      }
    }
    if (subMode == 251) {  
      drawChangeDateTimeMenu();
    }
    if (subMode == 252) {                        // --------------------- показать  "Реж.индикатора"
      LEDType = subPodMode;
      lcd.createChar(6, LL);  //Л
      lcd.createChar(3, DD);  //Д
      lcd.createChar(5, II);  //И
      lcd.createChar(8, ZZ);  //Ж
      lcd.setCursor(0, 0);
#if (WEEK_LANG == 1)
      lcd.print("PE\10.\4H\3\4KATOPA:");
#else
      lcd.print("indicator mode:");
#endif
      lcd.setCursor(0, 1);
      switch (subPodMode) {
        case 0:
          lcd.print("CO2   ");
          break;
        case 1:
#if (WEEK_LANG == 1)
          lcd.print("B\6A\10H.");          // влажн.
#else
          lcd.print("Humid.");
#endif
          break;
        case 2:
          lcd.print("t\337     ");
          break;
        case 3:
#if (WEEK_LANG == 1)
          lcd.print("OCA\3K\5");          // осадки
#else
          lcd.print("rain  ");
#endif
          break;
        case 4:
#if (WEEK_LANG == 1)
          lcd.print("\3AB\6EH\5E");       // давление
#else
          lcd.print("pressure");
#endif
          break;
      }

    }
    if (subMode == 253) {                        // --------------------- показать  "Ярк.экрана"
#if (WEEK_LANG == 1)
      lcd.print("\5PK.\7KPAHA:");// + String(LCD_BRIGHT * 10) + "%  ");
#else
      lcd.print("Bright LCD:");
#endif
      //lcd.setCursor(11, 0);
      if (LCD_BRIGHT == 11) {
#if (WEEK_LANG == 1)
        lcd.print("ABTO ");
#else
        lcd.print("Auto ");
#endif
      }
      else lcd.print(String(LCD_BRIGHT * 10) + "%");
    }
    if (subMode == 254) {                        // --------------------- показать  "Ярк.индикатора"
#if (WEEK_LANG == 1)
      lcd.print("\5PK.\4H\3\4K.:");// + String(LED_BRIGHT * 10) + "%  ");
#else
      lcd.print("indic.brt.:");
#endif
      //lcd.setCursor(15, 0);
      if (LED_BRIGHT == 11) {
#if (WEEK_LANG == 1)
        lcd.print("ABTO ");
#else
        lcd.print("Auto ");
#endif
      }
      else lcd.print(String(LED_BRIGHT * 10) + "%");
    }

    if (subMode == 0) {
      lcd.clear();
      loadClock();
      drawSensors();
      if (DISPLAY_TYPE == 1) drawData();
    } else if (subMode <= 10) {
      //lcd.clear();
      loadPlot();
      redrawPlot();
    }
}
