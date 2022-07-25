#include <controller.h>

uint16_t cap = 0, tmpPr, tmpAf;
uint16_t value_uF=29000, value_nF=2900

void setup() {
  bit_init(_PORTB_, 2, OUTPUT);

  lcd_init();
  lcd_clear();
  lcd_setcursor(0, 0);
}

void loop() {
  bit_init(_PORTB_, 2, OUTPUT);
  bit_write(_PORTB_, 2, LOW);
  delay_ms(500);
  bit_init(_PORTB_, 2, INPUT);
  bit_write(_PORTB_, 2, HIGH);

  while (bit_read(_PORTB_, 2) == LOW) {
    cap++;
  }


  if (cap > value_uF) {
    tmpPr = cap / value_uF;
    tmpAf = (cap % value_uF)/(value_uF/1000);
    lcd_setcursor(0, 0);
    lcd_int(tmpPr);
    lcd_print(".");
    if (tmpAf > 99) {
      lcd_print("");
    }
    else {
      lcd_print("0");
    }
    lcd_int(tmpAf);
    lcd_print("uF  ");
  }
  else if (cap > value_nF) {
    tmpPr = cap / value_nF;
    tmpAf = (cap % value_nF)/(value_nF/1000);
    lcd_setcursor(0, 0);
    lcd_int(tmpPr);
    lcd_print(".");
    if (tmpAf > 99) {
      lcd_print("");
    }
    else {
      lcd_print("0");
    }
    lcd_int(tmpAf);
    lcd_print("nF  ");
  }
  else {
    lcd_setcursor(0, 0);
    lcd_print("-------     ");
  }


/*
  lcd_setcursor(1, 0);
  lcd_int(cap);
  lcd_print("    ");
*/


  cap = 0;
}
