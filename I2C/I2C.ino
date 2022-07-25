#include <controller.h>

#define ADDR 0x91


uint8_t temp, trash;


void setup() {
  i2c_init();
  lcd_init();

  lcd_clear();
  lcd_setcursor(0,0);
  lcd_print("Temp: ");
}


void loop() {
  i2c_start();
  
  i2c_write(ADDR);
  
  temp = i2c_read(0);
  trash = i2c_read(1);

  i2c_stop();
  
  lcd_setcursor(0,6);
  lcd_byte(temp);
  lcd_char(0xDF);
  lcd_print("C ");
  
  delay_ms(500);
}
