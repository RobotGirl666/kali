/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wheels.cpp
 * Author: vangelis
 * 
 * Created on 26 April 2020, 7:31 pm
 */

#include <wiringPi.h>
#include <softPwm.h>

#include "Wheels.h"

Wheels::Wheels() {
    currentSpeed = 0;
}

Wheels::Wheels(const Wheels& orig) {
}

Wheels::~Wheels() {
}

void Wheels::initialise()
{
    leftWheels.initialise();
    rightWheels.initialise();
}

void Wheels::moveForward(int speed, int seconds)
{
    forwardRampUp(speed);
    
    if (seconds > 0)
    {
        // move forward for the specified time
        delay(seconds * 1000);
        
        // now ramp down
        forwardRampDown(speed);
    }
}

void Wheels::moveReverse(int speed, int seconds)
{
    reverseRampUp(speed);
    
    if (seconds > 0)
    {
        // reverse for the specified time
        delay(seconds * 1000);
        
        // now ramp down
        reverseRampDown(speed);
    }
}

void Wheels::forwardRampUp(int speed)
{
    int rampIncrement = 1000 * speed / 50 / 10;
    
    // ramp up the speed in increments of 10% of the total speed
    for (int i = (speed / 10); i < speed; i += (speed / 10))
    {
        leftWheels.setForwardMotion(i);
        rightWheels.setForwardMotion(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    leftWheels.setForwardMotion(speed);
    rightWheels.setForwardMotion(speed);
    
    currentSpeed = speed;
}

void Wheels::forwardRampDown(int speed)
{
    int rampIncrement = 1000 * speed / 50 / 10;
    
    // ramp down the speed in increments of 10% of the total speed
    for (int i = speed; i > 0; i -= (speed / 10))
    {
        leftWheels.setForwardMotion(i);
        rightWheels.setForwardMotion(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    leftWheels.setForwardMotion(0);
    rightWheels.setForwardMotion(0);
    
    currentSpeed = 0;
}

void Wheels::reverseRampUp(int speed)
{
    int rampIncrement = 1000 * speed / 50 / 10;

    // ramp up the speed in increments of 10% of the total speed
    for (int i = (speed / 10); i < speed; i += (speed / 10))
    {
        leftWheels.setReverseMotion(i);
        rightWheels.setReverseMotion(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    leftWheels.setReverseMotion(speed);
    rightWheels.setReverseMotion(speed);
    
    currentSpeed = -speed;
}

void Wheels::reverseRampDown(int speed)
{
    int rampIncrement = 1000 * speed / 50 / 10;

    // ramp down the speed in increments of 10% of the total speed
    for (int i = speed; i > 0; i -= (speed / 10))
    {
        leftWheels.setReverseMotion(i);
        rightWheels.setReverseMotion(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    leftWheels.setReverseMotion(0);
    rightWheels.setReverseMotion(0);
    
    currentSpeed = 0;
}

void Wheels::brakeSoft()
{
    if (currentSpeed > 0)
    {
        forwardRampDown(currentSpeed);
    }
    else if (currentSpeed < 0)
    {
        reverseRampDown(currentSpeed);
    }
}

void Wheels::brakeHard()
{
    // set the final speed accurately
    leftWheels.setForwardMotion(0);
    rightWheels.setForwardMotion(0);
    
    currentSpeed = 0;
}

void Wheels::twirlLeft(int speed, int milliseconds)
{
    // twirl according to the given wheel speed
    leftWheels.setReverseMotion(speed);
    rightWheels.setForwardMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue twirling for the specified time
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        leftWheels.setForwardMotion(0);
        rightWheels.setForwardMotion(0);

        currentSpeed = 0;
    }
}

void Wheels::twirlRight(int speed, int milliseconds)
{
    // twirl according to the given wheel speed
    leftWheels.setForwardMotion(speed);
    rightWheels.setReverseMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue twirling for the specified time
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        leftWheels.setForwardMotion(0);
        rightWheels.setForwardMotion(0);

        currentSpeed = 0;
    }
}

void Wheels::turnLeft(int speed, int milliseconds)
{
    // twirl according to the given wheel speed
    leftWheels.setReverseMotion(speed / 5);
    rightWheels.setForwardMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue twirling for the specified time
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        leftWheels.setForwardMotion(0);
        rightWheels.setForwardMotion(0);

        currentSpeed = 0;
    }
}

void Wheels::turnRight(int speed, int milliseconds)
{
    // twirl according to the given wheel speed
    rightWheels.setReverseMotion(speed / 5);
    leftWheels.setForwardMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue twirling for the specified time
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        leftWheels.setForwardMotion(0);
        rightWheels.setForwardMotion(0);

        currentSpeed = 0;
    }
}

void Wheels::turnHardLeft(int speed, int milliseconds)
{
    // twirl according to the given wheel speed
    leftWheels.setReverseMotion(speed / 15);
    rightWheels.setForwardMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue twirling for the specified time
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        leftWheels.setForwardMotion(0);
        rightWheels.setForwardMotion(0);

        currentSpeed = 0;
    }
}

void Wheels::turnHardRight(int speed, int milliseconds)
{
    // twirl according to the given wheel speed
    rightWheels.setReverseMotion(speed / 15);
    leftWheels.setForwardMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue twirling for the specified time
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        leftWheels.setForwardMotion(0);
        rightWheels.setForwardMotion(0);

        currentSpeed = 0;
    }
}
