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

#include "Logging.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Logging* kaliLog = Logging::Instance();
    
    string message("Kali Awakens! Bow to your machine overlord!");
    kaliLog->log(message);
    
    // do stuff here
    
    
    // goodbye
    message = "Goodbye puny humans!";
    kaliLog->log(message);
    
    return 0;
}

