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

/**
    Initialises the Wiring Pi library for each set of wheels.

*/
void Wheels::initialise()
{
    leftWheels.initialise();
    rightWheels.initialise();
}

/**
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
    kaliLog->logp1(message);
    
    kaliLog->logp1("Ramping up the speed");
    forwardRampUp(speed);
    
    if (seconds > 0)
    {
        // move forward for the specified time
        message = "Holding the speed for " + to_string(seconds) + " seconds.";
        kaliLog->logp1(message);
        delay(seconds * 1000);
        
        // now ramp down
        kaliLog->logp1("Ramping dpwn the speed to a halt");
        forwardRampDown(speed);
    }
}

/**
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
    kaliLog->logp1(message);
    
    kaliLog->logp1("Ramping up the speed");
    reverseRampUp(speed);
    
    if (seconds > 0)
    {
        // reverse for the specified time
        message = "Holding the speed for " + to_string(seconds) + " seconds.";
        kaliLog->logp1(message);
        delay(seconds * 1000);
        
        // now ramp down
        kaliLog->logp1("Ramping dpwn the speed to a halt");
        reverseRampDown(speed);
    }
}

/**
    Sets Kali's forward speed to the given speed.

    @param speed - A speed from 0-100.

*/
void Wheels::setForwardSpeed(int speed)
{
    if (speed == 0)
    {
        stop();
    }
    else
    {
        leftWheels.setForwardMotion(speed);
        rightWheels.setForwardMotion(speed);
    }
    
    currentSpeed = speed;
}

/**
    Sets Kali's reverse speed to the given speed.

    @param speed - A speed from 0-100.

*/
void Wheels::setReverseSpeed(int speed)
{
    if (speed == 0)
    {
        stop();
    }
    else
    {
        leftWheels.setReverseMotion(speed);
        rightWheels.setReverseMotion(speed);
    }
    
    currentSpeed = -speed;
}

/**
    Ramps up the speed to the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::forwardRampUp(int speed)
{
    int rampIncrement = speed / 2;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping up the speed to " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->logp1(message);
    
    // ramp up the speed in increments of 10% of the total speed
    for (int i = (speed / 10); i < speed; i += (speed / 10))
    {
        setForwardSpeed(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    message = "Set the speed of both wheels to " + to_string(speed);
    kaliLog->logp1(message);
    setForwardSpeed(speed);
}

/**
    Ramps down the speed to a halt from the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::forwardRampDown(int speed)
{
    int rampIncrement = speed / 2;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping down the speed from " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->logp1(message);
    
    // ramp down the speed in increments of 10% of the total speed
    for (int i = speed; i > 0; i -= (speed / 10))
    {
        setForwardSpeed(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    kaliLog->logp1("Stop both wheel motors and come to a halt.");
    stop();
}

/**
    Ramps up the reverse speed to the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::reverseRampUp(int speed)
{
    int rampIncrement = speed / 2;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping up the speed to " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->logp1(message);

    // ramp up the speed in increments of 10% of the total speed
    for (int i = (speed / 10); i < speed; i += (speed / 10))
    {
        setReverseSpeed(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    message = "Set the speed of both wheels to " + to_string(speed);
    kaliLog->logp1(message);
    setReverseSpeed(speed);
}

/**
    Ramps down the speed to a halt from the specified value.

    @param speed - A speed from 0-100.
*/
void Wheels::reverseRampDown(int speed)
{
    int rampIncrement = speed / 2;
    Logging* kaliLog = Logging::Instance();
    
    string message = "Ramping down the speed from " + to_string(speed) + " in 10 increments of " + to_string(rampIncrement);
    kaliLog->logp1(message);

    // ramp down the speed in increments of 10% of the total speed
    for (int i = speed; i > 0; i -= (speed / 10))
    {
        setReverseSpeed(i);

        delay(rampIncrement);
    }
    
    // set the final speed accurately
    kaliLog->logp1("Stop both wheel motors and come to a halt.");
    stop();
}

