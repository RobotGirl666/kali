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

#include "Wheel.h"

class Wheels {
public:
    Wheels();
    Wheels(const Wheels& orig);
    virtual ~Wheels();
    
protected:
    Wheel frontRightWheel;
    Wheel frontLeftWheel;
    Wheel rearRightWheel;
    Wheel rearLeftWheel;
    
private:

};

#endif /* WHEELS_H */

