/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MicroTimer.h
 * Author: vangelis
 *
 * Created on 11 July 2020, 10:43 am
 */

#ifndef MICROTIMER_H
#define MICROTIMER_H

#include <sys/time.h>

class MicroTimer {
public:
    MicroTimer();
    MicroTimer(const MicroTimer& orig);
    virtual ~MicroTimer();
    void start();
    int check();
    int checkLast();
    int getCheck();
protected:
    struct timeval timeValue;
    int startTime;
    int checkTime;
private:

};

#endif /* MICROTIMER_H */

