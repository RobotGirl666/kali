/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wheel.h
 * Author: vangelis
 *
 * Created on 26 April 2020, 7:29 pm
 */

#ifndef WHEEL_H
#define WHEEL_H

class Wheel {
public:
    Wheel();
    Wheel(const Wheel& orig);
    virtual ~Wheel();

protected:
    // Pin assignments for this/these wheel(s) - these will be set by the derived classes as this class does not know
    // whether this/these wheel(s) is/are left or right
    int pinForwardMotors = 0;
    int pinReverseMotors = 0;
    int pinMotorSpeed = 0;
    
    // implementation of wheel behaviours - basic pinouts
    void setForwardMotion(int speed);
    void setReverseMotion(int speed);

private:

};

#endif /* WHEEL_H */

