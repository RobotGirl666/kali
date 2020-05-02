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

#include "Logging.h"
#include "KaliRobot.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Logging* kaliLog = Logging::Instance();
    //start
    string message("Kali Awakens! Bow to your machine overlord!");
    kaliLog->log(message);
    
    // do stuff here (BE MORE SPECIFIC PLSSS DAD)
    KaliRobot kali;  // create the container class - overall robot
    kali.moveForward(30, 3); 
    
    // switch statement 
    cout << "What is your command? Choose from the following: remote, movement," << endl;
    for(int i = 1; i < argc; i++)
    {      
        string input = argv[i];
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
            // int time = atoi(arv[i+2]);
            //if RangeCheck(time, 0, 1000);
            
            //kali.moveForward();
        }
        
    
    
    
    
    
    
    // goodbye
    message = "Goodbye puny humans!";
    kaliLog->log(message);
    
    return 0;
}

