/*
 * RobotVikings
 * Config.h
 * 12/11/15
 * Defines a Config class.
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_
#include <string>
#include <vector>
#include <map>
#include "types.h"

//static const uint64 UINT64_MAX = (0-1);

class Config{
public:
    Config(std::string&);
    Config(const char*);
    Config();

    template<typename T>
    inline T* getOption(std::string& var){
        return (T*)(m_options.at(var));
    }

    template<typename T>
    inline T* getOption(const char* var){
        return (T*)(m_options.at((std::string&)(var)));
    }
protected:
    void Init(std::string&);
    int parseData();
    int parseVector(std::vector<std::string>&,std::vector<uint64>&);
    int parseMap(std::map<std::string,std::string>&,std::map<std::string,uint64>&);
private:
    std::string m_filename;
    std::map<std::string,uint64> m_options;
    std::string m_raw_data;
    bool m_ready;
};



#endif /* SRC_CONFIG_H_ */

