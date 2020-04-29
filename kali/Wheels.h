/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wheels.h
 * Author: vangelis
 *
 * Created on 26 April 2020, 7:31 pm
 */

#ifndef WHEELS_H
#define WHEELS_H

#include "LeftWheels.h"
#include "RightWheels.h"

class Wheels {
public:
    Wheels();
    Wheels(const Wheels& orig);
    virtual ~Wheels();
    
    // Wheel behaviours
    void moveForward(int speed, int seconds = 0);
    void moveReverse(int speed, int seconds = 0);
    
protected:
    LeftWheels leftWheels;
    RightWheels rightWheels;
    
    // Wheel behaviour helpers
    void forwardRampUp(int speed, int milliseconds = 0);
    void forwardRampDown(int speed, int milliseconds = 0);
    void reverseRampUp(int speed, int milliseconds = 0);
    void reverseRampDown(int speed, int milliseconds = 0);
    
private:
};

#endif /* WHEELS_H */

