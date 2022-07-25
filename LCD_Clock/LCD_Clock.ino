#include <controller.h>

volatile uint16_t t_ms, t_s, t_m, t_h;


void setup() {
  lcd_init();
  lcd_clear();
  lcd_setcursor(0,0);
  lcd_print("Time |   :  :   ");
  //        "Time | xx:xx:xx "
  
  timer1ms_init(timer1ms_isr);
  timer1ms_enable();

  t_ms = 0;
  t_s = 0;
  t_m = 0;
  t_h = 0;
}

void loop() {
  if t_s < 10{
    lcd_setcursor(0, s_index);
    lcd_print("0");
    lcd_setcursor(0, s_index+1);
    lcd_print(t_s);
  else {
    lcd_setcursor(0, s_index);
    lcd_print(t_s);
  }

  if t_m < 10{
    lcd_setcursor(0, m_index);
    lcd_print("0");
    lcd_setcursor(0, m_index+1);
    lcd_print(t_m);
  else {
    lcd_setcursor(0, m_index);
    lcd_print(t_m);
  }

  if t_s < 10{
    lcd_setcursor(0, h_index);
    lcd_print("0");
    lcd_setcursor(0, h_index+1);
    lcd_print(t_h);
  else {
    lcd_setcursor(0, h_index);
    lcd_print(t_h);
  }
}


void timer1ms_isr(void) {
  t_msek++;

  if (t_msek == 1000) {
    t_sek++;
    t_msek=0;
  }
  
  if (t_sek == 60) {
    t_min++;
    t_sek=0;
  }
  
  if (t_min == 60) {
    t_hour++;
    t_min=0;
  }
}
