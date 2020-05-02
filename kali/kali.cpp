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
            [](unsigned char c){ return std::tolower(c); });
        if (input.compare("remote") == 0)
        {
            kali.remote();
        }
        else if (input.compare("forward") == 0)
        {
            if (checkNum(argv[1])) {
                int speed = atoi(argv[i+1]);
               // if RangeCheck(speed, 0, 100) {
                    
                //}
            }  
        }
            //if (checkNum(argv[i+2]))P
            // int time = atoi(argv[i+2]);
            //if RangeCheck(time, 0, 1000);
            
            if (i + 1 >= argc)
            {
                kali.moveForward(30, 3);
            }
            else
            {
                int speed = atoi(argv[i+1]);
                i++;
                if (i + 1 <= argc)
                {
                    int time = atoi(argv[i+1]);
                    i++;
                    kali.moveForward(speed, time);
                }
                else
                {
                    kali.moveForward(speed);
                }
            }
        }
        else if (input.compare("reverse") == 0)
        {
            if (i + 1 >= argc)
            {
                kali.moveReverse(30, 3);
            }
            else
            {
                int speed = atoi(argv[i+1]);
                i++;
                if (i + 1 <= argc)
                {
                    int time = atoi(argv[i+1]);
                    i++;
                    kali.moveReverse(speed, time);
                }
                else
                {
                    kali.moveReverse(speed);
                }
            }
        }
        else if (input.compare("twirlleft") == 0)
        {
            if (i + 1 >= argc)
            {
                kali.twirlLeft(30, 3000);
            }
            else
            {
                int speed = atoi(argv[i+1]);
                i++;
                if (i + 1 <= argc)
                {
                    int time = atoi(argv[i+1]) * 1000; // need to pass milliseconds to the twirl method
                    i++;
                    kali.twirlLeft(speed, time);
                }
                else
                {
                    kali.twirlLeft(speed);
                }
            }
        }
        else if (input.compare("twirlright") == 0)
        {
            if (i + 1 >= argc)
            {
                kali.twirlRight(30, 3000);
            }
            else
            {
                int speed = atoi(argv[i+1]);
                i++;
                if (i + 1 <= argc)
                {
                    int time = atoi(argv[i+1]) * 1000; // need to pass milliseconds to the twirl method
                    i++;
                    kali.twirlRight(speed, time);
                }
                else
                {
                    kali.twirlRight(speed);
                }
            }
        }
        
    
    
    
    
    
    
    // goodbye
    kaliLog->log("", __FUNCTION__, "Goodbye puny humans!");
    
    return 0;
}

