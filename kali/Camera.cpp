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

/*******************************************************************************
 * 
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
 *******************************************************************************
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
 * destination_directory="~/Videos"
 * destination_file="cncjs-recording_$(date +'%Y%m%d_%H%M%S').mpeg"
 * 
 * # Recored Stream w/ ffmpeg
 * ffmpeg -f mjpeg -re -i "${source_stream}" -q:v 10 "${destination_directory}/${destination_file}"
 * 
 *******************************************************************************
 * 
 * Face recognition using OpenCV - https://opencv.org/
 * Install the dependencies: sudo apt install build-essential cmake git pkg-config libgtk-3-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev gfortran openexr libatlas-base-dev python3-dev python3-numpy libtbb2 libtbb-dev libdc1394-22-dev
 * 
 * Installing on Raspbian: https://www.pyimagesearch.com/2019/09/16/install-opencv-4-on-raspberry-pi-4-and-raspbian-buster/
 * 
 * Need to keep a database of face images which is built up from video image captures
 * For this we use SQLite - https://www.sqlite.org/index.html
 * Install by running sudo apt install sqlite3
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

// Include required header files from OpenCV directory
#include <opencv2/core/types_c.h>

#include "Camera.h"
#include "Logging.h"

extern char **environ;

Camera::Camera() {
    // initialise our variables
    streaming = false;
    recording = false;
}

Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
}

/**
 * 
 * Initialises the camera servos.
 *
 */
void Camera::initialise()
{
    horizontalServo.initialise(14);
    verticalServo.initialise(13);
}

/**
 * 
 * Starts streaming from the camera into a http stream.
 * The stream can be viewed at http://localhost:8080/?action=stream from the local machine.
 * From any other machine, localhost shold be replaced with the ip address of the machine doing the streaming.
 *
 */
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

/**
 * 
 * Stops streaming from the camera into a http stream (just kills the process using pkill).
 *
 */
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

/**
 * 
 * Starts recording from the stream (startStreaming should be called before calling this method)
 * source_stream="http://localhost:8080/?action=stream"
 * destination_directory="/home/pi/Videos"
 * destination_file="kali_recording_$(date_time_milliseconds).mpeg"
 * 
 * # Recored Stream w/ ffmpeg
 * ffmpeg -f mjpeg -i "${source_stream}" -q:v 10 "${destination_directory}/${destination_file}"
 * 
 */
void Camera::startRecording()
{
    Logging* kaliLog = Logging::Instance();

    if (!recording)
    {
        // set all the paramebers that need to be parsed to ffmpeg
        char uniqueFilename[200];
        char baseFilename[] = "~/Videos/kali_recording";
        generateUniqueFilename(uniqueFilename, baseFilename);
        pid_t pid;
        char appName[] = "ffmpeg";
        char param1[] = "-f";
        char param2[] = "mjpeg";
        char param3[] = "-i";
        char param4[] = "http://localhost:8080/?action=stream";
        char param5[] = "-q:v";
        char param6[] = "10";
        char *argv[] = {appName, param1, param2, param3, param4, param5, param6, uniqueFilename, NULL};

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

/**
 * 
 * Stops recording from the http stream (just kills the process using pkill).
 *
 */
void Camera::stopRecording()
{
    Logging* kaliLog = Logging::Instance();
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Stopping video streaming.");

    // set all the parameters that need to be parsed to pkill
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

/**
 * 
 * Tilt camera to the specified angle - sets the position of the relevant servo.
 *
 * @param angle - the angle to tilt to (0-180)
 *  
 */
void Camera::tilt(int angle)
{
    verticalServo.setPos(angle);
}

/**
 * 
 * Pan camera to the specified angle - sets the position of the relevant servo.
 *
 * @param angle - the angle to pan to (0-180)
 * 
 */
void Camera::pan(int angle)
{
    horizontalServo.setPos(angle);
}

void Camera::detectFaces()
{
    // VideoCapture class for playing video for which faces to be detected 
    VideoCapture capture; 
    Mat frame, image; 

    // PreDefined trained XML classifiers with facial features 
    CascadeClassifier cascade, nestedCascade; 
    double scale=1; 

    // Load classifiers from "opencv/data/haarcascades" directory 
    nestedCascade.load( "../../haarcascade_eye_tree_eyeglasses.xml" ) ; 

    // Change path before execution 
    cascade.load( "../../haarcascade_frontalcatface.xml" ) ; 

    // Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video 
    capture.open(0); 
    if( capture.isOpened() ) 
    { 
        // Capture frames from video and detect faces 
        cout << "Face Detection Started...." << endl; 
        while(1) 
        { 
                capture >> frame; 
                if( frame.empty() ) 
                        break; 
                Mat frame1 = frame.clone(); 
                detectAndDraw( frame1, cascade, nestedCascade, scale ); 
                char c = (char)waitKey(10); 

                // Press q to exit from window 
                if( c == 27 || c == 'q' || c == 'Q' ) 
                        break; 
        } 
    } 
    else
        cout<<"Could not Open Camera"; 
}

void Camera::recogniseFaces()
{
    
}

void Camera::detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale)
{
    vector<Rect> faces, faces2; 
    Mat gray, smallImg; 

    cvtColor( img, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale 
    double fx = 1 / scale; 

    // Resize the Grayscale Image 
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR ); 
    equalizeHist( smallImg, smallImg ); 

    // Detect faces of different sizes using cascade classifier 
    cascade.detectMultiScale( smallImg, faces, 1.1, 
                                                    2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) ); 

    // Draw circles around the faces 
    for ( size_t i = 0; i < faces.size(); i++ ) 
    { 
        Rect r = faces[i]; 
        Mat smallImgROI; 
        vector<Rect> nestedObjects; 
        Point center; 
        Scalar color = Scalar(255, 0, 0); // Color for Drawing tool 
        int radius; 

        double aspect_ratio = (double)r.width/r.height; 
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 ) 
        { 
            center.x = cvRound((r.x + r.width*0.5)*scale); 
            center.y = cvRound((r.y + r.height*0.5)*scale); 
            radius = cvRound((r.width + r.height)*0.25*scale); 
            circle( img, center, radius, color, 3, 8, 0 ); 
        } 
        else
            rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)), 
                            cvPoint(cvRound((r.x + r.width-1)*scale), 
                            cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0); 
        if( nestedCascade.empty() ) 
            continue; 
        smallImgROI = smallImg( r ); 

        // Detection of eyes int the input image 
        nestedCascade.detectMultiScale( smallImgROI, nestedObjects, 1.1, 2, 
                                                                        0|CASCADE_SCALE_IMAGE, Size(30, 30) ); 

        // Draw circles around eyes 
        for ( size_t j = 0; j < nestedObjects.size(); j++ ) 
        { 
            Rect nr = nestedObjects[j]; 
            center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale); 
            center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale); 
            radius = cvRound((nr.width + nr.height)*0.25*scale); 
            circle( img, center, radius, color, 3, 8, 0 ); 
        } 
    } 

    // Show Processed Image with detected faces 
    imshow( "Face Detection", img ); 
}

/**
 * 
 * Generate a unique filename for recording the stream.
 *
 * @param uniqueFilename - character string to store the generated filename
 * @param baseName - the base name for the filename eg "recording_"
 * 
 */
void Camera::generateUniqueFilename(char* uniqueFilename, char* baseName)
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
    sprintf(uniqueFilename, "%s_%s_%03d.mpeg", baseName, datetime_buffer, millisec);
}
