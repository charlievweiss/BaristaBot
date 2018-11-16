int sig_pin = 8; //signal to begin grinding process
int grind = 9; //powers motor to grind beans
int contact = 10; //reads if switch is opened/closed 
long start_time;
long current_time;
//long grind_time = 143000;  // time for 17g
long grind_time = 5000;

bool complete = false; //triggers process to begin
bool dumped = false; //indicates when lever has dumped beans
bool set_timer = false;
bool sig = false;

void setup() {
  Serial.begin(9600);
  pinMode(sig_pin, INPUT);
  pinMode(grind, OUTPUT);
  pinMode(contact, INPUT);
  digitalWrite(grind, LOW);
//  start_time = millis();
}

void grinding(){
    current_time = millis();
    Serial.println(current_time - start_time);
    
    if (current_time-start_time < grind_time){
      digitalWrite(grind,HIGH);
      Serial.println("grinding");
    }
    if (current_time-start_time >= grind_time){
      digitalWrite(grind,LOW);
      complete = true;
      }   
    }
  
void reset(){
  sig = false;
  set_timer = false;
  complete = false;  
  }

void loop() {
  Serial.println(complete);
  if (digitalRead(sig_pin) == HIGH){
    sig = true;
    }
  if (sig == true && complete==false) {
    if (set_timer == false){
      // The first time that the signal pin is high, this code will run once  
      // to record the current time, then it will not run again.
      start_time = millis();
      set_timer = true;
      }
    grinding();
  }
  if (complete==true){
    Serial.println("Ready to receive new HIGH");
    reset();
    }
  else {
    digitalWrite(grind,LOW);
    }
}
