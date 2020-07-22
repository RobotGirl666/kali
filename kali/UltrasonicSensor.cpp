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
#include <stdlib.h>

#include "Logging.h"
#include "UltrasonicSensor.h"
#include "MicroTimer.h"
#include "KaliRobot.h"

UltrasonicSensor::UltrasonicSensor() {
    pinTrigger = 31; //Define the pinTrigger connect to wiringPi port 31 of Raspberry pi
    pinEcho = 30; //Define the EchoPin connect to wiringPi port 30 of Raspberry pi
    
    // initialise the pservo direction
    dirSweep = Up;
    
    // initialise sweep range 0-180 degrees
    setSweepRange(0,180);
    
    // set minimum distance to 100mm
    distMin = 100;
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
    // initialise ultrasonic pins
    pinMode(pinTrigger, OUTPUT);
    pinMode(pinEcho, INPUT);
    
    // initialise servo
    horizontalServo.initialise(4);
}

void UltrasonicSensor::roam(int speed, int seconds)
{
    Logging* kaliLog = Logging::Instance();
    KaliRobot* kali = KaliRobot::Instance();
    
    // first do a full sweep so we get a lay of the land
    setSweepRange(30, 150); // sweep from 30-150 degrees
    fullSweep();
    return;
    
    // roam for the specified time (seconds)
    MicroTimer mt;
    mt.start();
    while (mt.check() < seconds * 1000000)
    {
        // work out what the best direction to move kali based on the ultrasonic information we obtained in the sweep
        int heading = calcBestDirection();

        string message = "Heading: " + to_string(heading);
        kaliLog->log(typeid(this).name(), __FUNCTION__, message);

        if (heading == 90)
        {
            kali->wheels.setForwardSpeed(speed);
            sweepNext();
        }
        else if (heading > 0)
        {
            // deviation from the current front face
            int deviation = (heading - 90) / 10;
            
            // turn based on deviation from straight
            float turnAdjustment = abs(deviation) / 9;
            if (deviation > 0)
            {
                message = "Turning right with adjustment: " + to_string(turnAdjustment);
                kaliLog->log(typeid(this).name(), __FUNCTION__, message);

                kali->wheels.turnRight(speed, 0, turnAdjustment);
            }
            else if (deviation < 0)
            {
                message = "Turning left with adjustment: " + to_string(turnAdjustment);
                kaliLog->log(typeid(this).name(), __FUNCTION__, message);

                kali->wheels.turnLeft(speed, 0, turnAdjustment);
            }
            
            sweepNext();
        }
        else
        {
            // kali has come to a cul-de-sac - she needs to turn around and re-sweep the area
            if (rand() % 2)
            {
                kali->wheels.twirlLeft(speed, 300);
            }
            else
            {
                kali->wheels.twirlRight(speed, 300);
            }
            fullSweep();
        }
    }
    
    // stop kali at the end of the roam
    kali->wheels.forwardRampDown(speed);
    kali->wheels.stop();
}

void UltrasonicSensor::fullSweep()
{
    Logging* kaliLog = Logging::Instance();
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Commencing full ultrsonic sweep.");

    // re-initialise the position and movement variables
    dirSweep = Up;
    
    for (int angle = 0; angle <= 180; angle += 10)
    {
        if (angle >= sweepMin && angle <= sweepMax)
        {
            // set the servo to the specified angle
            horizontalServo.setPos(angle);

            // measure the distance and store in the array
            dists[angle / 10] = getDistance();

            string message = "Angle: " + to_string(angle) + " distance: " + to_string(dists[angle / 10]);
            kaliLog->log(typeid(this).name(), __FUNCTION__, message);
        }
        else
        {
            // everything outside of the sweep range is set to 0
            dists[angle / 10] = 0;
        }
    }
    
    // future distance measurements will sweep the opposite way
    angleSweep = sweepMax;
    dirSweep = Down;
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
    int distance = limit;
    MicroTimer mt;
    
    // time to get a pulse back from the limit distance in microseconds
    long limitTime = (limit * 2) * 1000 / 343;
    
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
        if (mt.check() >= limitTime)  // stop if exceeds maximum value
        {
            break;
        }
    }
    
    if (mt.getCheck() < limitTime)
    {
        mt.start(); // start timing the length of the echo pulse which will be the distance in microsectonds

        // now wait for the pulse to finish and time it
        while(!digitalRead(pinEcho) == 0)
        {
            if (mt.check() >= limitTime)  // stop if exceeds maximum value
            {
                break;
            }
        }
        distance = mt.getCheck() * 343 / 2 / 1000; // distance in mm

        // clean it up in case it is a few microseconds over
        if (distance > limit)
        {
            distance = limit;
        }
    }

    return distance;
}

void UltrasonicSensor::setSweepRange(int min, int max)
{
    sweepMin = min;
    sweepMax = max;
}

int UltrasonicSensor::calcBestDirection()
{
    int bestDir = -1;
    int distMax = 0;
    
    for (int dir = sweepMin; dir <= sweepMax; dir += 10)
    {
        if (dists[dir / 10] > distMax and dists[dir / 10] > distMin)
        {
            bestDir = dir;
            distMax = dists[dir / 10];
        }
    }
    
    return bestDir;
}

void UltrasonicSensor::sweepNext()
{
    Logging* kaliLog = Logging::Instance();

    if (dirSweep == Up)
    {
        angleSweep += 10;
    }
    else
    {
        angleSweep -= 10;
    }

    // set the servo to the specified angle
    horizontalServo.setPos(angleSweep);

    // measure the distance and store in the array
    dists[angleSweep / 10] = getDistance();

    string message = "Angle: " + to_string(angleSweep) + " distance: " + to_string(dists[angleSweep / 10]);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    if (angleSweep == sweepMin)
    {
        dirSweep = Up;
    }
    else if (angleSweep == sweepMax)
    {
        dirSweep = Down;
    }
}