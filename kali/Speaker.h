/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Speaker.h
 * Author: vangelis
 *
 * Created on 12 June 2020, 3:44 pm
 */

#ifndef SPEAKER_H
#define SPEAKER_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Speaker {
public:
    Speaker();
    Speaker(const Speaker& orig);
    virtual ~Speaker();
    
    void say(string& text_to_say);
    
private:

};

#endif /* SPEAKER_H */

