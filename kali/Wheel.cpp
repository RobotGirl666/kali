/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wheel.cpp
 * Author: vangelis
 * 
 * Created on 26 April 2020, 7:29 pm
 */

#include <wiringPi.h>
#include <softPwm.h>

#include "Wheel.h"
#include "Logging.h"

Wheel::Wheel() {
}

Wheel::Wheel(const Wheel& orig) {
}

Wheel::~Wheel() {
}

/*
    Initialises the Wiring Pi library for each set of pins relating to the motor that drives these wheels (could be left or right set of wheels).

*/
void Wheel::initialise()
{
    //Initializethe motor drive IO as outputs
    pinMode(pinForwardMotors, OUTPUT);
    pinMode(pinReverseMotors, OUTPUT);

    //int softPwmCreate(int pin,int initialValue,int pwmRange);
    // initialise the motor speed range 0-255 (maximum bit output)
    softPwmCreate(pinMotorSpeed,0,255);
}

/*
    Moves Kali Robot forward or halt if speed is 0.
   
    Sets the motors that drives the wheels to the specified speed in the forward direction.

    @param speed - A speed from 0-100.
*/
void Wheel::setForwardMotion(int speed)
{
    Logging* kaliLog = Logging::Instance();
    
    speed = speed * 255 / 100;
    
    string message = "Motors moving forward with speed " + to_string(speed);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    digitalWrite(pinForwardMotors, HIGH);
    digitalWrite(pinReverseMotors, LOW);
    softPwmWrite(pinMotorSpeed, speed);
}


/*
    Moves Kali Robot in the reverse direction or halts her if speed is 0.
   
    Sets the motors that drives the wheels to the specified speed in the reverse direction.

    @param speed - A speed from 0-100.
*/
void Wheel::setReverseMotion(int speed)
{
    Logging* kaliLog = Logging::Instance();
    
    speed = speed * 255 / 100;
    
    string message = "Motors reversing with speed " + to_string(speed);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    digitalWrite(pinForwardMotors, LOW);
    digitalWrite(pinReverseMotors, HIGH);
    softPwmWrite(pinMotorSpeed, speed);
}
