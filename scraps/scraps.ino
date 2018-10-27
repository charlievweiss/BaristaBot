/*This code does something mysterious because someone didn't comment her code

***NOTE***
I'm using arduino's pinMode(INPUT_PULLUP), which eliminates the need for a pulldown resistor in the button circuit, so it can be cleaner. It works with a button between the pin and ground, so the default state will be "HIGH" rather than "LOW" (which is the opposite as before).


TODO: Add an Estop button
*/

int start_button_pin = 8; // starts cycle, default HIGH. When pushed, will read LOW. You'll want to hold the button.
int valve_pin = 10; // turns solenoid on and off
int pour_time = 10000; // time the solenoid stays open in milliseconds
long start_time = 0;
long current_time = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(valve_pin,OUTPUT);
  pinMode(start_button_pin,INPUT_PULLUP); // default HIGH
  start_time = millis(); // set start time
}

void loop() {
  // start the cycle and open the valve if the button is pushed (will restart cycle if pushed again)
  // **NOTE this will probably print a few times because of the length of the button push
  if (!digitalRead(start_button_pin)){
      start_time = millis();
      digitalWrite(valve_pin, HIGH);
      Serial.println("Begin");
  }
  // if the pour time has passed, set valve to off
  current_time = millis(); // get current time
  if((current_time-start_time) >= pour_time) {
      // turn off if time has passed
    digitalWrite(valve_pin, LOW);
    Serial.println("End");
  }
}
