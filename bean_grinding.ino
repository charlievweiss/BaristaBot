int sig = 8; //signal to begin grinding process
int grind = 9; //powers motor to grind beans
int contact = 10; //reads if switch is opened/closed 

bool execute = false; //triggers process to begin
bool dumped = false; //indicates when lever has dumped beans


void setup() {
  Serial.begin(9600);
  pinMode(sig, INPUT);
  pinMode(grind, OUTPUT);
  pinMode(contact, INPUT);
  digitalWrite(grind, LOW);
}

void loop() {
  if(digitalRead(8)==HIGH) {
    execute = true; 
  }
  //grinds when high signal is recieved 
  if(execute==true && digitalRead(contact)==HIGH) {
    digitalWrite(grind, HIGH);
  }
  //curs power when lever is dumping
  else if(execute==true && digitalRead(contact)==LOW) {
    digitalWrite(grind, LOW);
    dumped = true; 
  }
  //resets when lever goes back to original position 
  else if (dumped==true && digitalRead(contact)==HIGH) {
    execute = false;
    dumped = false; 
    digitalWrite(grind, LOW);
  }
}
