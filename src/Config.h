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
#include "structs.h"

//static const uint64 UINT64_MAX = (0-1);
typedef std::map<std::string,Iproxy*> opt_map;

class Config{
public:
    Config(std::string&);
    Config(const char*);
    Config();

    //inline std::map<std::string,uint64> getOptions(){ return this->m_options; };
    inline opt_map getOptions(){ return this->m_options; };

    /*
    template<typename T>
    inline T* getOption(std::string& var){
        if(m_options.find(var) != m_options.end())
            return (T*)(m_options.at(var));
        return NULL;
    }

    template<typename T>
    inline T* getOption(const char* var){
        if(m_options.find((std::string&)(var)) != m_options.end())
            return (T*)(m_options.at((std::string&)(var)));
        return NULL;
    }
    */

    inline Iproxy* getOption(const char* var){
        if(m_options.find((std::string&)var) != m_options.end())
            return m_options.at((std::string&)var);
        return NULL;
    }

    inline Iproxy* getOption(std::string& var){
        if(m_options.find(var) != m_options.end())
            return m_options.at(var);
        return NULL;
    }

    int Init(std::string&);
protected:
    int parseData();
    int parseVector(std::vector<std::string>&,std::vector<Iproxy*>&);
    int parseMap(std::map<std::string,std::string>&,opt_map&);
private:
    std::string m_filename;
    //std::map<std::string,uint64> m_options;
    opt_map m_options;
    std::string m_raw_data;
    bool m_ready;
};



#endif /* SRC_CONFIG_H_ */

