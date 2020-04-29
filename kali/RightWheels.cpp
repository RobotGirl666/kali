/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RightWheels.cpp
 * Author: vangelis
 * 
 * Created on 29 April 2020, 8:05 am
 */

#include <wiringPi.h>
#include <softPwm.h>

#include "RightWheels.h"

RightWheels::RightWheels() {
    pinForwardMotors = 24;
    pinReverseMotors = 25;
    pinMotorSpeed = 23;

    softPwmCreate(pinMotorSpeed,0,100);
}

RightWheels::RightWheels(const RightWheels& orig) {
}

RightWheels::~RightWheels() {
}

