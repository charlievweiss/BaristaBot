int signalpin = 8;
int valve = 10;
int pour_time = 10000; //5 seconds
bool go = false;
bool complete = false;
long start_time = millis();
long current_time;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(valve,OUTPUT);

}

void run()  {
  current_time = millis();
  if(current_time-start_time>=(pour_time)) {
    go = false;
    complete = true;
    digitalWrite(valve, LOW);
  }
}

void loop() {
  Serial.println(go);
  
  if ((digitalRead(signalpin)==1) && (complete == 0)){
    go = true;
    digitalWrite(valve,HIGH);
    Serial.print("pouring");
    }
  else if ((digitalRead(signalpin)==1) && (complete == 1)) {
    go = false;
    Serial.print("finished");
    }
  if (digitalRead(signalpin)==0){
    digitalWrite(valve,LOW);
    Serial.print("waiting");
    }
  if (go == 1){
    run();
    }
}
