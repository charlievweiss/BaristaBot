/*This file does 3 things:
1. reads temperature of water and converts it
2. turns coil on and off according to temperature
3. sends a signal to the solenoid based on temperature (HIGH or LOW)
*/

int power = 8; //Pin connecting to relay that controls power to heating coil 
int therm = A5; //Pin connected to thermistor
int pour = 9; // talks to the solenoid valve on another arduino
long val; // stores temperature voltage
long temp; // stores converted temperature

int min_temp = 90;
int max_temp = 92;
int off_state_temp = 50;
int on_state_temp = 92;

//int min_temp = 50;
//int max_temp = 52;
//int off_state_temp = 30;
//int on_state_temp = 52;

void setup() {
  // put your setup code here, to run once:
  pinMode(power, OUTPUT);
  pinMode(pour, OUTPUT);
  Serial.begin(9600);
  digitalWrite(pour,LOW); // send low signal
}

void loop() {
  // put your main code here, to run repeatedly:
  /*TESTING BASIC OUTPUT
  digitalWrite(pour,HIGH);
  delay(500);
  digitalWrite(pour,LOW);
  delay(500);*/

  convert_temp(); // reads current temp from thermistor and converts to celcius
  coil_control(); // turns coil on and off according to temp reading
  send_state(); // sends state to another arduino which controls solenoid valve8
}

void convert_temp() {
  val = analogRead(therm); //Raw voltage diff across thermistor
  temp = 0.00027*pow(val,2) - 0.23*val + 77;  //Calibration curve from volt to temp
  Serial.print(val);
  Serial.print(',');
  Serial.println(temp);
}

void coil_control() {
// If water temp is above 92 degrees, turn coil off, 
// If water temp is below 90 degrees, turn coil on
// Accounts for momentum to reach 95 degrees
 
  if (temp >= max_temp) {
    digitalWrite(power,LOW);
    }
  if (temp <= min_temp) {
    digitalWrite(power,HIGH);
    }
  }

void send_state() {
  // send a high signal out to solenoid if temperature is above 90, low signal if below 80
  if (temp > on_state_temp) {
    digitalWrite(pour,HIGH);
//    Serial.println("pouring now");
  }
  else if (temp < off_state_temp) {
    digitalWrite(pour,LOW);
//    Serial.println("heating");
  }
}
