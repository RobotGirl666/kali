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
    int currentSpeed;
    
    // Wheel behaviour helpers
    void forwardRampUp(int speed);
    void forwardRampDown(int speed);
    void reverseRampUp(int speed);
    void reverseRampDown(int speed);
    void brakeSoft();
    void brakeHard();
    
private:
};

#endif /* WHEELS_H */

