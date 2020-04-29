/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wheels.cpp
 * Author: vangelis
 * 
 * Created on 26 April 2020, 7:31 pm
 */

#include "Wheels.h"

Wheels::Wheels() {
}

Wheels::Wheels(const Wheels& orig) {
}

Wheels::~Wheels() {
}

void Wheels::moveForward(int speed, int seconds)
{
    int rampTime = 1000 * speed / 50;
    forwardRampUp(speed, rampTime);
    
    if (seconds > 0)
    {
        
    }
}

void Wheels::moveReverse(int speed, int seconds)
{
    
}

void Wheels::forwardRampUp(int speed, int milliseconds)
{
    
}

void Wheels::forwardRampDown(int speed, int milliseconds)
{
    
}

void Wheels::reverseRampUp(int speed, int milliseconds)
{
    
}

void Wheels::reverseRampDown(int speed, int milliseconds)
{
    
}