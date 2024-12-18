#include <iostream>
#include "sensors.hpp"

int main(int argc, const char * argv[]) {
    TemperatureSensor* firstSensor = new TemperatureSensor(0);
    delete firstSensor;
    return 0;
}