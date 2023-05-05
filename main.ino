#include <RH_ASK.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int BIT_RATE = 2000;

const int RX_PIN = 14;

RH_ASK driver(BIT_RATE, RX_PIN);

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(12, OUTPUT);
  driver.init();
  lcd.print("WELCOME!");
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {
    lcd.clear();
    lcd.setCursor(3,1);
    lcd.print((char*)buf);
    lcd.setCursor(3,0);
    lcd.print("EMERGENCY!");


    for (int i = 0; i < buflen; i++)
      Serial.print((char) buf[i]);
    Serial.println("");
    int b=0;
    while(b<10){
    delay(500);
    digitalWrite(2,LOW);
    digitalWrite(12,HIGH);
    delay(500);
    digitalWrite(2,HIGH);
    digitalWrite(12,LOW);
    b++;
    }
  lcd.clear();
  lcd.print("PUSH BUTTON");
  lcd.setCursor(0,1);
  lcd.print("EMERGENCY CALLER");
  }
}
