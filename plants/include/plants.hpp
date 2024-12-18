//
//  plants.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 18/12/24.
//

#ifndef plants_hpp
#define plants_hpp

#include "globals.hpp"
#include "sensors.hpp"
#include "workers.hpp"

class Plant
{
private:
    const std::string name;
    const int plantNumber;
    const int lowestSensValue;
    const int highstSensValue;
    std::vector<Sensor*> attachedSensors;
    std::vector<Worker*> attachedWorkers;
    std::map<int, int> devicesRelations;

};

#endif /* plants_hpp */
