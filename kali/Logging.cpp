/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Logging.cpp
 * Author: vangelis
 * 
 * Created on 27 April 2020, 8:00 am
 */

#include <time.h>
 #include <iostream>

#include "Logging.h"

Logging* Logging::_instance = 0;
string Logging::logFileName = string("kali.log");

Logging::Logging() {
    logFile.open(logFileName, ios::out | ios::app);
}

Logging::Logging(const Logging& orig) {
}

Logging::~Logging() {
}

Logging* Logging::Instance() {
    if (_instance == 0)
    {
        _instance = new Logging;
    }
    
    return _instance;
}

void Logging::log(string& message, bool output_to_screen)
{
    string logMessage = Logging::Instance()->currentDateTime() + " : " + message;
    
    if (output_to_screen)
    {
        cout << logMessage << endl;
    }
    logFile << logMessage << endl;
}

// shit code but a copy/paste from the interwebs
const std::string Logging::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}