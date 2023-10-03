#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
const int ldrPin = A0; 
const int pingPin = 7;

void setup() {
  pinMode(ldrPin, INPUT); 
  lcd.begin(16, 2);  
}

void loop(){
  ping();
  int ldrStatus = analogRead(ldrPin);
  lcd.clear(); 
  lcd.setCursor(2, 0); 
  lcd.print("Go Wildcats!"); 
  if (ldrStatus >= 102){ //
    lcd.setCursor(0, 1);
    lcd.print("DARK! ");
    lcd.print(ldrStatus);
    lcd.print(" ");
  } 
  if (ldrStatus <= 102){
    lcd.setCursor(0, 1);
    lcd.print("LIGHT! ");
    lcd.print(ldrStatus);
    lcd.print(" ");
  }
  delay(500);
}

void ping(){
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  //convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  lcd.print(inches);
  lcd.print("in");
  delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
