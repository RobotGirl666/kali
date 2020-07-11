/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MicroTimer.cpp
 * Author: vangelis
 * 
 * Created on 11 July 2020, 10:43 am
 */

#include <stdio.h>

#include "MicroTimer.h"
#include "Logging.h"

MicroTimer::MicroTimer() {
    start();
}

MicroTimer::MicroTimer(const MicroTimer& orig) {
}

MicroTimer::~MicroTimer() {
}

/**
 * 
 * Start the timer
 * 
 */
void MicroTimer::start()
{
    Logging* kaliLog = Logging::Instance();
    gettimeofday(&timeValue, NULL); // get the current time
    startTime = timeValue.tv_sec * 1000000 + timeValue.tv_usec;
    checkTime = startTime;
    string message = "sec: " + to_string(timeValue.tv_sec) + " usec: " + to_string(timeValue.tv_usec);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message, LogDebug);
    message = "startTime: " + to_string(startTime) + " checkTime: " + to_string(checkTime);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message, LogDebug);
}

/**
 * 
 * Return the number of microseconds since the timer was started
 * 
 * @return int microseconds
 * 
 */
int MicroTimer::check()
{
    Logging* kaliLog = Logging::Instance();
    gettimeofday(&timeValue, NULL); // get the current time
    checkTime = timeValue.tv_sec * 1000000 + timeValue.tv_usec;
    string message = "sec: " + to_string(timeValue.tv_sec) + " usec: " + to_string(timeValue.tv_usec);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message, LogDebug);
    message = "startTime: " + to_string(startTime) + " checkTime: " + to_string(checkTime) + " diff: " + to_string(checkTime - startTime);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message, LogDebug);
    
    return (checkTime - startTime);
}

/**
 * 
 * Return the number of microseconds since the timer was last checked
 * 
 * @return int microseconds
 * 
 */
int MicroTimer::checkLast()
{
    int prevCheckTime = checkTime;
    check();
    
    return (checkTime - prevCheckTime);
}

/**
 * 
 * Returns the time of the last check without updating check timer
 * 
 * @return int microseconds
 * 
 */
int MicroTimer::getCheck()
{
    return (checkTime - startTime);
}
