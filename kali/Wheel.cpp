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

Wheel::Wheel() {
}

Wheel::Wheel(const Wheel& orig) {
}

Wheel::~Wheel() {
}

void Wheel::setForwardMotion(int speed)
{
    digitalWrite(pinForwardMotors, HIGH);   
    digitalWrite(pinReverseMotors, LOW);  
    softPwmWrite(pinMotorSpeed, speed);   
}


void Wheel::setReverseMotion(int speed)
{
    digitalWrite(pinForwardMotors, LOW);   
    digitalWrite(pinReverseMotors, HIGH);  
    softPwmWrite(pinMotorSpeed, speed);   
}
