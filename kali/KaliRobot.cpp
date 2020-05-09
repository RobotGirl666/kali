/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KaliRobot.cpp
 * Author: vangelis
 * 
 * Created on 26 April 2020, 7:22 pm
 */

#include <wiringPi.h>
#include <softPwm.h>
#include <cstdlib>
#include <string>

#include "KaliRobot.h"
#include "Logging.h"

using namespace std;

KaliRobot::KaliRobot() {
    initialise(); // initialise all the Kali components - must do this before anything else!
}

KaliRobot::KaliRobot(const KaliRobot& orig) {
}

KaliRobot::~KaliRobot() {
}

/*
    Initialises the Wiring Pi library and each component of KaliRobot is asked to do the same.

*/
void KaliRobot::initialise()
{
    wiringPiSetup(); // Initialise WiringPi

    // initialise all the different components
    wheels.initialise();
    camera.initialise();
    
    // give it a couple of seconds to work its way through
    delay(2000);
}

/*
    Moves Kali Robot forward. Calls the wheels to move forward.

    @param speed - A speed from 0-100.
    @param seconds - How many seconds to move forward for. A value of 0 will start movement and not stop.
*/
void KaliRobot::moveForward(int speed, int seconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Moving forward with speed " + to_string(speed) + " for " + to_string(seconds) + " seconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    
    wheels.moveForward(speed, seconds);
}

/*
    Moves Kali Robot in the reverse direction. Calls the wheels to reverse.

    @param speed - A speed from 0-100.
    @param seconds - How many seconds to reverse for. A value of 0 will start movement and not stop.
*/
void KaliRobot::moveReverse(int speed, int seconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Reversing with speed " + to_string(speed) + " for " + to_string(seconds) + " seconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.moveReverse(speed, seconds);
}

/*
    Gently brings forward or reverse movement to a halt. Calls the wheels to slow down and stop.

*/
void KaliRobot::brakeSoft()
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Braking gently";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.brakeSoft();
}

/*
    Abruptly brings forward or reverse movement to a halt. Calls the wheels to suddenly stop.

*/
void KaliRobot::brakeHard()
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Braking suddenly";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.brakeHard();
}

/*
    Twirls Kali Robot in the left direction (anticlockwise). Calls the wheels to twirl.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to twirl for.
*/
void KaliRobot::twirlLeft(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Twirling left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.twirlLeft(speed, milliseconds);
}

/*
    Twirls Kali Robot in the right direction (clockwise). Calls the wheels to twirl.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to twirl for.
*/
void KaliRobot::twirlRight(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Twirling right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.twirlRight(speed, milliseconds);
}

/*
    Turns Kali Robot in the left direction with a gentle turning radius. Calls the wheels to turn.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void KaliRobot::turnLeft(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnLeft(speed, milliseconds);
}

/*
    Turns Kali Robot in the right direction with a gentle turning radius. Calls the wheels to turn.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void KaliRobot::turnRight(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnRight(speed, milliseconds);
}

/*
    Turns Kali Robot in the left direction with a sharp turning radius. Calls the wheels to turn.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void KaliRobot::turnHardLeft(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning hard left with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnHardLeft(speed, milliseconds);
}

/*
    Turns Kali Robot in the right direction with a gentle turning radius. Calls the wheels to turn.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void KaliRobot::turnHardRight(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning hard right with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnHardRight(speed, milliseconds);
}

/*
    Turns Kali Robot in the left direction with a gentle turning radius. Calls the wheels to turn.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void KaliRobot::turnLeftReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning left in reverse with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnLeftReverse(speed, milliseconds);
}

/*
    Turns Kali Robot in the right direction with a gentle turning radius. Calls the wheels to turn.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void KaliRobot::turnRightReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning right in reverse with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnRightReverse(speed, milliseconds);
}

/*
    Turns Kali Robot in the left direction with a sharp turning radius. Calls the wheels to turn.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void KaliRobot::turnHardLeftReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning hard left in reverse with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnHardLeftReverse(speed, milliseconds);
}

/*
    Turns Kali Robot in the right direction with a gentle turning radius. Calls the wheels to turn.

    @param speed - A speed from 0-100.
    @param milliseconds - How many milliseconds to turn for.
*/
void KaliRobot::turnHardRightReverse(int speed, int milliseconds)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Turning hard right in reverse with speed " + to_string(speed) + " for " + to_string(milliseconds) + " milliseconds.";
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    wheels.turnHardRightReverse(speed, milliseconds);
}

void KaliRobot::startCameraStream()
{
    Logging* kaliLog = Logging::Instance();
    
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Start camera stream.");

    camera.startStreaming();
}

void KaliRobot::stopCameraStream()
{
    Logging* kaliLog = Logging::Instance();
    
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Stop camera stream.");

    camera.stopStreaming();
}

void KaliRobot::startCameraRecording()
{
    Logging* kaliLog = Logging::Instance();
    
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Start camera recording.");

    camera.startRecording();
}

void KaliRobot::stopCameraRecording()
{
    Logging* kaliLog = Logging::Instance();
    
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Stop camera recording.");

    camera.stopRecording();
}

void KaliRobot::tiltCamera(int angle)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Tilt camera to angle " + to_string(angle);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    camera.tilt(angle);
}

void KaliRobot::panCamera(int angle)
{
    Logging* kaliLog = Logging::Instance();
    
    string message = "Pan camera to angle " + to_string(angle);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    camera.pan(angle);
}

void KaliRobot::remote()
{
    
}

void KaliRobot::party()
{
    
}