/**
    Brakes gently (ramps down in the forward or reverse direction).

*/
void Wheels::brakeSoft()
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Braking softly down from a speed of " + to_string(currentSpeed);
    kaliLog->logp1(message);

    if (currentSpeed > 0)
    {
        forwardRampDown(currentSpeed);
    }
    else if (currentSpeed < 0)
    {
        reverseRampDown(currentSpeed);
    }
}

/**
    Stops abruptly - sets the forward or reverse direction motion to 0.

*/
void Wheels::stop()
{
    Logging* kaliLog = Logging::Instance();

    kaliLog->logp1("Stop both wheel motors and come to a halt.");
    leftWheels.stop();
    rightWheels.stop();
    
    currentSpeed = 0;
}

/**
    Twirls Kali Robot in the left direction (anticlockwise).

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to twirl for.
*/
void Wheels::twirlLeft(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Twirling left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);

    // twirl according to the given wheel speed
    leftWheels.setReverseMotion(speed);
    rightWheels.setForwardMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue twirling for the specified time
        message = "Holding the twirl for " + to_string(milliseconds) + " milliseconds.";
        kaliLog->logp1(message);
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        kaliLog->logp1("Stop both wheel motors and come to a halt.");
        stop();
    }
}

/**
    Twirls Kali Robot in the right direction (clockwise).

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to twirl for.
*/
void Wheels::twirlRight(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Twirling right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);

    // twirl according to the given wheel speed
    leftWheels.setForwardMotion(speed);
    rightWheels.setReverseMotion(speed);
    currentSpeed = speed;

    if (milliseconds > 0)
    {
        // continue twirling for the specified time
        message = "Holding the twirl for " + to_string(milliseconds) + " milliseconds.";
        kaliLog->logp1(message);
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        kaliLog->logp1("Stop both wheel motors and come to a halt.");
        stop();
    }
}

/**
    Twirls Kali Robot in the left direction (anticlockwise).

    @param speed - A speed from 0-100.
    @param angle - How far to turn.
*/
void Wheels::twirlLeftPrecise(int speed, int angle)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Twirling left with speed " + to_string(speed) + " for " + to_string(angle) + " degrees.";
    kaliLog->logp1(message);

    if (angle > 0 && angle <= 360)
    {
        // twirl according to the given wheel speed
        leftWheels.setReverseMotion(speed);
        rightWheels.setForwardMotion(speed);
        currentSpeed = speed;

        // continue twirling for the specified time
        int milliseconds = calcTwirlTime(speed, angle);
        message = "Holding the twirl for " + to_string(milliseconds) + " milliseconds.";
        kaliLog->logp1(message);
        
        // wait for the specified time
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        kaliLog->logp1("Stop both wheel motors and come to a halt.");
        stop();
    }
}

/**
    Twirls Kali Robot in the right direction (clockwise).

    @param speed - A speed from 0-100.
    @param angle - How far to turn.
*/
void Wheels::twirlRightPrecise(int speed, int angle)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Twirling right with speed " + to_string(speed) + " for " + to_string(angle) + " degrees.";
    kaliLog->logp1(message);

    if (angle > 0 && angle <= 360)
    {
        // twirl according to the given wheel speed
        leftWheels.setForwardMotion(speed);
        rightWheels.setReverseMotion(speed);
        currentSpeed = speed;

        // continue twirling for the specified time
        int milliseconds = calcTwirlTime(speed, angle);
        message = "Holding the twirl for " + to_string(milliseconds) + " milliseconds.";
        kaliLog->logp1(message);
        
        // wait for the specified time
        delay(milliseconds);

        // stop twirling (wheel speed = 0)
        kaliLog->logp1("Stop both wheel motors and come to a halt.");
        stop();
    }
}

