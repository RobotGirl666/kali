/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   kali.cpp
 * Author: vangelis
 *
 * Created on 26 April 2020, 7:52 am
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>

#include "Logging.h"
#include "KaliRobot.h"
#include "validation.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Logging* kaliLog = Logging::Instance();
    // try catch everything - this will make kali a little more robust
    try {
        //start
        kaliLog->log("", __FUNCTION__, "Kali Awakens! Bow to your machine overlord!");

        // do stuff here (BE MORE SPECIFIC PLSSS DAD)
        KaliRobot kali;  // create the container class - overall robot
        kali.initialise(); // initialise all the Kali components - must do this before anything else!

        // switch statement 
        for(int i = 1; i < argc; i++)
        {
            string input = argv[i];
            transform(input.begin(), input.end(), input.begin(),
                [](unsigned char c){ return std::tolower(c); });  //wtf is this?
            if (input.compare("remote") == 0)
            {
                kali.remote();
            }
            else if (input.compare("forward") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 2;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2;
                }
                kali.moveForward(speed, time);
            }

            else if (input.compare("reverse") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 2;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2;
                }
                kali.moveReverse(speed, time);
            }

            else if (input.compare("twirlleft") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 1000;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2000;
                }
                kali.twirlLeft(speed, time);
            }

            else if (input.compare("twirlright") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 1000;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2000;
                }
                kali.twirlRight(speed, time);  //add in time
            }

            else if (input.compare("turnleft") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 2000;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2000;
                }
                kali.turnLeft(speed, time);
            }

            else if (input.compare("turnright") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 2000;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2000;
                }
                kali.turnRight(speed, time);
            }

            else if (input.compare("turnhardleft") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 2000;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2000;
                }
                kali.turnHardLeft(speed, time);
            }

            else if (input.compare("turnhardright") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 2000;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2000;
                }
                kali.turnHardRight(speed, time);
            }

            else if (input.compare("turnleftreverse") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 2000;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2000;
                }
                kali.turnLeftReverse(speed, time);
            }

            else if (input.compare("turnrightreverse") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 2000;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2000;
                }
                kali.turnRightReverse(speed, time);
            }

            else if (input.compare("turnhardleftreverse") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 2000;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2000;
                }
                kali.turnHardLeftReverse(speed, time);
            }

            else if (input.compare("turnhardrightreverse") == 0)
            {
                int speed = 0;
                int time = 0;
                if ((i+1<argc)&&(Validation::checkNum(argv[i+1]))) {
                    speed = atoi(argv[i+1]);
                    if (Validation::RangeCheck(speed, 0, 100)) {
                        if (Validation::checkNum(argv[i+2])){
                            time = atoi(argv[i+2]);
                            if (Validation::RangeCheck(time,0,10000)){
                            }
                        }
                        else {
                            time = 2000;
                        }
                    }
                }
                else {
                    speed = 30;
                    time = 2000;
                }
                kali.turnHardRightReverse(speed, time);
            }

        }
      // goodbye
        kaliLog->log("", __FUNCTION__, "Goodbye puny humans!");
    }
    catch (const std::exception& ex) {
        kaliLog->log("", __FUNCTION__, ex.what());
    }
    catch (...) {
        // Just log that there was an issue
        kaliLog->log("", __FUNCTION__, "Unknow exception thrown!");
    }
    
    return 0;
}

