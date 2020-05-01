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
#include "Logging.h"

Wheels::Wheels() {
    currentSpeed = 0;
}

Wheels::Wheels(const Wheels& orig) {
}

Wheels::~Wheels() {
}

/*
    Initialises the Wiring Pi library for each set of wheels.

*/
void Wheels::initialise()
{
    leftWheels.initialise();
    rightWheels.initialise();
}

/*
    Moves Kali Robot forward.
   
    It ramps up the speed to the specified speed, it holds that speed for the specified number of seconds,
    then ramps the speed down to a halt.

    @param speed - A speed from 0-100.
    @param seconds - How many seconds to move forward for. A value of 0 will start movement and not stop.
*/
void Wheels::moveForward(int speed, int seconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Moving forward with speed " + to_string(speed) + " for " + to_string(seconds) + " seconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Ramping up the speed");
    forwardRampUp(speed);
    
    if (seconds > 0)
    {
        // move forward for the specified time
        message = "Holding the speed for " + to_string(seconds) + " seconds.";
        kaliLog->log(typeid(this).name(), __FUNCTION__, message);
        delay(seconds * 1000);
        
        // now ramp down
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Ramping dpwn the speed to a halt");
        forwardRampDown(speed);
    }
}

/*
    Moves Kali Robot in reverse.
   
    It ramps up the speed to the specified speed, it holds that speed for the specified number of seconds,
    then ramps the speed down to a halt.

    @param speed - A speed from 0-100.
    @param seconds - How many seconds to move forward for. A value of 0 will start movement and not stop.
*/
void Wheels::moveReverse(int speed, int seconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Moving in reverse with speed " + to_string(speed) + " for " + to_string(seconds) + " seconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Ramping up the speed");
    reverseRampUp(speed);
    
    if (seconds > 0)
    {
        // reverse for the specified time
        message = "Holding the speed for " + to_string(seconds) + " seconds.";
        kaliLog->log(typeid(this).name(), __FUNCTION__, message);
        delay(seconds * 1000);
        
        // now ramp down
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Ramping dpwn the speed to a halt");
        reverseRampDown(speed);
    }
}

/*
    Ramps up the speed to the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::forwardRampUp(int speed)
{
    int rampIncrement = 1000 * speed / 50 / 10;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping up the speed to " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    // ramp up the speed in increments of 10% of the total speed
    for (int i = (speed / 10); i < speed; i += (speed / 10))
    {
        leftWheels.setForwardMotion(i);
        rightWheels.setForwardMotion(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    message = "Set the speed of both wheels to " + to_string(speed);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    leftWheels.setForwardMotion(speed);
    rightWheels.setForwardMotion(speed);
    
    currentSpeed = speed;
}

/*
    Ramps down the speed to a halt from the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::forwardRampDown(int speed)
{
    int rampIncrement = 1000 * speed / 50 / 10;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping down the speed from " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    // ramp down the speed in increments of 10% of the total speed
    for (int i = speed; i > 0; i -= (speed / 10))
    {
        leftWheels.setForwardMotion(i);
        rightWheels.setForwardMotion(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Set the speed of both wheels to 0 to come to a halt.");
    leftWheels.setForwardMotion(0);
    rightWheels.setForwardMotion(0);
    
    currentSpeed = 0;
}

/*
    Ramps up the reverse speed to the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::reverseRampUp(int speed)
{
    int rampIncrement = 1000 * speed / 50 / 10;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping up the speed to " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // ramp up the speed in increments of 10% of the total speed
    for (int i = (speed / 10); i < speed; i += (speed / 10))
    {
        leftWheels.setReverseMotion(i);
        rightWheels.setReverseMotion(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    message = "Set the speed of both wheels to " + to_string(speed);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    leftWheels.setReverseMotion(speed);
    rightWheels.setReverseMotion(speed);
    
    currentSpeed = -speed;
}

/*
    Ramps down the speed to a halt from the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::reverseRampDown(int speed)
{
    int rampIncrement = 1000 * speed / 50 / 10;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping down the speed from " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // ramp down the speed in increments of 10% of the total speed
    for (int i = speed; i > 0; i -= (speed / 10))
    {
        leftWheels.setReverseMotion(i);
        rightWheels.setReverseMotion(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Set the speed of both wheels to 0 to come to a halt.");
    leftWheels.setReverseMotion(0);
    rightWheels.setReverseMotion(0);
    
    currentSpeed = 0;
}

/*
    Brakes gently (ramps down in the forward or reverse direction).

*/
void Wheels::brakeSoft()
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Braking softly down from a speed of " + to_string(currentSpeed);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    if (currentSpeed > 0)
    {
        forwardRampDown(currentSpeed);
    }
    else if (currentSpeed < 0)
    {
        reverseRampDown(currentSpeed);
    }
}

