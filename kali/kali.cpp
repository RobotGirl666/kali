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
            int speed = 30;
            int time = 2;
            if (Validation::checkNum(argv[i+1])) {
                speed = atoi(argv[i+1]);
                if (Validation::RangeCheck(speed, 0, 100)) {
                    if (Validation::checkNum(argv[i+2])){
                        time = atoi(argv[i+2]);
                        if (Validation::RangeCheck(time,0,10000)){
                        }
                    }
                }
            }  
            kali.moveForward(speed, time);
        }

        else if (input.compare("reverse") == 0)
        {
            int speed = 30;
            int time = 2;
            if (Validation::checkNum(argv[i+1])) {
                speed = atoi(argv[i+1]);
                if (Validation::RangeCheck(speed, 0, 100)) {
                    if (Validation::checkNum(argv[i+2])){
                        time = atoi(argv[i+2]);
                        if (Validation::RangeCheck(time,0,10000)){
                        }
                    }
                }
            }  
            kali.moveReverse(speed, time);
        }
            
        else if (input.compare("twirlleft") == 0)
        {
            int speed = 30;
            if (Validation::checkNum(argv[i+1])) {
                speed = atoi(argv[i+1]);
                if (Validation::RangeCheck(speed, 0, 100)) {
                }
            }  
           
            kali.twirlLeft(speed);
        }
        else if (input.compare("twirlright") == 0)
        {
            int speed = 30;
            if (Validation::checkNum(argv[i+1])) {
                speed = atoi(argv[i+1]);
                if (Validation::RangeCheck(speed, 0, 100)) {
                }
            }  
           
            kali.twirlRight(speed);
        }
    }
        
    
    
    
    
    
    
    // goodbye
    kaliLog->log("", __FUNCTION__, "Goodbye puny humans!");
    
    return 0;
}

