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

enum LoggingLevel { LogOff, LogInfo, LogDebug };

#define logp1(a) log(typeid(this).name(),__FUNCTION__,a)
#define logp2(a,b) log(typeid(this).name(),__FUNCTION__,a,b)
#define logp3(a,b,c) log(typeid(this).name(),__FUNCTION__,a,b,c)
#define logp4(a,b,c,d) log(typeid(this).name(),__FUNCTION__,a,b,c,d)
#define lognp1(a) log("",__FUNCTION__,a)

class Logging {
public:
    static Logging* Instance();
    virtual ~Logging();
    
    void log(string class_name, string method_name, string message, LoggingLevel level = LogInfo, bool output_to_speaker = false, bool output_to_screen = true);
    void setLogLevel(LoggingLevel level);
    
protected:
    Logging();
    Logging(const Logging& orig);
    const string currentDateTime();

private:
    static Logging* _instance;
    static string logFileName;
    ofstream logFile;
    static LoggingLevel logLevel;
};

#endif /* LOGGING_H */

