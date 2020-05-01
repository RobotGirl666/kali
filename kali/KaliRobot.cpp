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

void KaliRobot::initialise()
{
    wheels.initialise();
    
    // give it a couple of seconds to work its way through
    delay(2000);
}

void KaliRobot::moveForward(int speed, int seconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Moving forward with speed " + to_string(speed) + " for " + to_string(seconds) + " seconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    wheels.moveForward(speed, seconds);
}

void KaliRobot::moveReverse(int speed, int seconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reversing with speed " + to_string(speed) + " for " + to_string(seconds) + " seconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.moveReverse(speed, seconds);
}

void KaliRobot::brakeSoft()
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Braking gently";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.brakeSoft();
}

void KaliRobot::brakeHard()
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Braking suddenly";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.brakeHard();
}

void KaliRobot::twirlLeft(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Twirling left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.twirlLeft(speed, milliseconds);
}

void KaliRobot::twirlRight(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Twirling right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.twirlRight(speed, milliseconds);
}

void KaliRobot::turnLeft(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnLeft(speed, milliseconds);
}

void KaliRobot::turnRight(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnRight(speed, milliseconds);
}

void KaliRobot::turnHardLeft(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning hard left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnHardLeft(speed, milliseconds);
}

void KaliRobot::turnHardRight(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning hard right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnHardRight(speed, milliseconds);
}

void KaliRobot::remote()
{
    
}

void KaliRobot::party()
{
    
}