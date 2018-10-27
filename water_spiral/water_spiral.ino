#include <Servo.h>

int pan = 7;
int tilt = 6;
Servo panServo;
Servo tiltServo;
int panAngle = 0; //angle written to the pan servo
int tiltAngle = 0; //angle written to the tilt servo
double tiltCart = 0; //calculated cartesian tilt location
double panCart = 0; //calculated cartesian pan location
double spiral_r = 2; //radius of spiral, varies with time
float pi = 3.141592;
int duration = 12; //seconds to complete a full rotation
double distance = 4; //distance from origin, cm
float r_factor = 0.01; //increments spiral_r
int pour = 60; //pour time in seconds 

void setup() {
  panServo.attach(pan);
  tiltServo.attach(tilt);
  pinMode(8, INPUT);
  Serial.begin(9600);
}


void loop() {
  //causes spiral to switch between spiraling in and out
  if(spiral_r < 0.3) {
    r_factor = r_factor * -1;
    Serial.println("ran");
  }
  else if(spiral_r > 2) {
    r_factor = r_factor * -1;
  }

  //varies radius of the circle with time to create spiral
  spiral_r -= r_factor;
  
  Serial.println(spiral_r);

  //calculates cartesian coordinates of pan and tilt
  panCart = spiral_r * cos(millis()*(2*pi/(duration*1000)));
  tiltCart = spiral_r * sin(millis()*(2*pi/(duration*1000)));

  //converts to spherical coordinates and adjusts for the location of the origin
  panAngle = acos(panCart/(sqrt(pow(panCart, 2) + pow(distance, 2))))*(180/pi) - 60;
  tiltAngle = acos(tiltCart/(sqrt(pow(tiltCart, 2) + pow(distance, 2))))*(180/pi)-2;
  
  panServo.write(panAngle);
  tiltServo.write(tiltAngle);
  delay(100);
}

/*#include <Servo.h>

int pan = 7;
int tilt = 6;
Servo panServo;
Servo tiltServo;
int panAngle = 0; //angle written to the pan servo
int tiltAngle = 0; //angle written to the tilt servo
double tiltCart = 0; //calculated cartesian tilt location
double panCart = 0; //calculated cartesian pan location
double spiral_r = 2; //radius of spiral, varies with time
float pi = 3.141592;
int duration = 12; //seconds to complete a full rotation
double distance = 4; //distance from origin, cm
float r_factor = 0.01; //increments spiral_r
int pour = 60; //pour time in seconds 
boolean go = false; //takes signal from heating to begin
int start_time = 0; 

void setup() {
  panServo.attach(pan);
  tiltServo.attach(tilt);
  pinMode(8, INPUT);
  Serial.begin(9600);
}


void loop() {
  if(digitalRead(8)==HIGH) {
    go = true;
    start_time = millis();
    
  }
  if(go==true) {
    run();
  }
}

void run()  {
  if(millis-start_time>=(pour*1000)) {
    go = false;
  }
  
    //causes spiral to switch between spiraling in and out
  if(spiral_r < 0.3) {
    r_factor = r_factor * -1;
    Serial.println("ran");
  }
  else if(spiral_r > 2) {
    r_factor = r_factor * -1;
  }

  //varies radius of the circle with time to create spiral
  spiral_r -= r_factor;
  
  Serial.println(spiral_r);

  //calculates cartesian coordinates of pan and tilt
  panCart = spiral_r * cos(millis()*(2*pi/(duration*1000)));
  tiltCart = spiral_r * sin(millis()*(2*pi/(duration*1000)));

  //converts to spherical coordinates and adjusts for the location of the origin
  panAngle = acos(panCart/(sqrt(pow(panCart, 2) + pow(distance, 2))))*(180/pi) - 60;
  tiltAngle = acos(tiltCart/(sqrt(pow(tiltCart, 2) + pow(distance, 2))))*(180/pi)-2;
  
  panServo.write(panAngle);
  tiltServo.write(tiltAngle);
  delay(100);
}*/
