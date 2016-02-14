#ifndef _LOG_WRITER_H_
#define _LOG_WRITER_H_

#include <iostream>
#include <fstream>
#include <string>

class log_writer {
    public:
        ~log_writer();
        int writeToFile(std::string&);
        int writeToFile(const char*);
        static log_writer& getInstance(){
            static log_writer instance;
            return instance;
        };
    private:
        log_writer();
        std::ofstream file;
        std::string filename;
        static log_writer instance;
};

inline int wLog(std::string& s){
    return log_writer::getInstance().writeToFile(s);
}

inline int wLog(const char* s){
    return log_writer::getInstance().writeToFile(s);
}

#endif

