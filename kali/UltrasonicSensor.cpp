/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UltrasonicSensor.cpp
 * Author: vangelis
 * 
 * Created on 26 April 2020, 7:38 pm
 */

#include <wiringPi.h>
#include <softPwm.h>

#include "Logging.h"
#include "UltrasonicSensor.h"
#include "MicroTimer.h"

UltrasonicSensor::UltrasonicSensor() {
    pinTrigger = 31; //Define the TrigPin connect to wiringPi port 31 of Raspberry pi
    pinEcho = 30; //Define the EchoPin connect to wiringPi port 30 of Raspberry pi
    
    // initialise the pservo direction
    dir = Up;
}

UltrasonicSensor::UltrasonicSensor(const UltrasonicSensor& orig) {
}

UltrasonicSensor::~UltrasonicSensor() {
}

/**
 * 
 *   Initialises the Wiring Pi library for each set of pins relating to the motor that drives these wheels (could be left or right set of wheels).
 *
 */
void UltrasonicSensor::initialise()
{
    horizontalServo.initialise(4);
}

void UltrasonicSensor::roam(int speed, int seconds)
{
    // first do a full sweep so we get a lay of the land
    fullSweep();
}

void UltrasonicSensor::fullSweep()
{
    Logging* kaliLog = Logging::Instance();
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Commencing ultrsonic sweep.");

    // re-initialise the position and movement variables
    dir = Up;
    
    for (int angle = 0; angle <= 180; angle += 10)
    {
        // set the servo to the specified angle
        horizontalServo.setPos(angle);
        
        // measure the distance and store in the array
        dists[angle / 10] = getDistance();

        string message = "Angle: " + to_string(angle) + " distance: " + to_string(dists[angle / 10]);
        kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    }
    
    // future distance measurements will sweep the opposite way
    dir = Down;
}

/**
 * 
 * Get the distance to the object in front of the sensor in mm
 * 
 * @param int limit - maximum distance (can't wait forever for horizon readings)
 *                    default is set to 10,000mm (10m)
 *                    time calculations assume speed of sound of 343 m/s which is true for air at STP
 * 
 * @return int - Nubmer of mm to object
 * 
 */
int UltrasonicSensor::getDistance(int limit)
{
    Logging* kaliLog = Logging::Instance();
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Commencing ultrsonic distance processing.", LogDebug);

    int distance = limit;
    MicroTimer mt;
    
    // time to get a pulse back from the limit distance in microseconds
    int limitTime = (limit * 2) * 1000 / 343;

    string message = "Limit: " + to_string(limit) + " limit time: " + to_string(limitTime);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message, LogDebug);
    
    // send a pulse of at least 15 microseconds
    digitalWrite(pinTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrigger, HIGH);
    mt.start(); // start the timer at the start of the pulse and finish once it comes back (leading edge)
    delayMicroseconds(15);
    digitalWrite(pinTrigger, LOW);
    
    // wait for pulse to come back
    while(!digitalRead(pinEcho) == 1)
    {
        if (mt.check() > limitTime)  // stop if exceeds maximum value
        {
            break;
        }
    }
    
    distance = mt.getCheck() * 343 / 2 / 1000; // distance in mm
    if (distance > limit)
    {
        distance = limit;
    }
    
    message = "Time for pulse to return: " + to_string(mt.getCheck()) + " distance: " + to_string(distance);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message, LogDebug);
    
    return distance;
}
