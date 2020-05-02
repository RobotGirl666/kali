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
        cout << "Value is out of bounds. Lol";
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