#include "Log.h"

#include <iostream>

using std::cout;
using std::endl;

Log * Log::_instance = 0;

Log::Log(){
    this->message = "";
}

Log * Log::instance(){
    if( Log::_instance == 0 ){
        Log::_instance = new Log();
    }
    return Log::_instance;
}

void Log::log( string s, int level ){
    if( level <= LOG_LEVEL ){
        this->message += s;
    }
}

void Log::show(){
    cout << this->message << endl;
}