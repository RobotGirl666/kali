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
#include <sys/time.h>
#include <tgmath.h>

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

void Logging::log(string message, string method, bool output_to_screen)
{
    string logMessage = Logging::Instance()->currentDateTime() + " : " + method + " : " + message;
    
    if (output_to_screen)
    {
        cout << logMessage << endl;
    }
    logFile << logMessage << endl;
}

// shit code but a copy/paste from the interwebs
const std::string Logging::currentDateTime() {
    char buffer[26];
    int millisec;
    struct tm* tm_info;
    struct timeval tv;

    gettimeofday(&tv, NULL);

    millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
    if (millisec>=1000) { // Allow for rounding up to nearest second
      millisec -=1000;
      tv.tv_sec++;
    }

    tm_info = localtime(&tv.tv_sec);

    strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", tm_info);
    printf("%s.%03d\n", buffer, millisec);

    return buffer;
}