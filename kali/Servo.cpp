/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Servo.cpp
 * Author: vangelis
 * 
 * Created on 8 May 2020, 5:25 pm
 */

#include <wiringPi.h>
#include <softPwm.h>

#include "Logging.h"
#include "Servo.h"

Servo::Servo() {
    // initialise variables
    servoPin = 0;
}

Servo::Servo(const Servo& orig) {
}

Servo::~Servo() {
}


/**
 * 
 *   Initialises the Wiring Pi library for each set of pins relating to the motor that drives these wheels (could be left or right set of wheels).
 *
 */
void Servo::initialise(int sp)
{
    servoPin = sp;
    pinMode(servoPin, OUTPUT);
}

/**
 * 
 * @brief         Set the position of the servo to the given angle. This will generate a series of pulses to the servo from 1-2 ms and a period of 20 ms as per servo specs.
 * 
 * @param         angle 0 - 180 degrees
 * 
 */
void Servo::setPos(int angle)
{
    Logging* kaliLog = Logging::Instance();

    // clip the angle to the allowed upper and lower limits
    if (angle < 0)
    {
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Servo position exceeds lower limit. Clipping to 0.");
        angle = 0;
    }
    else if (angle > 180)
    {
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Servo position exceede upper limit. Clipping to 180.");
        angle = 180;
    }
    
    int pulseWidth;                   //Define the pulse width variable
//    pulseWidth = angle * 1000 / 180 + 1000;  //Convert the Angle to 1000-2000 microseconds pulse width as per servo specs
    // The following line of code came with the Yahboom robot. The specs on the servo (which I looked up on the web) contradict the settings in the code below
    pulseWidth = (angle * 11) + 500;  //Convert the Angle to 500-2480 pulse width
    
    // send 16 pulses to make sure angle is set correctly by servo motor
    for (int i = 0; i < 16; i++)
    {
        digitalWrite(servoPin, HIGH);
        delayMicroseconds(pulseWidth);
        digitalWrite(servoPin, LOW);
        delay(20 - pulseWidth / 1000);     //Delay remaining time
    }
}
