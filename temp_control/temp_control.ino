int power = 8; //Pin connecting to relay that controls power to heating coil 
int therm = A0; //Pin connected to thermistor
long val;

void setup() {
  // put your setup code here, to run once:
  pinMode(power, OUTPUT);
  Serial.begin(9600);
}

int convertTemp() {
  long temp;
  val = analogRead(therm); //Raw voltage diff across thermistor
  temp = 0.00027*pow(val,2) - 0.23*val + 77;  //Calibration curve from volt to temp
  Serial.print(val);
  Serial.print(',');
  Serial.println(temp);
  return temp;
}

void control() {
// If water temp is above 92 degrees, turn coil off, 
// If water temp is below 90 degrees, turn coil on
// Accounts for momentum to reach 95 degrees
 
  long temp;
  temp = convertTemp();
  if (temp >= 92) {
    digitalWrite(power,LOW);
    }
  if (temp <= 90) {
    digitalWrite(power,HIGH);
    }
  }


void loop() {
  // put your main code here, to run repeatedly:
  control();
}
