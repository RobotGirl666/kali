/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KaliRobot.h
 * Author: vangelis
 *
 * Created on 26 April 2020, 7:22 pm
 */

#ifndef KALIROBOT_H
#define KALIROBOT_H

#include "Wheels.h"
#include "Sensors.h"
#include "Buzzer.h"
#include "Camera.h"

class KaliRobot {
public:
    KaliRobot();
    KaliRobot(const KaliRobot& orig);
    virtual ~KaliRobot();
    
    // Kali's behaviours
    void moveForward(int speed, int seconds = 0);
    void moveReverse(int speed, int seconds = 0);
    void remote();
    void party();
    
protected:
    Wheels wheels;
    Sensors sensors;
    Buzzer buzzer;
    Camera camera;
    
private:
};

#endif /* KALIROBOT_H */

