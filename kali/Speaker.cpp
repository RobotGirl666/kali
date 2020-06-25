/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Speaker.cpp
 * Author: vangelis
 * 
 * Created on 12 June 2020, 3:44 pm
 * 
 * How to install espeak for the text to speech conversion
 * sudo apt-get install espeak libespeak1 libespeak-dev espeak-data
 * 
 * ok, so I have found out that espeak has been broken on raspberry pi
 * need to use espeak-ng instead
 * 
 */

#include <cstring>

#include "Speaker.h"
#include "Logging.h"

Speaker::Speaker() {
}

Speaker::Speaker(const Speaker& orig) {
}

Speaker::~Speaker() {
}

/** Must be called before any synthesis functions are called.
   This specifies a function in the calling program which is called when a buffer of
   speech sound data has been produced.
   The callback function is of the form:
int SynthCallback(short *wav, int numsamples, espeak_EVENT *events);
   @param wav:  is the speech sound data which has been produced.
      NULL indicates that the synthesis has been completed.
   @param numsamples: is the number of entries in wav.  This number may vary, may be less than
      the value implied by the buflength parameter given in espeak_Initialize, and may
      sometimes be zero (which does NOT indicate end of synthesis).
   @param events: an array of espeak_EVENT items which indicate word and sentence events, and
      also the occurance if <mark> and <audio> elements within the text.  The list of
      events is terminated by an event of type = 0.
   Callback returns: 0=continue synthesis,  1=abort synthesis.
*/
int Speaker::SynthCallback(short* wav, int numsamples, espeak_EVENT* events)
{
    return 0;
}

void Speaker::say(string& text_to_say, int volume, int rate, int pitch, int range)
{
    espeak_ERROR speakErr;

    Logging* kaliLog = Logging::Instance();
    // try catch everything - this will make kali a little more robust

    //must be called before any other functions
    //espeak initialize
    if (espeak_Initialize(AUDIO_OUTPUT_SYNCH_PLAYBACK, 0, NULL, espeakINITIALIZE_PHONEME_EVENTS) >= 0)
    {
        espeak_SetSynthCallback(Speaker::SynthCallback);
        
        // set some properties
        espeak_VOICE voice = {
            "Kali", // name
            "en-uk", // language
            NULL, // identifier
            2, // gender - female
            70, // age
            0 // variant
        };
        espeak_SetVoiceByProperties(&voice);

        // set some parameters
        espeak_SetParameter(espeakVOLUME, volume, 0);
        espeak_SetParameter(espeakRATE, rate, 0);
        espeak_SetParameter(espeakPITCH, pitch, 0);
        espeak_SetParameter(espeakRANGE, range, 0);

        if ((speakErr = espeak_Synth(text_to_say.c_str(), text_to_say.size(), 0, POS_SENTENCE, 0, espeakCHARS_AUTO, NULL, NULL)) != EE_OK)
        {
            // failed
            kaliLog->log("", __FUNCTION__, "Error on synth creation - cannot convert text to speech.");
        }
    }
    else
    {
        // failed
        kaliLog->log("", __FUNCTION__, "Failed to initialize espeak.");
    }
}