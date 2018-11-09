//This code opens the solenoid valve for 10 seconds when the water is above our
//threshold temperature and spirals the pan-tilt

// Set up for spiral 
#include <Servo.h>
int pan = 7;
int tilt = 6;
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
int signal_pin = 8;         // Pin that goes to high when water is at temp
int valve = 10;             // Pin controlling solenoid valve
int grind_pin = 12;         // Pin signaling the grinder to start up
long wet_filter = 5000;     // Pour for 5 seconds just to get the filter wet 
long wet_pause = 10000;     // Pause for 20 to wait for beans to drop in filter
long bloom_time = 10000;    // Initial pour 15 seconds
long pause = 10000;         // Time between bloom and pour 20 seconds
long pour_time = 10000;     // 30 seconds
bool set_timer = false;     // 
bool complete = true;       // Starts true, set false by button. False until the pour is completed
long start_time;            //
long current_time;          //
long elapsed;

//Set up for reset
int button = 4;
int buttonState;

void setup() {
  // put your setup code here, to run once:
panServo.attach(pan);
tiltServo.attach(tilt);
pinMode(signal_pin,INPUT);
pinMode(valve,OUTPUT);
pinMode(button,INPUT);
pinMode(grind_pin,OUTPUT);
Serial.begin(9600);
panServo.write(42);
tiltServo.write(85);
}

void loop() {
  // put your main code here, to run repeatedly:

  buttonState = digitalRead(button);
  Serial.println(complete);
  if (( buttonState == HIGH)&&(complete == true)) {
    reset();
    Serial.println("RESET");
    }
  
  if (digitalRead(signal_pin) == 1 && complete==false) {
    if (set_timer == false){
      // The first time that the signal pin is high, this code will run once  
      // to record the current time, then it will not run again.
      start_time = millis();
      set_timer = true;
      }
    pour();
    }
  else {
    Serial.println("Heating");
    }  
}


void pour() {
  // Opens the valve for 10 seconds, and then closes it and sets complete to true
    current_time = millis();
    elapsed = (current_time - start_time);
  Serial.println(elapsed);
  if ( elapsed <= wet_filter ){
    digitalWrite(valve,HIGH);
    digitalWrite(grind_pin,HIGH);
    spiral();
    Serial.println("wetting filter");
    }
  else if ( elapsed <= wet_filter + wet_pause){
    digitalWrite(valve,LOW);
    Serial.println("Waiting for beans");
    }
  else if ( elapsed <= wet_filter + wet_pause + bloom_time ) {
    //Pours for desired bloom time
    digitalWrite(valve,HIGH);
    spiral();
    Serial.println("blooming");
    }
  else if ( elapsed <= wet_filter + wet_pause + bloom_time + pause) {
    //Pauses to allow blooming to occur in beans
    digitalWrite(valve,LOW);
    Serial.println("bloom pause");
    }
  else if ( elapsed <= wet_filter + wet_pause + bloom_time + pause + pour_time) {
    //Main pour 
    digitalWrite(valve,HIGH);
    spiral();
    Serial.println("pouring");
    }  
  else if ( elapsed >= wet_filter + wet_pause + bloom_time + pause + pour_time) {
    // The entire pouring cycle is complete
    digitalWrite(valve,LOW);
    panServo.write(42);  // re-center the nozzle while waiting
    tiltServo.write(85); // re-center the nozzle while waiting
    complete = true;
    delay(5000);  // Debouncing so we don't immediately reenter blooming
    Serial.println("finished");
    }
    
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

void reset() {
  set_timer = false;
  complete = false;
  spiral_r = 0.3;  //reseting the radius to start from the center
  }
  
