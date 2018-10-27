/*This code does something mysterious because someone didn't comment her code

***NOTE***
I'm using arduino's pinMode(INPUT_PULLUP), which eliminates the need for a pulldown resistor in the button circuit, so it can be cleaner. It works with a button between the pin and ground, so the default state will be "HIGH" rather than "LOW" (which is the opposite as before).

*/

int button_pin = 8; // starts cycle, default HIGH. When pushed, will read LOW. You'll want to hold the button.
int valve_pin = 10; // turns solenoid on and off
int pour_time = 10000; // time the solenoid stays open in milliseconds
bool go = false;
bool complete = false;
long start_time = 0;
long current_time = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(valve_pin,OUTPUT);
  pinMode(button_pin,INPUT_PULLUP); // default HIGH
  start_time = millis(); // set start time
}

void loop() {
  Serial.println(go);
  
  if ((digitalRead(button_pin)==0) && (complete == 0)){ 
    // button on and incomplete? Open valve
    go = true;
    digitalWrite(valve_pin,HIGH);
    Serial.print("pouring");
    }
  else if ((digitalRead(button_pin)==0) && (complete == 1)) {
    // button on and complete? go is false?
    go = false;
    Serial.print("finished");
    }
  if (digitalRead(button_pin)==1){
    // button is off, close valve
    digitalWrite(valve_pin,LOW);
    Serial.print("waiting");
    }
  if (go == 1){
    // if go is true, run?
    run();
    }
}

void run()  {
    // if the pour time has passed, set valve to off and complete to true, and turn off valve
  current_time = millis(); //get current time
  if((current_time-start_time) >= pour_time) {
    go = false;
    complete = true;
    digitalWrite(valve_pin, LOW);
  }
}