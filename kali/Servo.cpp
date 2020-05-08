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

#include "Servo.h"

Servo::Servo() {
    // initialise variables
    servoPin = 0;
}

Servo::Servo(const Servo& orig) {
}

Servo::~Servo() {
}

    
void Servo::initialise(int sp)
{
    servoPin = sp;
    pinMode(servoPin, OUTPUT);
}

/**
* Function       setPos
* @brief         Define a pulse function to generate the PWM value in the analog mode. 
*                The base pulse is 20ms, 
*                and the high level of the pulse is controlled at 0-180 degrees in 0.5-2.5ms.
* @param         angle
*/
void Servo::setPos(int angle)
{
    int pulseWidth;                   //Define the pulse width variable
    pulseWidth = (angle * 11) + 500;  //Convert the Angle to 500-2480 pulse width
    digitalWrite(servoPin, HIGH);      
    delayMicroseconds(pulseWidth);     
    digitalWrite(servoPin, LOW);       
    delay(20 - pulseWidth / 1000);     //Delay remaining time 
}
