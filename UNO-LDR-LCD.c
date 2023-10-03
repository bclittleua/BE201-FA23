/* Arduino Tutorial: Learn how to use an LCD 16x2 screen
   More info: https://www.instructables.com/How-to-use-an-LCD-displays-Arduino-Tutorial/ */

//Include LCD library
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // initialize the library and define which of the Uno's pins operate the LCD 
const int ldrPin = A0; // set the LDR to read on analog pin 0

void setup() {
  pinMode(ldrPin, INPUT); // Here LDR sensor is determined as input.
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
}

void loop(){
  // NOTE: Code usually begins counting at zero rather than 1... the first line of the LCD is line 0 (zero), second line is line 1.
  int ldrStatus = analogRead(ldrPin);
  lcd.clear(); // clears the LCD in case it has info from previous loop or loaded with junk characters when powered
  lcd.setCursor(2, 0); // first number is the character offset (0-15), second number is the line number (zero in this case)
  lcd.print("Go Wildcats!"); // this will display on first line with 2 characters empty before message
  if (ldrStatus >= 102){ //
    lcd.setCursor(1, 1); // offset by one on second line
    lcd.print("TOO DARK! ");
    lcd.print(ldrStatus); // we didn't setcursor first, so ldrStatus will print on same line as TOO DARK!
  } 
  elif (ldrStatus <= 102){
  lcd.setCursor(1, 1);
  lcd.print("BRIGHT! ");
  lcd.print(ldrStatus);
  }
  delay(500); // time to wait before restarting loop
}
