/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   validation.h
 * Author: ioanna
 *
 * Created on 2 May 2020, 1:03 pm
 */

#ifndef VALIDATION_H
#define VALIDATION_H

class Validation {
public:
    Validation();
    Validation(const Validation& orig);
    virtual ~Validation();
    
    //validation functions
    static bool RangeCheck(int val,int lowerBound, int upperBound);
    static bool checkNum(char num[]);
    static int parseSpeedTime(int argc, char** argv, int i, int& speed, int& time, bool msec = false);
    static int parseAngle(int argc, char** argv, int i, int& angle);


private:

};

#endif /* VALIDATION_H */

