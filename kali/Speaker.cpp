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

#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <spawn.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

#include "Speaker.h"
#include "Logging.h"

Speaker::Speaker() {
}

Speaker::Speaker(const Speaker& orig) {
}

Speaker::~Speaker() {
}

void Speaker::say(string& text_to_say)
{
    Logging* kaliLog = Logging::Instance();
    string message = "Saying: " + text_to_say;
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);

    // set all the paramebers that need to be parsed to pkill
    pid_t pid;
    char appName[] = "espeak-ng";
    char *argv[] = {appName, (char*)text_to_say.c_str(), NULL};

    // set output to null so it doesn't go to the screen - very annoying!
    posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init(&action);
    posix_spawn_file_actions_addopen (&action, STDERR_FILENO, "/dev/null", O_RDONLY, 0);

    int status;
    status = posix_spawnp(&pid, appName, &action, NULL, argv, environ);
    posix_spawn_file_actions_destroy(&action);
    if (status != 0)
    {
        kaliLog->log(typeid(this).name(), __FUNCTION__, "Failed to speak");
    }
}
