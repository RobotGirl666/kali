/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LeftWheels.cpp
 * Author: vangelis
 * 
 * Created on 29 April 2020, 8:05 am
 */

#include <wiringPi.h>
#include <softPwm.h>

#include "LeftWheels.h"

LeftWheels::LeftWheels() {
    pinForwardMotors = 28;
    pinReverseMotors = 29;
    pinMotorSpeed = 27;

    softPwmCreate(pinMotorSpeed,0,100); 
}

LeftWheels::LeftWheels(const LeftWheels& orig) {
}

LeftWheels::~LeftWheels() {
}

