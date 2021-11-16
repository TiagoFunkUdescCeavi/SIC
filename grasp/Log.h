#ifndef LOGGER_H
#define LOGGER_H

#include <string>

using std::string;

#define LOG_LEVEL 1

class Log{
    private:
        string message;

        static Log * _instance;
    
    protected:
        Log();
    
    public:
        static Log * instance();
        void log( string s, int level );
        void show();
};

#endif