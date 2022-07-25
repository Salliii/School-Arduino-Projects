#include <controller.h>
#include <lcd.h>

#define h_index 7
#define m_index 10
#define s_index 13

volatile uint16_t t_ms, t_s, t_m, t_h;
volatile uint8_t set_mode;

void setup() {
  bit_init(_PORTB_, 2, INPUT);
  bit_init(_PORTB_, 1, INPUT);

  lcd_init();
  lcd_clear();
  lcd_setcursor(0, 0);
  lcd_print("Time |   :  :   ");
  //        "Time | xx:xx:xx "

  timer1ms_init(timer1ms_isr);
  timer1ms_enable();

  ext_interrupt_init(ext_interrupt_isr);
  ext_interrupt_enable();

  t_ms = 0;
  t_s = 0;
  t_m = 0;
  t_h = 0;
}

void loop() {
  if (t_s < 10) {
    lcd_setcursor(0, s_index);
    lcd_print("0");
    lcd_setcursor(0, s_index+1);
    lcd_print(t_s);
  }
  else {
    lcd_setcursor(0, s_index);
    lcd_print(t_s);
  }
  if (t_m < 10) {
    lcd_setcursor(0, m_index);
    lcd_print("0");
    lcd_setcursor(0, m_index+1);
    lcd_print(t_m);
  }
  else {
    lcd_setcursor(0, m_index);
    lcd_print(t_m);
  }
  if (t_h < 10){
    lcd_setcursor(0, h_index);
    lcd_print("0");
    lcd_setcursor(0, h_index+1);
    lcd_print(t_h);
  }
  else {
    lcd_setcursor(0, h_index);
    lcd_print(t_h);
  }
}

void h_set_loop() {
  while(true) {
    while (bit_read(_PORTB_, 2) == 0) {
      delay_100us(50);
      while (bit_read(_PORTB_, 2) == 0) { }
      delay_100us(50);
      t_h++;
    }
    while (bit_read(_PORTB_, 1) == 0) {
      delay_100us(50);
      while (bit_read(_PORTB_, 1) == 0) { }
      delay_100us(50);
      t_h--;
    }
  }
    lcd_setcursor(0, h_index);
    lcd_print("  ");
    if (t_h < 10){
      lcd_setcursor(0, h_index);
      lcd_print("0");
      lcd_setcursor(0, h_index+1);
      lcd_print(t_h);
    }
    else {
      lcd_setcursor(0, h_index);
      lcd_print(t_h);
    
  }
}
void m_set_loop() {
  while(true) {
    while (bit_read(_PORTB_, 2) == 0) {
      delay_100us(50);
      while (bit_read(_PORTB_, 2) == 0) { }
      delay_100us(50);
      t_m++;
    }
    while (bit_read(_PORTB_, 1) == 0) {
      delay_100us(50);
      while (bit_read(_PORTB_, 1) == 0) { }
      delay_100us(50);
      t_m--;
    }
    lcd_setcursor(0, m_index);
    lcd_print("  ");
    if (t_m < 10){
      lcd_setcursor(0, m_index);
      lcd_print("0");
      lcd_setcursor(0, m_index+1);
      lcd_print(t_m);
    }
    else {
      lcd_setcursor(0, m_index);
      lcd_print(t_m);
    }
  }
}
void s_set_loop() {
  while(true) {
    while (bit_read(_PORTB_, 2) == 0) {
      delay_100us(50);
      while (bit_read(_PORTB_, 2) == 0) { }
      delay_100us(50);
      t_s++;
    }
    while (bit_read(_PORTB_, 1) == 0) {
      delay_100us(50);
      while (bit_read(_PORTB_, 1) == 0) { }
      delay_100us(50);
      t_s--;
    }
    lcd_setcursor(0, s_index);
    lcd_print("  ");
    if (t_s < 10){
      lcd_setcursor(0, s_index);
      lcd_print("0");
      lcd_setcursor(0, s_index+1);
      lcd_print(t_s);
    }
    else {
      lcd_setcursor(0, s_index);
      lcd_print(t_s);
    }
  }
}

void timer1ms_isr(void) {
  t_ms++;

  if (t_ms == 1000) {
    t_s++;
    t_ms=0;
  }
  if (t_s == 60) {
    t_m++;
    t_s=0;
  }
  if (t_m == 60) {
    t_h++;
    t_m=0;
  }
}

void ext_interrupt_isr() {
  delay_100us(50);
  while (bit_read(_PORTD_, 2) == 0) { }
  delay_100us(50);

  timer1ms_disable();
  
  if (set_mode == 0) {
    set_mode = 1;       //Zeit anzeigen → Stunden setzen
  }
  if (set_mode == 1) {
    set_mode = 2;       //Stunden setzen → Minuten setzen
  }
  if (set_mode == 2) {
    set_mode = 3;       //Minuten setzen → Sekunden setzen
  }
  if (set_mode == 3) {
    set_mode = 0;       //Sekunden setzen → Zeit anzeigen (speichern)
  }

  timer1ms_enable();
}
