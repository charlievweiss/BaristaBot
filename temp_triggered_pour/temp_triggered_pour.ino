//This code opens the solenoid valve for 10 seconds when the water is above our threshold temperature


int signal_pin = 8;         // Pin that rails high when water is at temp
int valve = 10;             // Pin controlling solenoid valve
int pour_time = 10000;      // 10 seconds
bool set_timer = false;     // 
bool complete = false;      // False until the pour is completed
long start_time;            //
long current_time;          //


void setup() {
  // put your setup code here, to run once:
pinMode(signal_pin,INPUT);
pinMode(valve,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (digitalRead(signal_pin) == 1 && complete==false) {
    Serial.println("Pouring");
    if (set_timer == false){
      // The first time that the signal pin is high, this code will run once  
      // to record the current time, then it will not run again.
      start_time = millis();
      set_timer = true;
      }
    run();
    }
  else {
    Serial.println("Heating");
    }  
}


void run() {
  // Opens the valve for 10 seconds, and then closes it and sets complete to true
  
  digitalWrite(valve,HIGH);
  current_time = millis();
  if ( current_time - start_time > pour_time ) {
    Serial.println("Finished");
    digitalWrite(valve,LOW);
    complete = true;
    }
  }
