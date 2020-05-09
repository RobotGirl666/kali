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
 * MJPEG-Streamer Install & Setup - this streams video to http
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
 * Go here to watch the stream: http://10.1.1.100:8080/?action=stream
 * where 10.1.1.100 is the ip address of the raspberry pi
 * and from the raspberry pi itself use: http://localhost:8080/?action=stream
 * 
 * To record the video stream, you will need to install ffmpeg
 * 
 * # Install FFMpeg from Package Manager
 * sudo apt-get update  
 * sudo apt-get install ffmpeg -y
 * 
 * 
 * Recored Stream w/ ffmpeg
 * 
 * # [Varables]
 * source_stram="http://localhost:8080/?action=stream"
 * destination_directory="/home/pi/Videos"
 * destination_file="cncjs-recording_$(date +'%Y%m%d_%H%M%S').mpeg"
 * 
 * # Recored Stream w/ ffmpeg
 * ffmpeg -f mjpeg -re -i "${source_stream}" -q:v 10 "${destination_directory}/${destination_file}"
 * 
 */

#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <spawn.h>
#include <time.h>
#include <iostream>
#include <sys/time.h>
#include <tgmath.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "Camera.h"
#include "Logging.h"

extern char **environ;

using namespace std;

Camera::Camera() {
    // initialise our variables
    streaming = false;
    recording = false;
}

Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
}

/*
    Initialises the Wiring Pi library for this servo.

*/
void Camera::initialise()
{
    horizontalServo.initialise(14);
    verticalServo.initialise(13);
}

void Camera::startStreaming()
{
    Logging* kaliLog = Logging::Instance();

    if (!streaming)
    {
        // set all the paramebers that need to be parsed to ffmpeg
        pid_t pid;
        char appName[] = "mjpg_streamer";
        char param1[] = "-i";
        char param2[] = "input_uvc.so -r 1280x960 -d /dev/video0 -f 30";
        char param3[] = "-o";
        char param4[] = "output_http.so -p 8080 -w /usr/local/share/mjpg-streamer/www";
        char *argv[] = {appName, param1, param2, param3, param4, NULL};

        // set output to null so it doesn't go to the screen - very annoying!
        posix_spawn_file_actions_t action;
        posix_spawn_file_actions_init(&action);
        posix_spawn_file_actions_addopen (&action, STDERR_FILENO, "/dev/null", O_RDONLY, 0);

        int status = -1;
        status = posix_spawnp(&pid, appName, &action, NULL, argv, environ);
        posix_spawn_file_actions_destroy(&action);
        if (status == 0)
        {
            streaming = true;
            kaliLog->log(typeid(this).name(), __FUNCTION__, "Video streaming has commenced!");
        }
        else
        {
            string message = "Failed to stop video streaming! Error: " + to_string(status);
            kaliLog->log(typeid(this).name(), __FUNCTION__, message);
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

    // set all the paramebers that need to be parsed to pkill
    pid_t pid;
    char appName[] = "pkill";
    char param1[] = "mjpg_streamer";
    char *argv[] = {appName, param1, NULL};

    // set output to null so it doesn't go to the screen - very annoying!
    posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init(&action);
    posix_spawn_file_actions_addopen (&action, STDERR_FILENO, "/dev/null", O_RDONLY, 0);

    int status;
    status = posix_spawnp(&pid, appName, &action, NULL, argv, environ);
    posix_spawn_file_actions_destroy(&action);
    if (status == 0)
    {
        streaming = false;
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Video streaming has stopped!");
    }
    else
    {
        string message = "Failed to stop video streaming! Error: " + to_string(status);
        kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    }
}
/*
 * source_stram="http://localhost:8080/?action=stream"
 * destination_directory="/home/pi/Videos"
 * destination_file="cncjs-recording_$(date +'%Y%m%d_%H%M%S').mpeg"
 * 
 * # Recored Stream w/ ffmpeg
 * ffmpeg -f mjpeg -re -i "${source_stream}" -q:v 10 "${destination_directory}/${destination_file}"
 */
void Camera::startRecording()
{
    Logging* kaliLog = Logging::Instance();

    if (!recording)
    {
        // set all the paramebers that need to be parsed to ffmpeg
        char uniqueFilename[200];
        char baseFilename[] = "/home/pi/Videos/kali_recording";
        generateUniqueFilename(uniqueFilename, baseFilename);
        pid_t pid;
        char appName[] = "ffmpeg";
        char param1[] = "-f";
        char param2[] = "mjpeg";
        char param3[] = "-re";
        char param4[] = "-i";
        char param5[] = "http://localhost:8080/?action=stream";
        char param6[] = "-q:v";
        char param7[] = "10";
        char *argv[] = {appName, param1, param2, param3, param4, param5, param6, param7, uniqueFilename, NULL};

        // set output to null so it doesn't go to the screen - very annoying!
        posix_spawn_file_actions_t action;
        posix_spawn_file_actions_init(&action);
        posix_spawn_file_actions_addopen(&action, STDERR_FILENO, "/dev/null", O_RDONLY, 0);

        int status = -1;
        status = posix_spawnp(&pid, appName, &action, NULL, argv, environ);
        posix_spawn_file_actions_destroy(&action);
        if (status == 0)
        {
            recording = true;
            kaliLog->log(typeid(this).name(), __FUNCTION__, "Video streaming has commenced!");
        }
        else
        {
            string message = "Failed to stop video streaming! Error: " + to_string(status);
            kaliLog->log(typeid(this).name(), __FUNCTION__, message);
        }
    }
    else
    {
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Already recording video!");
    }
}

void Camera::stopRecording()
{
    Logging* kaliLog = Logging::Instance();
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Stopping video streaming.");

    // set all the paramebers that need to be parsed to pkill
    pid_t pid;
    char appName[] = "pkill";
    char param1[] = "ffmpeg";
    char *argv[] = {appName, param1, NULL};

    // set output to null so it doesn't go to the screen - very annoying!
    posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init(&action);
    posix_spawn_file_actions_addopen (&action, STDERR_FILENO, "/dev/null", O_RDONLY, 0);

    int status;
    status = posix_spawnp(&pid, appName, &action, NULL, argv, environ);
    posix_spawn_file_actions_destroy(&action);
    if (status == 0)
    {
        recording = false;
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Video recording has stopped!");
    }
    else
    {
        string message = "Failed to stop video recording! Error: " + to_string(status);
        kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    }
}

void Camera::tilt(int angle)
{
    verticalServo.setPos(angle);
}

void Camera::pan(int angle)
{
    horizontalServo.setPos(angle);
}

void Camera::generateUniqueFilename(char* timestring, char* baseName)
{
    char datetime_buffer[26];
    int millisec;
    struct tm* tm_info;
    struct timeval tv;

    gettimeofday(&tv, NULL);

    millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
    if (millisec>=1000) { // Allow for rounding up to nearest second
      millisec -=1000;
      tv.tv_sec++;
    }

    tm_info = localtime(&tv.tv_sec);

    strftime(datetime_buffer, 26, "%Y_%m_%d_%H_%M_%S", tm_info);
    sprintf(timestring, "%s_%s_%03d.mpeg", baseName, datetime_buffer, millisec);
}
