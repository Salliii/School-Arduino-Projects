#include <controller.h>


uint16_t dis, disMetric;


void setup() {
  bit_init(_PORTC_, 5, OUTPUT);
  bit_init(_PORTC_, 4, INPUT);
  
  lcd_init();
  lcd_clear();
  lcd_setcursor(0,0);
}


void loop() {
  bit_write(_PORTC_, 5, HIGH);
  delay_100us(1);
  bit_write(_PORTC_, 5, LOW);

  while (bit_read(_PORTC_, 4) == 0) {}

  do {
    dis++;
  }while (bit_read(_PORTC_, 4) == 1);

  disMetric = dis/2;

  lcd_clear();
  lcd_setcursor(0,0);
  lcd_int(disMetric);
  lcd_setcursor(1,0);
  lcd_int(dis);

  dis = 0;
  disMetric = 0;
  
  delay_ms(200);
}
