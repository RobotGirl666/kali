/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camera.h
 * Author: vangelis
 *
 * Created on 26 April 2020, 7:40 pm
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <string>

// Include required header files from OpenCV directory
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Servo.h"

using namespace std;
using namespace cv;

class Camera {
public:
    Camera();
    Camera(const Camera& orig);
    virtual ~Camera();
    
    // Camera behaviours
    void initialise();
    void startStreaming();
    void stopStreaming();
    void startRecording();
    void stopRecording();
    void tilt(int angle);
    void pan(int angle);
    void detectFaces();
    void recogniseFaces();

protected:
    bool streaming;
    bool recording;
    Servo horizontalServo;
    Servo verticalServo;
    
    void detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale);
    void generateUniqueFilename(char* timestring, char* baseName);
    
private:

};

#endif /* CAMERA_H */

