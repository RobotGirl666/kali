/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Remote.h
 * Author: ioanna
 *
 * Created on 22 June 2020, 5:29 pm
 */

#ifndef REMOTE_H
#define REMOTE_H

class KaliRobot;

class Remote {
public:
    Remote();
    Remote(const Remote& orig);
    virtual ~Remote();
    void KeyboardControl(KaliRobot* kali);
private:

};

#endif /* REMOTE_H */

