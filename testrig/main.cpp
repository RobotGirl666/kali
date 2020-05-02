/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: vangelis
 *
 * Created on 1 May 2020, 8:49 am
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>

#include <cstdlib>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    for(int i = 1; i < argc; i++)
    {
        string input = argv[i];
        transform(input.begin(), input.end(), input.begin(),
            [](unsigned char c){ return std::tolower(c); });
        
        if (input.compare("forward") == 0)
        {
            if (i + 1 >= argc)
            {
                cout << "No parameters given" << endl;
            }
            else
            {
                int speed = atoi(argv[i+1]);
                i++;
                if (i + 1 <= argc)
                {
                    int time = atoi(argv[i+1]);
                    i++;
                    cout << "Two parameters given. Speed is " << speed << " and time is " << time << " seconds." << endl;
                }
                else
                {
                    cout << "Only one parameter given. Speed is " << speed << endl;
                }
            }
        }
    }

    return 0;
}

