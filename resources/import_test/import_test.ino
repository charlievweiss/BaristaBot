#include <Test.h>

Test test('A');

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    test.printSomething();
}