#include <controller.h>

/*
   Autos grün: PB2
   Autos gelb: PB4
   Autos rot : PB5

   Fußgänger grün: PC1
   Fußgänger rot : PC2

   Taster : PD2
*/


void setup() {
  bit_init(_PORTB_, 2, OUTPUT);
  bit_init(_PORTB_, 4, OUTPUT);
  bit_init(_PORTB_, 5, OUTPUT);

  bit_init(_PORTC_, 1, OUTPUT);
  bit_init(_PORTC_, 2, OUTPUT);

  bit_init(_PORTD_, 2, INPUT);

  ext_interrupt_init(ext_interrupt_isr);

  set_startpos();
}

void loop() {
  delay_ms(10000);                  //10000ms = 10sek Grünphase Autoverkehr
  car_to_ped();
  delay_ms(3000);
  ped_to_car();
}


void set_startpos() {
  bit_write(_PORTB_, 2, HIGH);
  bit_write(_PORTB_, 4, LOW);
  bit_write(_PORTB_, 5, LOW);
  bit_write(_PORTC_, 1, LOW);
  bit_write(_PORTC_, 2, HIGH);
}


void car_to_ped() {
  bit_write(_PORTB_, 2, LOW);
  bit_write(_PORTB_, 4, HIGH);
  bit_write(_PORTB_, 5, LOW);
  bit_write(_PORTC_, 1, LOW);
  bit_write(_PORTC_, 2, HIGH);

  delay_ms(1000);                   //1000ms = 1sek Gelbphase

  bit_write(_PORTB_, 2, LOW);
  bit_write(_PORTB_, 4, LOW);
  bit_write(_PORTB_, 5, HIGH);
  bit_write(_PORTC_, 1, LOW);
  bit_write(_PORTC_, 2, HIGH);

  delay_ms(1000);                   //1000ms = 1sek Rotphase bis Autos stehen

  bit_write(_PORTB_, 2, LOW);
  bit_write(_PORTB_, 4, LOW);
  bit_write(_PORTB_, 5, HIGH);
  bit_write(_PORTC_, 1, HIGH);
  bit_write(_PORTC_, 2, LOW);
}


void ped_to_car() {
  bit_write(_PORTB_, 2, LOW);
  bit_write(_PORTB_, 4, LOW);
  bit_write(_PORTB_, 5, HIGH);
  bit_write(_PORTC_, 1, LOW);
  bit_write(_PORTC_, 2, HIGH);

  delay_ms(1000);                   //1000ms = 1ek Rotphase bis Fußgänger überquert

  bit_write(_PORTB_, 2, LOW);
  bit_write(_PORTB_, 4, HIGH);
  bit_write(_PORTB_, 5, HIGH);
  bit_write(_PORTC_, 1, LOW);
  bit_write(_PORTC_, 2, HIGH);

  delay_ms(1000);                   //1000ms = 3sek Gelbphase

  bit_write(_PORTB_, 2, HIGH);
  bit_write(_PORTB_, 4, LOW);
  bit_write(_PORTB_, 5, LOW);
  bit_write(_PORTC_, 1, LOW);
  bit_write(_PORTC_, 2, HIGH);
}


void manual() {
  bit_write(_PORTB_, 2, LOW);
  bit_write(_PORTB_, 4, HIGH);
  bit_write(_PORTB_, 5, LOW);
  bit_write(_PORTC_, 1, LOW);
  bit_write(_PORTC_, 2, HIGH);

  delay_100us(10000);                   //1000ms = 1sek Gelbphase

  bit_write(_PORTB_, 2, LOW);
  bit_write(_PORTB_, 4, LOW);
  bit_write(_PORTB_, 5, HIGH);
  bit_write(_PORTC_, 1, LOW);
  bit_write(_PORTC_, 2, HIGH);

  delay_100us(10000);                   //1000ms = 1sek Rotphase bis Autos stehen

  bit_write(_PORTB_, 2, LOW);
  bit_write(_PORTB_, 4, LOW);
  bit_write(_PORTB_, 5, HIGH);
  bit_write(_PORTC_, 1, HIGH);
  bit_write(_PORTC_, 2, LOW);

  delay_100us(30000);                   //30000us = 3sek Fußgänger

  bit_write(_PORTB_, 2, LOW);
  bit_write(_PORTB_, 4, LOW);
  bit_write(_PORTB_, 5, HIGH);
  bit_write(_PORTC_, 1, LOW);
  bit_write(_PORTC_, 2, HIGH);

  delay_100us(10000);                       //1000ms = 1ek Rotphase bis Fußgänger überquert

  bit_write(_PORTB_, 2, LOW);
  bit_write(_PORTB_, 4, HIGH);
  bit_write(_PORTB_, 5, HIGH);
  bit_write(_PORTC_, 1, LOW);
  bit_write(_PORTC_, 2, HIGH);

  delay_100us(10000);                       //1000ms = 3sek Gelbphase

  bit_write(_PORTB_, 2, HIGH);
  bit_write(_PORTB_, 4, LOW);
  bit_write(_PORTB_, 5, LOW);
  bit_write(_PORTC_, 1, LOW);
  bit_write(_PORTC_, 2, HIGH);
}

void ext_interrupt_isr(void) {
  delay_100us(50);
  while (bit_read(_PORTD_, 2) == 0) {}
  delay_100us(50);
  manual();
}
