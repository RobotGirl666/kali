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

void Wheels::setForwardSpeed(int speed)
{
    leftWheels.setForwardMotion(speed);
    rightWheels.setForwardMotion(speed);
    
    currentSpeed = speed;
}

void Wheels::setReverseSpeed(int speed)
{
    leftWheels.setReverseMotion(speed);
    rightWheels.setReverseMotion(speed);
    
    currentSpeed = -speed;
}

/*
    Ramps up the speed to the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::forwardRampUp(int speed)
{
    int rampIncrement = speed / 2;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping up the speed to " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    // ramp up the speed in increments of 10% of the total speed
    for (int i = (speed / 10); i < speed; i += (speed / 10))
    {
        setForwardSpeed(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    message = "Set the speed of both wheels to " + to_string(speed);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    setForwardSpeed(speed);
}

/*
    Ramps down the speed to a halt from the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::forwardRampDown(int speed)
{
    int rampIncrement = speed / 2;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping down the speed from " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    // ramp down the speed in increments of 10% of the total speed
    for (int i = speed; i > 0; i -= (speed / 10))
    {
        setForwardSpeed(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Stop both wheel motors and come to a halt.");
    stop();
}

/*
    Ramps up the reverse speed to the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::reverseRampUp(int speed)
{
    int rampIncrement = speed / 2;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping up the speed to " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // ramp up the speed in increments of 10% of the total speed
    for (int i = (speed / 10); i < speed; i += (speed / 10))
    {
        setReverseSpeed(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    message = "Set the speed of both wheels to " + to_string(speed);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    setReverseSpeed(speed);
}

/*
    Ramps down the speed to a halt from the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::reverseRampDown(int speed)
{
    int rampIncrement = speed / 2;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping down the speed from " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // ramp down the speed in increments of 10% of the total speed
    for (int i = speed; i > 0; i -= (speed / 10))
    {
        setReverseSpeed(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Stop both wheel motors and come to a halt.");
    stop();
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
    Stops abruptly - sets the forward or reverse direction motion to 0.

*/
void Wheels::stop()
{
    Logging* kaliLog = Logging::Instance();

    kaliLog->log(typeid(this).name(), __FUNCTION__, "Stop both wheel motors and come to a halt.");
    leftWheels.stop();
    rightWheels.stop();
    
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
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Stop both wheel motors and come to a halt.");
        stop();
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
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Stop both wheel motors and come to a halt.");
        stop();
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
    
    turn((speed / TURN_FACTOR), speed, milliseconds);
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
    
    turn(speed, (speed / TURN_FACTOR), milliseconds);
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
    
    turn((speed / TURN_HARD_FACTOR), speed, milliseconds);
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
    
    turn(speed, (speed / TURN_HARD_FACTOR), milliseconds);
}

/*
    Turns Kali Robot gently left.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnLeftReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reverse turning left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    turnReverse((speed / TURN_FACTOR), speed, milliseconds);
}

/*
    Turns Kali Robot gently right.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnRightReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reverse turning right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    turnReverse(speed, (speed / TURN_FACTOR), milliseconds);
}

/*
    Turns Kali Robot aggressively left.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnHardLeftReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reverse turning hard left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    turnReverse((speed / TURN_HARD_FACTOR), speed, milliseconds);
}

/*
    Turns Kali Robot aggressively right.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnHardRightReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reverse turning hard right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    turnReverse(speed, (speed / TURN_HARD_FACTOR), milliseconds);
}

/*
    Internal (protected) method to turn kali left/right

    @param speedLeft - A speed from 0-100 for the left wheels.
    @param speedRight - A speed from 0-100 for the left wheels.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turn(int speedLeft, int speedRight, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning left wheels with left wheels speed " + to_string(speedLeft) + " and right wheels with speed " + to_string(speedRight) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // turn according to the given wheel speeds
    leftWheels.setForwardMotion(speedLeft);
    rightWheels.setForwardMotion(speedRight);
    if (speedLeft >= speedRight)
    {
        currentSpeed = speedLeft;
    }
    else
    {
        currentSpeed = speedRight;
    }

    if (milliseconds > 0)
    {
        // continue turning for the specified time
        message = "Holding the turn for " + to_string(milliseconds) + " milliseconds.";
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Stop both wheel motors and come to a halt.");
        stop();
    }
}

/*
    Internal (protected) method to turn kali left/right

    @param speedLeft - A speed from 0-100 for the left wheels.
    @param speedRight - A speed from 0-100 for the left wheels.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnReverse(int speedLeft, int speedRight, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reverse turning left wheels with left wheels speed " + to_string(speedLeft) + " and right wheels with speed " + to_string(speedRight) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // turn according to the given wheel speeds
    leftWheels.setReverseMotion(speedLeft);
    rightWheels.setReverseMotion(speedRight);
    if (speedLeft >= speedRight)
    {
        currentSpeed = speedLeft;
    }
    else
    {
        currentSpeed = speedRight;
    }

    if (milliseconds > 0)
    {
        // continue turning for the specified time
        message = "Holding the turn for " + to_string(milliseconds) + " milliseconds.";
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Stop both wheel motors and come to a halt.");
        stop();
    }
}
