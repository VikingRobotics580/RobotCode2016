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
#include "macros.h"
#include "structs.h"

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
    if(Init(filename))
        std::cout << "An error occurred during Init("<<filename<<");"<<std::endl;
}

Config::Config(const char* filename):
    m_filename(""),
    m_options(),
    m_raw_data(""),
    m_ready(false)
{
    if(Init((std::string&)(filename))) // Cast it to a string, rather than pass it to a constructor. wut.
        std::cout << "An error occurred during Init("<<filename<<");"<<std::endl;
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
    std::cout << "split(m_raw_data,'\\n',v)" << std::endl;
    help::strings::split(m_raw_data,'\n',v);
    for(auto& line : v){
        std::cout << "line=" << line << std::endl;
        std::cout << "trim(line,line)" << std::endl;
        help::strings::simple_trim(line,line);
        std::cout<< "line=" << line << std::endl;

        if(line == ""||line.at(0) == '@') continue;

        std::vector<std::string> varval;
        std::cout << "split(line,'=',varval)"<<std::endl;
        help::strings::split(line,'=',varval);

        // Trim each side
        help::strings::simple_trim(varval.at(0),varval.at(0));
        help::strings::simple_trim(varval.at(1),varval.at(1));

        std::cout << varval.at(0) << " is " << varval.at(1) << std::endl;

        if(help::is::isInt(varval.at(1))){
            //m_options[varval[0]] = (uint64)(help::convert::toInt(varval[1]));
            m_options[varval[0]] = new proxy<int>(help::convert::toInt(varval[1]));
        }else if(help::is::isFloat(varval.at(1))){
            //m_options[varval[0]] = (uint64)(help::convert::toFloat(varval[1])*UINT64_MAX);
            m_options[varval[0]] = new proxy<float>(help::convert::toFloat(varval[1]));
        }else if(help::is::isBool(varval.at(1))){
            //m_options[varval[0]] = (uint64)(help::convert::toBool(varval[1]));
            m_options[varval[0]] = new proxy<bool>(help::convert::toBool(varval[1]));
        }else if(help::is::isString(varval.at(1))){
            std::cout << "varval.at(1).substr(1)" << std::endl;
            std::string s = (varval.at(1).substr(1));//,varval.at(1).size()-1));
            //m_options[varval[0]] = reinterpret_cast<uint64>(&s);
            m_options[varval[0]] = new proxy<std::string>(s);
        }else if(help::is::isVector(varval.at(1))){
            std::vector<std::string> nv;
            std::vector<Iproxy*> nnv;
            help::convert::toVector(varval.at(1),nv);
            parseVector(nv,nnv);
            //m_options[varval[0]] = reinterpret_cast<uint64>(&nv);
            m_options[varval[0]] = new proxy<std::vector<Iproxy*>>(nnv);
        }else if(help::is::isMap(varval.at(1))){
            std::map<std::string,std::string> m;
            std::map<std::string,Iproxy*> nm;
            help::convert::toMap(varval.at(1),m);
            parseMap(m,nm);
            //m_options[varval[0]] = reinterpret_cast<uint64>(&nm);
            m_options[varval[0]] = new proxy<std::map<std::string,Iproxy*>>(nm);
        }else{
            //m_options[varval[0]] = reinterpret_cast<uint64>(&varval.at(1));
            m_options[varval[0]] = new proxy<std::string>(varval.at(1));
        }
    }
    return 0;
}

int Config::parseMap(std::map<std::string,std::string>& map,std::map<std::string,Iproxy*>& newmap){
    for(std::map<std::string,std::string>::iterator it = map.begin();it != map.end();it++){
        std::string var = it->first;
        std::string val = it->second;
        if(help::is::isInt(val)){
            newmap[var] = new proxy<int>(help::convert::toInt(val));//(uint64)(help::convert::toInt(val));
        }else if(help::is::isFloat(val)){
            newmap[var] = new proxy<float>(help::convert::toFloat(val)); //(uint64)(help::convert::toFloat(val)*UINT64_MAX);
        }else if(help::is::isBool(val)){
            newmap[var] = new proxy<bool>(help::convert::toBool(val));//(uint64)(help::convert::toBool(val));
        }else if(help::is::isString(val)){
            std::string s = (val.substr(1,val.size()-1));
            //newmap[var] = reinterpret_cast<uint64>(&s);
            newmap[var] = new proxy<std::string>(s);
        }else if(help::is::isVector(val)){
            std::vector<std::string> nv;
            std::vector<Iproxy*> nnv;
            help::convert::toVector(val,nv);
            parseVector(nv,nnv);
            //newmap[var] = reinterpret_cast<uint64>(&nv);
            newmap[var] = new proxy<std::vector<Iproxy*>>(nnv);
        }else if(help::is::isMap(val)){
            std::map<std::string,std::string> m;
            std::map<std::string,Iproxy*> nm;
            help::convert::toMap(val,m);
            parseMap(m,nm);
            //newmap[var] = reinterpret_cast<uint64>(&nm);
            newmap[var] = new proxy<std::map<std::string,Iproxy*>>(nm);
        }else{
            //newmap[var] = reinterpret_cast<uint64>(&val);
            newmap[var] = new proxy<std::string>(val);
        }
    }
    return 0;
}

int Config::parseVector(std::vector<std::string>& vector,std::vector<Iproxy*>& newvector){
    for(auto& elem : vector){
        if(help::is::isInt(elem)){
            //newvector.push_back((uint64)(help::convert::toInt(elem)));
            newvector.push_back(new proxy<int>(help::convert::toInt(elem)));
        }else if(help::is::isFloat(elem)){
            //newvector.push_back((uint64)(help::convert::toFloat(elem)*UINT64_MAX));
            newvector.push_back(new proxy<float>(help::convert::toFloat(elem)));
        }else if(help::is::isBool(elem)){
            //newvector.push_back((uint64)(help::convert::toBool(elem)));
            newvector.push_back(new proxy<bool>(help::convert::toBool(elem)));
        }else if(help::is::isString(elem)){
            std::string s = (elem.substr(1,elem.size()-1));
            //newvector.push_back(reinterpret_cast<uint64>(&s));
            newvector.push_back(new proxy<std::string>(s));
        }else if(help::is::isVector(elem)){
            std::vector<std::string> nv;
            std::vector<Iproxy*> nnv;
            help::convert::toVector(elem,nv);
            parseVector(nv,nnv);
            //newvector.push_back(reinterpret_cast<uint64>(&nv));
            newvector.push_back(new proxy<std::vector<Iproxy*>>(nnv));
        }else if(help::is::isMap(elem)){
            std::map<std::string,std::string> m;
            std::map<std::string,Iproxy*> nm;
            help::convert::toMap(elem,m);
            parseMap(m,nm);
            //newvector.push_back(reinterpret_cast<uint64>(&nm));
            newvector.push_back(new proxy<std::map<std::string,Iproxy*>>(nm));
        }else{
            //newvector.push_back(reinterpret_cast<uint64>(&elem));
            newvector.push_back(new proxy<std::string>(elem));
        }
    }
    return 0;
}

