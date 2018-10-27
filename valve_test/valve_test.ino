/*This code does something mysterious because someone didn't comment her code

***NOTE***
I'm using arduino's pinMode(INPUT_PULLUP), which eliminates the need for a pulldown resistor in the button circuit, so it can be cleaner. It works with a button between the pin and ground, so the default state will be "HIGH" rather than "LOW" (which is the opposite as before).

*/

int button_pin = 8; // starts cycle, default HIGH
int valve_pin = 10; // turns solenoid on and off
int pour_time = 10000; // time the solenoid stays open in milliseconds
bool go = false;
bool complete = false;
long start_time = millis();
long current_time = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(valve_pin,OUTPUT);
  pinMode(button_pin,INPUT_PULLUP); // default HIGH
}

void loop() {
  Serial.println(go);
  
  if ((digitalRead(button_pin)==1) && (complete == 0)){
    go = true;
    digitalWrite(valve_pin,HIGH);
    Serial.print("pouring");
    }
  else if ((digitalRead(button_pin)==1) && (complete == 1)) {
    go = false;
    Serial.print("finished");
    }
  if (digitalRead(button_pin)==0){
    digitalWrite(valve_pin,LOW);
    Serial.print("waiting");
    }
  if (go == 1){
    run();
    }
}

void run()  {
  current_time = millis();
  if(current_time-start_time>=(pour_time)) {
    go = false;
    complete = true;
    digitalWrite(valve_pin, LOW);
  }
}