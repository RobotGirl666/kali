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

void Speaker::say(string& text_to_say)
{
    espeak_ERROR speakErr;

    Logging* kaliLog = Logging::Instance();
    // try catch everything - this will make kali a little more robust

    //must be called before any other functions
    //espeak initialize
    if (espeak_Initialize(AUDIO_OUTPUT_SYNCH_PLAYBACK, 0, NULL, espeakINITIALIZE_PHONEME_EVENTS) >= 0)
    {
        espeak_SetSynthCallback(Speaker::SynthCallback);

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
