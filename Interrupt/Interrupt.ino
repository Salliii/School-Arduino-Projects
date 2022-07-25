#include <controller.h>

volatile uint8_t dir=0;

void setup() {
  bit_init(_PORTB_, 2, OUTPUT);
  bit_init(_PORTB_, 4, OUTPUT);
  bit_init(_PORTB_, 5, OUTPUT);
  
  bit_init(_PORTD_, 2, INPUT);
  
  ext_interrupt_init(ext_interrupt_isr);
}

void loop() {
  if (dir == 0) {
    bit_write(_PORTB_, 2, HIGH);
    bit_write(_PORTB_, 4, LOW);
    bit_write(_PORTB_, 5, LOW);

    delay_ms(200);

    bit_write(_PORTB_, 2, LOW);
    bit_write(_PORTB_, 4, HIGH);
    bit_write(_PORTB_, 5, LOW);
    
    delay_ms(200);
    
    bit_write(_PORTB_, 2, LOW);
    bit_write(_PORTB_, 4, LOW);
    bit_write(_PORTB_, 5, HIGH);
    
    delay_ms(200);
  }

  else {
    bit_write(_PORTB_, 2, LOW);
    bit_write(_PORTB_, 4, LOW);
    bit_write(_PORTB_, 5, HIGH);

    delay_ms(200);

    bit_write(_PORTB_, 2, LOW);
    bit_write(_PORTB_, 4, HIGH);
    bit_write(_PORTB_, 5, LOW);
    
    delay_ms(200);
    
    bit_write(_PORTB_, 2, HIGH);
    bit_write(_PORTB_, 4, LOW);
    bit_write(_PORTB_, 5, LOW);
    
    delay_ms(200);
  }
}



void ext_interrupt_isr(void) {
  delay_100us(50);
  while(bit_read(_PORTD_, 2) == 0){ }
  delay_100us(50);

  if (dir == 0) {
    dir = 1;
  }
  else {
    dir = 0;
  }

  EIFR|=0;
}
