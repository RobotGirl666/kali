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

#include "Servo.h"

class Camera {
public:
    Camera();
    Camera(const Camera& orig);
    virtual ~Camera();
    
    // Camera behaviours
    void initialise();
    void startStreaming();
    void stopStreaming();
    void tilt(int angle);
    void pan(int angle);

protected:
    bool streaming;
    Servo horizontalServo;
    Servo verticalServo;
    
private:

};

#endif /* CAMERA_H */

