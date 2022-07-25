#include <controller.h>

volatile uint8_t tastgrad = 240, intpress = 0;

void setup() {
  bit_init(_PORTD_, 2, IN);
  
  lcd_init();
  lcd_clear();
  lcd_setcursor(0,0);
  lcd_print("Tastgrad:  ");
  lcd_setcursor(1,0);
  lcd_print("Int Press: ");
  
  pwm_init();
  pwm_duty_cycle(tastgrad);
  pwm_start();

  ext_interrupt_init(ext_interrupt_isr);
}

void loop() {  
  lcd_setcursor(0,11);
  lcd_byte(tastgrad);
  lcd_print(" ");

  lcd_setcursor(1,11);
  lcd_byte(intpress);
}


void ext_interrupt_isr(void) {
  delay_100us(50);
  while (bit_read(_PORTD_, 2) == 0) { }
  delay_100us(50);

  intpress += 1;

  if (tastgrad > 60) {
    tastgrad /= 2;
  }
  else {
    tastgrad = 240;
  }

  pwm_duty_cycle(tastgrad);
  pwm_start();

  EIFR|=0;
  
}
