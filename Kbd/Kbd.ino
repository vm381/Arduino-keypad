#include <Kbd.h>
#include <LiquidCrystal_I2C.h>

int rowPins[Kbd::ROWS] = { 7, 6, 5, 4 };
int colPins[Kbd::COLS] = { 11, 10, 9, 8 };

Kbd kbd(rowPins, colPins);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int cursorRow = 0;
int cursorCol = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(cursorCol, cursorRow);

  Serial.begin(9600);
}

void loop() {
  if (cursorCol == 16 && cursorRow == 0) {
    cursorRow++;
    cursorCol = 0;
    lcd.setCursor(0, 1);
  }
  if (cursorCol == 16 && cursorRow == 1) {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("                ");
    cursorRow = 0;
    cursorCol = 0;
    lcd.setCursor(0, 0);
  }

  char ch = kbd.readKey();
  if (ch != '\0') {
    lcd.print(ch);
    cursorCol++;
    Serial.println("Char: " + String(ch));
  }
}
