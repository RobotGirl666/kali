/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   kali->cpp
 * Author: vangelis
 *
 * Created on 26 April 2020, 7:52 am
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>

#include "Logging.h"
#include "KaliRobot.h"
#include "Validation.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Logging* kaliLog = Logging::Instance();
    // try catch everything - this will make kali a little more robust

    //start
    kaliLog->log("", __FUNCTION__, "Kali Awakens! Bow to your machine overlord!");

    try {
        // do stuff here (BE MORE SPECIFIC PLSSS DAD)
        KaliRobot* kali = KaliRobot::Instance();  // create the container class - overall robot

        // switch statement 
        for(int i = 1; i < argc; i++)
        {
            string input = argv[i];
            transform(input.begin(), input.end(), input.begin(),
                [](unsigned char c){ return std::tolower(c); });  //wtf is this?
            if (input.compare("remote") == 0)
            {
                kali->remote.KeyboardControl(kali);
            }

            else if (input.compare("forward") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time);

                kali->wheels.moveForward(speed, time);
            }

            else if (input.compare("reverse") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time);

                kali->wheels.moveReverse(speed, time);
            }

            else if (input.compare("twirlleft") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time, true);

                kali->wheels.twirlLeft(speed, time);
            }

            else if (input.compare("twirlright") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time, true);

                kali->wheels.twirlRight(speed, time);  //add in time
            }

            else if (input.compare("turnleft") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time, true);

                kali->wheels.turnLeft(speed, time);
            }

            else if (input.compare("turnright") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time, true);

                kali->wheels.turnRight(speed, time);
            }

            else if (input.compare("turnhardleft") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time, true);

                kali->wheels.turnHardLeft(speed, time);
            }

            else if (input.compare("turnhardright") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time, true);

                kali->wheels.turnHardRight(speed, time);
            }

            else if (input.compare("turnleftreverse") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time, true);

                kali->wheels.turnLeftReverse(speed, time);
            }

            else if (input.compare("turnrightreverse") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time, true);

                kali->wheels.turnRightReverse(speed, time);
            }

            else if (input.compare("turnhardleftreverse") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time, true);

                kali->wheels.turnHardLeftReverse(speed, time);
            }

            else if (input.compare("turnhardrightreverse") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time, true);

                kali->wheels.turnHardRightReverse(speed, time);
            }

            else if (input.compare("startcamerastream") == 0)
            {
                kali->camera.startStreaming();
            }

            else if (input.compare("stopcamerastream") == 0)
            {
                kali->camera.stopStreaming();
            }

            else if (input.compare("startcamerarecording") == 0)
            {
                kali->camera.startRecording();
            }

            else if (input.compare("stopcamerarecording") == 0)
            {
                kali->camera.stopRecording();
            }

            else if (input.compare("tiltcamera") == 0)
            {
                int angle;
                
                i += Validation::parseAngle(argc, argv, i, angle);

                kali->camera.tilt(angle);
            }

            else if (input.compare("pancamera") == 0)
            {
                int angle;
                
                i += Validation::parseAngle(argc, argv, i, angle);

                kali->camera.pan(angle);
            }

            else if (input.compare("detectfaces") == 0)
            {
                kali->camera.detectFaces();
            }

            else if (input.compare("recognisefaces") == 0)
            {
                kali->camera.recogniseFaces();
            }

            else if (input.compare("say") == 0)
            {
                string text;
                
                i += Validation::parseString(argc, argv, i, text);

                kali->speaker.say(text);
            }

            else if (input.compare("roam") == 0)
            {
                int speed;
                int time;
                
                i += Validation::parseSpeedTime(argc, argv, i, speed, time);

                kali->ultrasonicSensor.roam(speed, time);
            }

            else
            {
                cout << "You can control Kali with the following commands:" << endl;
                cout << "kali forward [speed] [seconds]" << endl;
                cout << "kali reverse [speed] [seconds]" << endl;
                cout << "kali twirlleft [speed] [milliseconds]" << endl;
                cout << "kali twirlright [speed] [milliseconds]" << endl;
                cout << "kali turnleft [speed] [milliseconds]" << endl;
                cout << "kali turnright [speed] [milliseconds]" << endl;
                cout << "kali turnhardleft [speed] [milliseconds]" << endl;
                cout << "kali turnhardright [speed] [milliseconds]" << endl;
                cout << "kali turnleftreverse [speed] [milliseconds]" << endl;
                cout << "kali turnrightreverse [speed] [milliseconds]" << endl;
                cout << "kali turnhardleftreverse [speed] [milliseconds]" << endl;
                cout << "kali turnhardrightreverse [speed] [milliseconds]" << endl;
                cout << "kali startcamerastream" << endl;
                cout << "kali stopcamerastream" << endl;
                cout << "kali startcamerarecording" << endl;
                cout << "kali stopcamerarecording" << endl;
                cout << "kali tiltcamera [angle]" << endl;
                cout << "kali pancamera [angle]" << endl;
                cout << "kali detectfaces" << endl;
                cout << "kali recognisefaces" << endl;
                cout << "kali remote" << endl;
                cout << "kali say" << endl;
                cout << "kali roam" << endl;
            }

        }
    }
    catch (const std::exception& ex) {
        kaliLog->log("", __FUNCTION__, ex.what());
    }
    catch (...) {
        // Just log that there was an issue
        kaliLog->log("", __FUNCTION__, "Unknow exception thrown!");
    }

    // goodbye
    kaliLog->log("", __FUNCTION__, "Goodbye puny humans!");
    
    return 0;
}

