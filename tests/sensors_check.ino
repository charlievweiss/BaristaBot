// Reads sensors and prints values to serial

int cup_level = A0;
int bean_level = A1;
int water_level = A2;

int bean_reading = 0;
int cup_reading = 0;
int water_reading = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(bean_level, INPUT);
    pinMode(water_level, INPUT);
    pinMode(cup_level, INPUT);
}

void read_sensors()
{
    bean_reading = analogRead(bean_level); //below 500
    cup_reading = analogRead(cup_level); //below 500
    water_reading = analogRead(water_level); //below 400
}

void print_readings()
{
    Serial.print("beans: "); Serial.print(bean_reading);
    Serial.print(" cups: "); Serial.print(cup_reading);
    Serial.print(" water: "); Serial.println(water_reading);
}

void loop()
{
    read_sensors();
    print_readings();
}