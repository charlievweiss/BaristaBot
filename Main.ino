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

// Set up for spiral 
#include <Servo.h>
int pan = 1;
int tilt = 2;
Servo panServo;
Servo tiltServo;
int panAngle = 0; //angle written to the pan servo
int tiltAngle = 0; //angle written to the tilt servo
double tiltCart = 0; //calculated cartesian tilt location
double panCart = 0; //calculated cartesian pan location
double spiral_r = 0.3; //radius of spiral, varies with time
double min_rad = 0.3;
double max_rad = 1.2;
int duration = 4; //seconds to complete a full rotation
double distance = 4; //distance from origin, cm
float r_factor = 0.005; //increments max_rad
int calibrate_pan = 49;
int calibrate_tilt = 2;


//Set up for valve
//int signal_pin = 8;         // Pin that goes to high when water is at temp
int valve = 3;             // Pin controlling solenoid valve
//int grind_pin = 12;         // Pin signaling the grinder to start up
long wet_filter = 5000;     // Pour for 5 seconds just to get the filter wet 
long pause = 10000;     // Pause for 20 to wait for beans to drop in filter
long bloom = 10000;    // Initial pour 15 seconds
//long pause = 10000;         // Time between bloom and pour 20 seconds
long pour_time = 10000;     // 30 seconds
long grind_time = 30000;
long brew_time = 10000;
long longpour = 15000;
long convey = 5000;
long convey2 = 10000;
long cup_time = 5000;

bool button_press = false;
bool coffee_prep = false;
bool complete = false;
bool water_hot = false;
long elapsed;






int bean_level = A0;
int water_level = A1;
int cup_level = A2;
//int pour_pin = 6;
int grind_pin = 10;
int button = 11;
int temp_pin = 12; //The pin that tells us if the water is hot
long current_time;
long start_time;
//long go_grind = 1000;
//long grind_time = 10000;
bool stocked = false;
int set_timer = 0;


// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
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
//  pinMode(pour_pin, OUTPUT);
//  pinMode(grind_pin, OUTPUT);



  //from temp triggered pour
  panServo.attach(pan);
  tiltServo.attach(tilt);
//  pinMode(signal_pin,INPUT);
  pinMode(valve,OUTPUT);
  pinMode(button,INPUT);
  pinMode(grind_pin,OUTPUT);
  Serial.begin(9600);
  panServo.write(42);
  tiltServo.write(85);

  
}

void pour_on() {
    digitalWrite(valve,HIGH);
    spiral();
//    Serial.println("Pouring");    
  }
void pour_off(){
    digitalWrite(valve,LOW);
    panServo.write(42);  // re-center the nozzle while waiting
    tiltServo.write(85); // re-center the nozzle while waiting
  }

void spiral() {
  //causes spiral to switch between spiraling in and out
  if(spiral_r < min_rad) {
    r_factor = r_factor * -1;
  }
  else if(spiral_r > max_rad) {
    r_factor = r_factor * -1;
  }

  //varies radius of the circle with time to create spiral
  spiral_r -= r_factor;
  
//  Serial.println(spiral_r);

  //calculates cartesian coordinates of pan and tilt
  panCart = spiral_r * cos(millis()*(2*M_PI/(duration*1000)));
  tiltCart = spiral_r * sin(millis()*(2*M_PI/(duration*1000)));

  //converts to spherical coordinates and adjusts for the location of the origin
  panAngle = acos(panCart/(sqrt(pow(panCart, 2) + pow(distance, 2))))*(180/M_PI) - calibrate_pan;
  tiltAngle = acos(tiltCart/(sqrt(pow(tiltCart, 2) + pow(distance, 2))))*(180/M_PI) - calibrate_tilt;
  
  panServo.write(panAngle);
  tiltServo.write(tiltAngle);
  delay(100);
}

void button_status() {
  if (digitalRead(button) == HIGH){
    button_press = true;
    }
  }

void machine_status() {

if (coffee_prep == false){
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
    lcd.print("Ready to grind beans");
    stocked = true;
  }
}

if (coffee_prep == true){
  if (digitalRead(temp_pin)==0) {
    lcd.print("Water Heating");
    water_hot = false;
  }
  else if(digitalRead(temp_pin)==1) {
    lcd.print("Ready to brew!");
    water_hot = true;
    }
  }
  

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
}


void dispense(){
  digitalWrite(20,HIGH);
  // This is not the correct code, replace with dispensing code
  
  }

int conveyor(int num_steps){
  digitalWrite(21,HIGH);
//  Serial.println(num_steps);
  // This is not the correct code, replace with stepper code
  
  }



void prep_coffee(){
  current_time = millis();
  elapsed = current_time - start_time;
//  Serial.print(elapsed);
//  Serial.print(",");
  if (elapsed < wet_filter){
    pour_on();
    Serial.println("wetting filter");
    }
  else if (elapsed < wet_filter + pause){
    pour_off();
    Serial.println("draining filter");
    }

  else if (elapsed < wet_filter + pause + grind_time){
    digitalWrite(grind_pin, HIGH);
    Serial.print("grinding");
    Serial.print(",");
      if(elapsed < wet_filter + pause + cup_time){
        dispense();
        Serial.println("cup");
        }
      else if(elapsed < wet_filter + pause + cup_time + convey){
        conveyor(10);
        Serial.println("conveyor");
      }
  else if (elapsed > wet_filter + pause + grind_time) {
    digitalWrite(grind_pin, LOW);
    Serial.println("Finished prepping");
//    start_time = wet_filter + pause + grind_time;
    coffee_prep = true;
    }
  }
}


void brew_coffee(){
  current_time = millis();
  elapsed = current_time - start_time;
//  Serial.println(elapsed);
  if (elapsed < bloom){
    pour_on();
    }
  else if(elapsed < bloom + pause){
    pour_off();
    }
  else if(elapsed < bloom + pause + longpour){
    pour_on();
    }
  else if(elapsed < bloom + pause + longpour + brew_time){
    pour_off();
    }
  else if(elapsed < bloom + pause + longpour + brew_time + convey2){
    conveyor(10);
    }  
  else{
    complete = true;
    }  
}

    
void reset(){
  coffee_prep = false;
  complete = false;
  set_timer = 0;
  stocked = false;
  button_press = false;
  }


void loop() {
  machine_status();
  button_status();
//  current_time = millis();
  if (stocked == true && button_press == true && complete == false){
//  Serial.println("stocked");
    
      if (coffee_prep == false){
        if (set_timer == 0){
          Serial.println(start_time);
          start_time = millis();
          set_timer = 1;
          }
        prep_coffee();
      }
//      if (coffee_prep == true && water_hot == true){    THIS IS THE ACTUAL IF STATEMENT
     if (coffee_prep == true){
        Serial.println("ENTERING BREW");
        if (set_timer == 1){
          Serial.println(start_time);
          start_time = millis();
          set_timer = 2;          // ASK maya, this a really janky way of keeping time, but it will work
          }
        brew_coffee();
        }
  
      }
  
  else if (stocked == false && button_press == true){
    Serial.println("Check machine status");
    }
  else {
//    Serial.println("Waiting");
    digitalWrite(grind_pin,LOW);
    // write an all low function
    }
  }
