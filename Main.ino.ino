/*
  LiquidCrystal Library - Hello World
  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.
  This sketch prints "Hello World!" to the LCD
  and shows the time.
  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)
  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld
*/

int bean_level = A5;
int water_level = A4;
int cup_level = A3;
int pour_pin = 6;
int grind_pin = 5;
long current_time;
long start_time;
long go_grind = 1000;
long grind_time = 10000;
bool stocked = false;
bool set_timer = false;


// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("                ");

  pinMode(bean_level, INPUT);
  pinMode(water_level, INPUT);
  pinMode(cup_level, INPUT);
  pinMode(pour_pin, OUTPUT);
  pinMode(grind_pin, OUTPUT);
}

void check_status() {

//  Serial.println(stocked);

  if (analogRead(bean_level) > 500) {
    lcd.print("Refill beans pls");
    stocked = false;
  }
  else if (analogRead(water_level) > 400) {
    lcd.print("Refill water pls");
    stocked = false;
  }
  else if (analogRead(cup_level) > 500) {
    lcd.print("Refill cups pls");
    stocked = false;
  }
  else {
    lcd.print("Ready to brew      ");
    stocked = true;
  }
  

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
}

void brew_coffee(){
  current_time = millis();
//  Serial.println(current_time - start_time);
  if (current_time - start_time < go_grind){
    digitalWrite(grind_pin, HIGH);
    Serial.println("Grinding");
    }
  else if (current_time - start_time <= grind_time){
    digitalWrite(grind_pin,LOW);
    } 
  else if (current_time - start_time <= grind_time+5000){
    digitalWrite(pour_pin,HIGH);
    Serial.println("Pouring");
    }
  else if (current_time - start_time >= grind_time+5000){
    digitalWrite(pour_pin,LOW);
    Serial.println("Finished");
    }  
  }

void reset(){
  set_timer = false;
  }

void loop() {
  check_status();
  current_time = millis();
  if (stocked == true){
//  Serial.println("stocked");
    if (set_timer == false){
      start_time = millis();
      set_timer = true;
      }
      brew_coffee();
  }
  else {
    Serial.println("Check machine status");
    digitalWrite(grind_pin,LOW);
    }
  }
