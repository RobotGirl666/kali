/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Servo.h
 * Author: vangelis
 *
 * Created on 8 May 2020, 5:25 pm
 */

#ifndef SERVO_H
#define SERVO_H

class Servo {
public:
    Servo();
    Servo(const Servo& orig);
    virtual ~Servo();
    
    void initialise(int sp);
    void setPos(int angle);
    
protected:
    int servoPin;
private:

};

#endif /* SERVO_H */

