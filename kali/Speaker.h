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
#include <espeak-ng/speak_lib.h>

using namespace std;

class Speaker {
public:
    Speaker();
    Speaker(const Speaker& orig);
    virtual ~Speaker();
    
    static int SynthCallback(short *wav, int numsamples, espeak_EVENT *events);
    void say(string& text_to_say, int volume = 100, int rate = 100, int pitch = 40, int range = 50);
    
private:

};

#endif /* SPEAKER_H */