/*
    Brakes abruptly - sets the forward or reverse direction motion to 0.

*/
void Wheels::brakeHard()
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Braking abruptly down from a speed of " + to_string(currentSpeed) ;
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);


    if (currentSpeed > 0)
    {
        // set the final speed accurately
        leftWheels.setForwardMotion(0);
        rightWheels.setForwardMotion(0);
    }
    else if (currentSpeed < 0)
    {
        // set the final speed accurately
        leftWheels.setReverseMotion(0);
        rightWheels.setReverseMotion(0);
    }
    
    currentSpeed = 0;
}

/*
    Twirls Kali Robot in the left direction (anticlockwise).

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to twirl for.
*/
void Wheels::twirlLeft(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Twirling left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // twirl according to the given wheel speed
    leftWheels.setReverseMotion(speed);
    rightWheels.setForwardMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue twirling for the specified time
        message = "Holding the twirl for " + to_string(milliseconds) + " milliseconds.";
        kaliLog->log(typeid(this).name(), __FUNCTION__, message);
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Stopping the twirling motion.");
        leftWheels.setReverseMotion(0);
        rightWheels.setForwardMotion(0);

        currentSpeed = 0;
    }
}

/*
    Twirls Kali Robot in the right direction (clockwise).

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to twirl for.
*/
void Wheels::twirlRight(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Twirling right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // twirl according to the given wheel speed
    leftWheels.setForwardMotion(speed);
    rightWheels.setReverseMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue twirling for the specified time
        message = "Holding the twirl for " + to_string(milliseconds) + " milliseconds.";
        kaliLog->log(typeid(this).name(), __FUNCTION__, message);
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Stopping the twirling motion.");
        leftWheels.setForwardMotion(0);
        rightWheels.setReverseMotion(0);

        currentSpeed = 0;
    }
}

/*
    Turns Kali Robot gently left.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnLeft(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    message = "Left wheel speed is " + to_string(speed / 5) + " and right wheel speed is " + to_string(speed);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // twirl according to the given wheel speed
    leftWheels.setForwardMotion(speed / 5);
    rightWheels.setForwardMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue turning for the specified time
        message = "Holding the turn for " + to_string(milliseconds) + " milliseconds.";
        delay(milliseconds);

        kaliLog->log(typeid(this).name(), __FUNCTION__, "Stopping the turn.");

        // stop twirling (wheel speed = 0)
        leftWheels.setForwardMotion(0);
        rightWheels.setForwardMotion(0);

        currentSpeed = 0;
    }
}

/*
    Turns Kali Robot gently right.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnRight(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    message = "Left wheel speed is " + to_string(speed) + " and right wheel speed is " + to_string(speed / 5);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // twirl according to the given wheel speed
    rightWheels.setForwardMotion(speed / 5);
    leftWheels.setForwardMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue turning for the specified time
        message = "Holding the turn for " + to_string(milliseconds) + " milliseconds.";
        delay(milliseconds);

        kaliLog->log(typeid(this).name(), __FUNCTION__, "Stopping the turn.");

        // stop twirling (wheel speed = 0)
        leftWheels.setForwardMotion(0);
        rightWheels.setForwardMotion(0);

        currentSpeed = 0;
    }
}

/*
    Turns Kali Robot aggressively left.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnHardLeft(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning hard left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    message = "Left wheel speed is " + to_string(speed / 15) + " and right wheel speed is " + to_string(speed);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // twirl according to the given wheel speed
    leftWheels.setReverseMotion(speed / 15);
    rightWheels.setForwardMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue turning for the specified time
        message = "Holding the turn for " + to_string(milliseconds) + " milliseconds.";
        delay(milliseconds);

        kaliLog->log(typeid(this).name(), __FUNCTION__, "Stopping the turn.");

        // stop twirling (wheel speed = 0)
        leftWheels.setForwardMotion(0);
        rightWheels.setForwardMotion(0);

        currentSpeed = 0;
    }
}

/*
    Turns Kali Robot aggressively right.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnHardRight(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning hard right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    message = "Left wheel speed is " + to_string(speed) + " and right wheel speed is " + to_string(speed / 15);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // twirl according to the given wheel speed
    rightWheels.setForwardMotion(speed / 15);
    leftWheels.setForwardMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue turning for the specified time
        message = "Holding the turn for " + to_string(milliseconds) + " milliseconds.";
        delay(milliseconds);

        kaliLog->log(typeid(this).name(), __FUNCTION__, "Stopping the turn.");

        // stop twirling (wheel speed = 0)
        leftWheels.setForwardMotion(0);
        rightWheels.setForwardMotion(0);

        currentSpeed = 0;
    }
}
