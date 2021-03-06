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
#include "KaliRobot.h"

Logging* Logging::_instance = NULL;
string Logging::logFileName = string("kali.log");
LoggingLevel Logging::logLevel = LogDebug;

Logging::Logging() {
    logFile.open(logFileName, ios::out | ios::app);
}

Logging::Logging(const Logging& orig) {
    logFile.close();
}

Logging::~Logging() {
}

Logging* Logging::Instance() {
    if (_instance == NULL)
    {
        _instance = new Logging;
    }
    
    return _instance;
}

void Logging::log(string class_name, string method_name, string message, LoggingLevel level, bool output_to_speaker, bool output_to_screen)
{
    if (level != LogOff && level <= logLevel)
    {
        string logMessage = Logging::Instance()->currentDateTime() + " : " + class_name + "::" + method_name + " : " + message;

        // output to screen
        if (output_to_screen)
        {
            cout << logMessage << endl;
        }

        // output to speaker
        if (output_to_speaker)
        {
            KaliRobot* kali = KaliRobot::Instance();
            kali->speaker.say(message);
        }

        // output to log file
        logFile << logMessage << endl;

        logFile.flush();
    }
}

// shit code but a copy/paste from the interwebs
const string Logging::currentDateTime() {
    char buffer[26];
    char timestring[80];
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
    sprintf(timestring, "%s.%03d", buffer, millisec);

    return timestring;
}