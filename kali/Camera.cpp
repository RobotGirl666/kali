/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camera.cpp
 * Author: vangelis
 * 
 * Created on 26 April 2020, 7:40 pm
 */

/*
 * MJPEG-Streamer Install & Setup
 * 
 * https://github.com/cncjs/cncjs/wiki/Setup-Guide:-Raspberry-Pi-%7C-MJPEG-Streamer-Install-&-Setup-&-FFMpeg-Recording
 * 
 * # Update & Install Tools
 * sudo apt-get update -y
 * sudo apt-get upgrade -y
 * sudo apt-get install build-essential imagemagick libv4l-dev libjpeg-dev cmake -y
 * 
 * # Clone Repo in /tmp
 * cd /tmp
 * git clone https://github.com/jacksonliam/mjpg-streamer.git
 * cd mjpg-streamer/mjpg-streamer-experimental
 * 
 * # Make
 * make
 * sudo make install
 * 
 * # Run
 * /usr/local/bin/mjpg_streamer -i "input_uvc.so -r 1280x720 -d /dev/video0 -f 30" -o "output_http.so -p 8080 -w /usr/local/share/mjpg-streamer/www"
 * 
 */

#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <spawn.h>

#include "Camera.h"
#include "Logging.h"

extern char **environ;

using namespace std;

Camera::Camera() {
    // initialise our variables
    streaming = false;
}

Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
}

/*
    Initialises the Wiring Pi library for each set of wheels.

*/
void Camera::initialise()
{
}

void Camera::startStreaming()
{
    Logging* kaliLog = Logging::Instance();

    if (!streaming)
    {
        //system("mjpg_streamer -i \"input_uvc.so -r 1280x720 -d /dev/video0 -f 30\" -o \"output_http.so -p 8080 -w /usr/local/share/mjpg-streamer/www\" >> ${MJPG_STREAMER_LOG_FILE} 2>&1 &");
        pid_t pid;
        char appName[] = "mjpg_streamer";
        char param1[] = "-i";
        char param2[] = "input_uvc.so -r 1280x960 -d /dev/video0 -f 30";
        char param3[] = "-o";
        char param4[] = "output_http.so -p 8080 -w /usr/local/share/mjpg-streamer/www";
        char *argv[] = {appName, param1, param2, param3, param4, NULL};
        int status = -1;
        status = posix_spawnp(&pid, appName, NULL, NULL, argv, environ);
        if (status == 0)
        {
            streaming = true;
            kaliLog->log(typeid(this).name(), __FUNCTION__, "Video streaming has commenced!");
        }
        else
        {
            kaliLog->log(typeid(this).name(), __FUNCTION__, "Failed to start video streaming!");
        }
    }
    else
    {
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Already streaming video!");
    }
}

void Camera::stopStreaming()
{
    Logging* kaliLog = Logging::Instance();
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Stopping video streaming.");

    pid_t pid;
    char appName[] = "pkill";
    char param1[] = "-q";
    char param2[] = "mjpg_streamer";
    char *argv[] = {appName, param1, param2, NULL};
    int status;
    status = posix_spawnp(&pid, appName, NULL, NULL, argv, environ);
    if (status == 0)
    {
        streaming = false;
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Video streaming has stopped!");
    }
    else
    {
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Failed to stop video streaming!");
    }
}
