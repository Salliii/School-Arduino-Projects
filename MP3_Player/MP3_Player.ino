#include <DFPlayer_Mini_Mp3.h>
#include <controller.h>

SoftwareSerial mp3(0, 1);
bool play = false;
uint8_t volume = 5;

void setup()
{
  volume = 10;
  mp3.begin(9600);
  mp3_set_serial(mp3);
  delay_ms(10);
  mp3_set_volume(volume);
  delay_ms(20);

  bit_init(_PORTD_, 2, IN); //Start-Stop
  bit_init(_PORTB_, 2, IN); //Prev
  bit_init(_PORTB_, 1, IN); //Next
  bit_init(_PORTB_, 4, IN); //Vol-
  bit_init(_PORTB_, 5, IN); //Vol+
}

void loop ()
{
  // play stop
  while (bit_read(_PORTD_, 2) == 0) {
    delay_ms(5);
    while (bit_read(_PORTD_, 2) == 0) {}
    delay_ms(5);

    if (play == false) {
      mp3_play();
      play = true;
      delay_ms(300);
    }
    else if (play == true) {
      mp3_stop();
      play = false;
      delay_ms(300);
    }
  }


  // prev
  while (bit_read(_PORTB_, 2) == 0) {
    delay_ms(5);
    while (bit_read(_PORTB_, 2) == 0) {}
    delay_ms(5);

    mp3_prev();
    delay_ms(300);
  }

  // next
  while (bit_read(_PORTB_, 1) == 0) {
    delay_ms(5);
    while (bit_read(_PORTB_, 1) == 0) {}
    delay_ms(5);

    mp3_next();
    delay_ms(300);
  }


  // Vol-
  while (bit_read(_PORTB_, 4) == 0) {
    delay_ms(5);
    while (bit_read(_PORTB_, 4) == 0) {}
    delay_ms(5);

    if (volume > 0) {
      volume -= 1;
    }

    mp3_set_volume(volume);
    delay_ms(300);
  }
  
  // Vol+
  while (bit_read(_PORTB_, 5) == 0) {
    delay_ms(5);
    while (bit_read(_PORTB_, 5) == 0) {}
    delay_ms(5);

    if (volume < 30) {
      volume += 1;
    }

    mp3_set_volume(volume);
    delay_ms(300);
  }
}
