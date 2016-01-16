/*
 * Config.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: tyler
 */

#include <cassert>
#include <iostream>
#include <fstream>
#include "Config.h"
#include "help.h"

Config::Config():
    m_filename(""),
    m_options(),
    m_raw_data(""),
    m_ready(false)
{ }

Config::Config(std::string& filename):
    m_filename(""),
    m_options(),
    m_raw_data(""),
    m_ready(false)
{
    Init(filename);
}

Config::Config(const char* filename):
    m_filename(""),
    m_options(),
    m_raw_data(""),
    m_ready(false)
{
    Init((std::string&)(filename)); // Cast it to a string, rather than pass it to a constructor. wut.
}

int Config::Init(std::string& filename){
    std::ifstream file(filename.c_str());
    if(file){
        file.seekg(0,file.end);
        int length = file.tellg();
        file.seekg(0,file.beg);

        char* buffer = new char[length];
        file.read(buffer,length);

        m_raw_data = buffer;

        delete[] buffer;
    }else{
        return 1;
    }
    if(parseData())
        return 1;
    m_ready = true;
    return 0;
}

int Config::parseData(){
    std::vector<std::string> v;
    help::strings::split(m_raw_data,'\n',v);
    for(auto& line : v){
        help::strings::trim(line,line);

        std::vector<std::string> varval;
        help::strings::split(line,'=',varval);

        if(help::is::isInt(varval.at(1))){
            m_options[varval[0]] = (uint64)(help::convert::toInt(varval[1]));
        }else if(help::is::isFloat(varval.at(1))){
            m_options[varval[0]] = (uint64)(help::convert::toFloat(varval[1])*UINT64_MAX);
        }else if(help::is::isBool(varval.at(1))){
            m_options[varval[0]] = (uint64)(help::convert::toBool(varval[1]));
        }else if(help::is::isString(varval.at(1))){
            std::string s = (varval.at(1).substr(1,varval.at(1).size()-1));
            m_options[varval[0]] = reinterpret_cast<uint64>(&s);
        }else if(help::is::isVector(varval.at(1))){
            std::vector<std::string> nv;
            std::vector<uint64> nnv;
            help::convert::toVector(varval.at(1),nv);
            parseVector(nv,nnv);
            m_options[varval[0]] = reinterpret_cast<uint64>(&nv);
        }else if(help::is::isMap(varval.at(1))){
            std::map<std::string,std::string> m;
            std::map<std::string,uint64> nm;
            help::convert::toMap(varval.at(1),m);
            parseMap(m,nm);
            m_options[varval[0]] = reinterpret_cast<uint64>(&nm);
        }else{
            m_options[varval[0]] = reinterpret_cast<uint64>(&varval.at(1));
        }
    }
    return 0;
}

int Config::parseMap(std::map<std::string,std::string>& map,std::map<std::string,uint64>& newmap){
    for(std::map<std::string,std::string>::iterator it = map.begin();it != map.end();it++){
        std::string var = it->first;
        std::string val = it->second;
        if(help::is::isInt(val)){
            newmap[var] = (uint64)(help::convert::toInt(val));
        }else if(help::is::isFloat(val)){
            newmap[var] = (uint64)(help::convert::toFloat(val)*UINT64_MAX);
        }else if(help::is::isBool(val)){
            newmap[var] = (uint64)(help::convert::toBool(val));
        }else if(help::is::isString(val)){
            std::string s = (val.substr(1,val.size()-1));
            newmap[var] = reinterpret_cast<uint64>(&s);
        }else if(help::is::isVector(val)){
            std::vector<std::string> nv;
            std::vector<uint64> nnv;
            help::convert::toVector(val,nv);
            parseVector(nv,nnv);
            newmap[var] = reinterpret_cast<uint64>(&nv);
        }else if(help::is::isMap(val)){
            std::map<std::string,std::string> m;
            std::map<std::string,uint64> nm;
            help::convert::toMap(val,m);
            parseMap(m,nm);
            newmap[var] = reinterpret_cast<uint64>(&nm);
        }else{
            newmap[var] = reinterpret_cast<uint64>(&val);
        }
    }
    return 0;
}

int Config::parseVector(std::vector<std::string>& vector,std::vector<uint64>& newvector){
    for(auto& elem : vector){
        if(help::is::isInt(elem)){
            newvector.push_back((uint64)(help::convert::toInt(elem)));
        }else if(help::is::isFloat(elem)){
            newvector.push_back((uint64)(help::convert::toFloat(elem)*UINT64_MAX));
        }else if(help::is::isBool(elem)){
            newvector.push_back((uint64)(help::convert::toBool(elem)));
        }else if(help::is::isString(elem)){
            std::string s = (elem.substr(1,elem.size()-1));
            newvector.push_back(reinterpret_cast<uint64>(&s));
        }else if(help::is::isVector(elem)){
            std::vector<std::string> nv;
            std::vector<uint64> nnv;
            help::convert::toVector(elem,nv);
            parseVector(nv,nnv);
            newvector.push_back(reinterpret_cast<uint64>(&nv));
        }else if(help::is::isMap(elem)){
            std::map<std::string,std::string> m;
            std::map<std::string,uint64> nm;
            help::convert::toMap(elem,m);
            parseMap(m,nm);
            newvector.push_back(reinterpret_cast<uint64>(&nm));
        }else{
            newvector.push_back(reinterpret_cast<uint64>(&elem));
        }
    }
    return 0;
}

