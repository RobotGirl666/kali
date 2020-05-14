/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   validation.cpp
 * Author: ioanna
 * 
 * Created on 2 May 2020, 1:03 pm
 */

#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

#include <wiringPi.h>
#include <softPwm.h>
#include "validation.h"


Validation::Validation() {
}

Validation::Validation(const Validation& orig) {
}

Validation::~Validation() {
}

// Check if user input is within desired range. Return true if within range. 
bool Validation::RangeCheck(int val,int lowerBound, int upperBound) 
{
    if (val < lowerBound || val > upperBound)
    {
        return false;
    }
    else
        return true;
}

// check if user input is an integer number. 
bool Validation::checkNum(char num[]) {
    int test = 0;
    for (int i = 0; num[i] != '\0'; i++) 
    {
        test = isdigit(num[i]);
        if (test != 0 ) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}

int Validation::parseSpeedTime(int argc, char** argv, int i, int& speed, int& time, bool msec)
{
    int incr = 0;

    speed = 0;
    time = 0;
    int timeFactor = 1;
    if (msec)
    {
        timeFactor = 1000;
    }
    if ((i+1 < argc) && (Validation::checkNum(argv[i+1]))) {
        incr++;
        i++;
        speed = atoi(argv[i]);
        if (Validation::RangeCheck(speed, 0, 100)) {
            if (Validation::checkNum(argv[i+1])){
                incr++;
                i++;
                time = atoi(argv[i]);
                if (Validation::RangeCheck(time,0,10000)){
                }
            }
            else {
                time = 2 * timeFactor;
            }
        }
    }
    else {
        speed = 30;
        time = 2 * timeFactor;
    }
    
    return incr;
}

int Validation::parseAngle(int argc, char** argv, int i, int& angle)
{
    int incr = 0;
    
    angle = 90;
    if ((i+1 < argc) && (Validation::checkNum(argv[i+1]))) {
        incr++;
        i++;
        angle = atoi(argv[i]);
        if (!Validation::RangeCheck(angle, 0, 180)) {
            angle = 90;
        }
    }
    
    return incr;
}
