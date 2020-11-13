/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Remote.cpp
 * Author: ioanna
 * 
 * Created on 22 June 2020, 5:29 pm
 * 
 * need to install ncurses
 * sudo apt-get install ncurses-dev
 */

#include <iostream>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>
#include <wiringPi.h>
#include <softPwm.h>

#include "Remote.h"
#include "KaliRobot.h"

Remote::Remote() {
}

Remote::Remote(const Remote& orig) {
}

Remote::~Remote() {
}

void Remote::KeyboardControl(KaliRobot* kali)
{
    // POLLING TECHNIQUE
    char key = 127;
    
    //while(1) 
    {
        key = getch();
        while (key == 0 || key == -32)
        {
            key = getch();
            if (key == 72) //up arrow
            {
            //call forward function
                kali->wheels.moveForward(30,0);
                delay(1000);
            }
            else if (key == 75) // left arrow
            {
                //call turn left
                kali->wheels.twirlLeft(30,0);
                delay(1000);
            }
            else if (key == 77) // right arrow
            {
                //call turn right
                kali->wheels.twirlRight(30,0);
                delay(1000);
            }
            else if (key == 80) // down arrow
            {
                //call reverse?? or brake??
                kali->wheels.moveReverse(30,0);
                delay(1000);
            }
        }
   }

}