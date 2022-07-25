#include <controller.h>


void setup() {
  byte_init(_PORTD_, OUT);
}


void loop() 
{
  byte_write(_PORTD_, 0b10010011);

  delay_ms(1000);
  
  byte_write(_PORTD_, mirroring(0b10010011));
  
  while(1);
}


uint8_t mirroring(uint8_t ew) 
{
  uint8_t aw=0;
  
  for (uint8_t n=8; n!=0; n--) 
  {
    if (ew > 127) {
      aw = aw + 128;
    }
    if (n > 1) 
    {
      aw = aw >> 1;
    }
    
    ew = ew << 1;
  }
  
  return aw;
}
