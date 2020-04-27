/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Logging.h
 * Author: vangelis
 *
 * Created on 27 April 2020, 8:00 am
 */

#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Logging {
public:
    static Logging* Instance();
    virtual ~Logging();
    
    void log(string& message);
    
protected:
    Logging();
    Logging(const Logging& orig);
    const std::string currentDateTime();

private:
    static Logging* _instance;
    static string logFileName;
    ofstream logFile;
};

#endif /* LOGGING_H */

