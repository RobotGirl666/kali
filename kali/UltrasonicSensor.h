/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UltrasonicSensor.h
 * Author: vangelis
 *
 * Created on 26 April 2020, 7:38 pm
 */

#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include "Servo.h"

enum SweepDir { Up, Down };

class UltrasonicSensor {
public:
    UltrasonicSensor();
    UltrasonicSensor(const UltrasonicSensor& orig);
    virtual ~UltrasonicSensor();

    void initialise();
    void roam(int speed = 20, int seconds = 30);
    void setSweepRange(int min, int max);
    int calcBestDirection();

protected:
    // Pin assignments for the ultrasonic sensors
    int pinTrigger;
    int pinEcho;
    
    // servo that drives the ultrasonic sensor direction
    Servo horizontalServo;
    
    // servo direction
    SweepDir dir;

    // sweep range
    int sweepMin;
    int sweepMax;
    
    // don't go closer than this to an object
    int distMin;
    
    // distances
    int dists[19];
    
    void fullSweep(); // Do a full sweep of the forward area
    int getDistance(int limit = 10000); // get the distance to the object the sensor is pointing to

private:

};

#endif /* ULTRASONICSENSOR_H */