/**
    Calculates the time in milliseconds it takes to turn Kali at the given speed to the given angle.
    The time is proportional to 1 / s^2 where s = speed (inverse square law).

    @param speed - A speed from 0-100.
    @param angle - How far to turn.
    @return The number of milliseconds it takes to turn Kali at the given speed to the given angle.
*/
int Wheels::calcTwirlTime(int speed, int angle)
{
    int milliseconds = (3985714.0 / (speed * speed) + 131.4285714) * angle / 360.0;
    
    return milliseconds;
}

/**
 * Turns Kali Robot gently left.
 * 
 * @param speed - A speed from 0-100.
 * @param milliseconds - How many milliseconds to turn for.
 * @param turnAdjustment - how much to adjust the turn. should be a value from 0.0 to 1.0. works to ease the turn.
 * 
 */
void Wheels::turnLeft(int speed, int milliseconds, float turnAdjustment)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);
    
    // limit turnAdjustment in case the wrong values have been sent through
    // invalid values will be set to the default turn
    if (turnAdjustment > 1.0 || turnAdjustment < 0.0)
    {
        turnAdjustment = 1.0;
    }
    int turnSpeedNominal = speed / TURN_FACTOR;
    int turnSpeed = (1 - turnAdjustment) * (speed - turnSpeedNominal) + turnSpeedNominal;
    
    turn(turnSpeed, speed, milliseconds);
}

/**
    Turns Kali Robot gently right.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnRight(int speed, int milliseconds, float turnAdjustment)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);
    
    // limit turnAdjustment in case the wrong values have been sent through
    // invalid values will be set to the default turn
    if (turnAdjustment > 1.0 || turnAdjustment < 0.0)
    {
        turnAdjustment = 1.0;
    }
    int turnSpeedNominal = speed / TURN_FACTOR;
    int turnSpeed = (1 - turnAdjustment) * (speed - turnSpeedNominal) + turnSpeedNominal;
    
    turn(speed, turnSpeed, milliseconds);
}

/**
    Turns Kali Robot aggressively left.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnHardLeft(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning hard left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);
    
    turn((speed / TURN_HARD_FACTOR), speed, milliseconds);
}

/**
    Turns Kali Robot aggressively right.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnHardRight(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning hard right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);
    
    turn(speed, (speed / TURN_HARD_FACTOR), milliseconds);
}

/**
    Turns Kali Robot gently left.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnLeftReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reverse turning left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);
    
    turnReverse((speed / TURN_FACTOR), speed, milliseconds);
}

/**
    Turns Kali Robot gently right.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnRightReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reverse turning right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);
    
    turnReverse(speed, (speed / TURN_FACTOR), milliseconds);
}

/**
    Turns Kali Robot aggressively left.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnHardLeftReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reverse turning hard left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);
    
    turnReverse((speed / TURN_HARD_FACTOR), speed, milliseconds);
}

/**
    Turns Kali Robot aggressively right.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnHardRightReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reverse turning hard right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);
    
    turnReverse(speed, (speed / TURN_HARD_FACTOR), milliseconds);
}

/**
    Internal (protected) method to turn kali left/right

    @param speedLeft - A speed from 0-100 for the left wheels.
    @param speedRight - A speed from 0-100 for the left wheels.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turn(int speedLeft, int speedRight, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning left wheels with speed " + to_string(speedLeft) + " and right wheels with speed " + to_string(speedRight) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);

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
        kaliLog->logp1("Stop both wheel motors and come to a halt.");
        stop();
    }
}

/**
    Internal (protected) method to turn kali left/right

    @param speedLeft - A speed from 0-100 for the left wheels.
    @param speedRight - A speed from 0-100 for the left wheels.
    @param milliseconds - How many milliseconds to turn for.
*/
void Wheels::turnReverse(int speedLeft, int speedRight, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reverse turning left wheels with speed " + to_string(speedLeft) + " and right wheels with speed " + to_string(speedRight) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->logp1(message);

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
        kaliLog->logp1("Stop both wheel motors and come to a halt.");
        stop();
    }
}

/** Returns the current speed
 
    @return The current wheel speed
 
 */

int Wheels::getCurrentSpeed()
{
    return currentSpeed;
}