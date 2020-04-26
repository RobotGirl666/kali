/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sensors.h
 * Author: vangelis
 *
 * Created on 26 April 2020, 7:37 pm
 */

#ifndef SENSORS_H
#define SENSORS_H

#include "InfraredSensor.h"
#include "UltrasonicSensor.h"

class Sensors {
public:
    Sensors();
    Sensors(const Sensors& orig);
    virtual ~Sensors();
    
protected:
    InfraredSensor infraredSensor;
    UltrasonicSensor ultrasonicSensor;
    
private:

};

#endif /* SENSORS_H */

