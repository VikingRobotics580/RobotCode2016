#include "log_writer.h"

log_writer::log_writer():
    file(),
    filename("roboLog.log")
{
    file.open(filename);
}

log_writer::~log_writer(){
    file.close();
}

int log_writer::writeToFile(std::string& msg){
    return this->writeToFile(msg.c_str());
}

int log_writer::writeToFile(const char* msg){
    if(file.is_open()){
        file << msg;
        return 0;
    }
    return 1;
}

