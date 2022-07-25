#include <controller.h>

uint8_t y, value, pos;
uint8_t _null=84, p45=96, n45=72;
char cl=0xFE, fl=0xFF;

void setup() {
  lcd_init();
  adc_init();
  lcd_clear();
}

void loop() {
  y = adc_in1();

  if (y >= n45 && y <= p45) {
    value = y-n45;
    pos = value/1.7; 
  }

  lcd_print("  ");


    for (int i=0; i<=15; i++) {
    lcd_setcursor(0,i);
    if (i == pos || i == pos+1) {
      lcd_char(fl);
      lcd_char(fl);
    }
    else {
      lcd_char(cl);
    }
    
    lcd_setcursor(1,i);
    if (i == pos || i == pos+1) {
      lcd_char(fl);
      lcd_char(fl);
    }
    else {
      lcd_char(cl);
    }
  }
  
  delay_ms(20);
}
