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

#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <spawn.h>

#include "Camera.h"
#include "Logging.h"

extern char **environ;

using namespace std;

Camera::Camera() {
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
        char appName[] = "mjpg_streamer";
        char param1[] = "-i";
        char param2[] = "input_uvc.so -r 1280x720 -d /dev/video0 -f 30";
        char param3[] = "-o";
        char param4[] = "output_http.so -p 8080 -w /usr/local/share/mjpg-streamer/www";
        char *argV[] = {appName, param1, param2, param3, param4};
        int status = -1;
        status = posix_spawnp(&pid, appName, NULL, NULL, argV, environ);
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

    if (streaming)
    {
        char appName[] = "sh";
        char param1[] = "-c";
        char cmd[200];
        sprintf(cmd, "%s%i%s", "ps aux | grep mjpg_streamer | grep /dev/video0 | tr -s ' ' | cut -d ' ' -f 2 | grep -v ", pid, " | xargs -r kill");
        char *argv[] = {appName, param1, cmd, NULL};
        int status;
        printf("Run command: %s\n", cmd);
        status = posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);
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
}
