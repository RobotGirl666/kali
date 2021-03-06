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
#include "Buzzer.h"
#include "Camera.h"
#include "Speaker.h"
#include "Remote.h"
#include "InfraredSensor.h"
#include "UltrasonicSensor.h"
#include "Eliza.h"

class KaliRobot {
public:
    KaliRobot();
    KaliRobot(const KaliRobot& orig);
    virtual ~KaliRobot();
    
    // singleton pattern
    static KaliRobot* Instance();
    
    // Kali's behaviours
    // initialisation
    void initialise();
    
    // components of the robot
    Wheels wheels;
    Buzzer buzzer;
    Camera camera;
    Speaker speaker;
    Remote remote;
    InfraredSensor infraredSensor;
    UltrasonicSensor ultrasonicSensor;
    
    // abstract robot components
    MB::Eliza eliza; // psychologist
    
private:
    static KaliRobot* _instance;
};

#endif /* KALIROBOT_H */

