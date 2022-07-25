#include <controller.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN A4
#define SS_PIN 10


uint8_t i, value, value1, add;
unsigned int validUID[] = {42, 5, 23, 211};  //d3 17 5 2a
byte valid = false;


MFRC522 mfrc522(SS_PIN, RST_PIN);


void setup()
{
  SPI.begin();
  mfrc522.PCD_Init();

  lcd_init();
  lcd_clear();
}


bool validation() {
  for (int i = 3; i >= 0; i--) {
    lcd_print(String(mfrc522.uid.uidByte[i], HEX));
    if ( validUID[i] != mfrc522.uid.uidByte[i]) {
      return false;
    }
  }
  return true;
}

void loop() {
  if ((mfrc522.PICC_IsNewCardPresent()) && (mfrc522.PICC_ReadCardSerial()))
  {
    lcd_clear();
    lcd_setcursor(0, 0);


    if (validation() == true) {
      lcd_print("Val(U)id");
    }
    else {
      lcd_print("geh fort!");
    }

    delay_ms(3000);
    lcd_clear();


    mfrc522.PICC_HaltA();
    delay_ms(1000);
  }
}
