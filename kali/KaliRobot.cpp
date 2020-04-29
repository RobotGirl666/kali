/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KaliRobot.cpp
 * Author: vangelis
 * 
 * Created on 26 April 2020, 7:22 pm
 */

#include <wiringPi.h>
#include <softPwm.h>
#include <cstdlib>
#include <string>

#include "KaliRobot.h"
#include "Logging.h"

using namespace std;

KaliRobot::KaliRobot() {
}

KaliRobot::KaliRobot(const KaliRobot& orig) {
}

KaliRobot::~KaliRobot() {
}

void KaliRobot::moveForward(int speed, int seconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Moving forward with speed " + to_string(speed) + " for " + to_string(seconds) + " seconds.";
    kaliLog->log(message);
    
    wheels.moveForward(speed, seconds);
}

void KaliRobot::moveReverse(int speed, int seconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reversing with speed " + to_string(speed) + " for " + to_string(seconds) + " seconds.";
    kaliLog->log(message);

    wheels.moveReverse(speed, seconds);
}

void KaliRobot::remote()
{
    
}

void KaliRobot::party()
{
    
}