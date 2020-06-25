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
    initialise(); // initialise all the Kali components - must do this before anything else!
}

KaliRobot::KaliRobot(const KaliRobot& orig) {
}

KaliRobot::~KaliRobot() {
}

/*
    Initialises the Wiring Pi library and each component of KaliRobot is asked to do the same.

*/
void KaliRobot::initialise()
{
    wiringPiSetup(); // Initialise WiringPi

    // initialise all the different components
    wheels.initialise();
    camera.initialise();
    
    // give it a couple of seconds to work its way through
    delay(2000);
}
