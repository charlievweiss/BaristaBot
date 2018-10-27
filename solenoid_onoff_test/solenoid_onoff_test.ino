/*This code simply turns the solenoid on and off continuously*/

int valve_pin = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(valve_pin,OUTPUT);
}

void loop() {
  digitalWrite(valve_pin,HIGH); //valve on
  delay(500);
  digitalWrite(valve_pin,LOW); //valve off
  delay(500);
}
