/*
 * RobotVikings
 * help.cpp
 * 12/6/15
 * Defines help functions to help with whatever we may need them for.
 */

#include <cassert>
#include <cmath>
#include "help.h"

using namespace help;

int misc::range(int start,int stop,int step,std::vector<int>& store){
    for(int i=start;i<stop;i+=step){
        store.push_back(i);
    }
    return 0;
}

int misc::range(int start,int stop,std::vector<int>& store){
    return misc::range(start,stop,1,store);
}

int misc::range(int stop,std::vector<int>&store){
    return misc::range(0,stop,store);
}

int strings::split(std::string& str, char delim, std::vector<std::string>& store){
	return strings::split(str,delim,str.find_last_not_of(delim),store);
}

int strings::split(std::string& str, char delim, int n, std::vector<std::string>& store){
    size_t i=0;
    std::string fstr = str.substr(); // get a copy of str
    while(i!=std::string::npos){
        i=fstr.find(',',i); // Find the next ','
        store.push_back(fstr.substr(i,fstr.find(',',i)-1)); // add substring of element to vector (chop off ',')
    }
	return 0;
}

int convert::toInt(char c){
    assert(c < '9' && c > '0');
    return (int)(c)-'0';
}

int convert::toInt(std::string& str){
    size_t i=0; // start
    int s=1; // sign
    int t=0; // total
    int p=1; // place
    if(str.at(0)=='-'){
        i=1;
        s=-1;
    }
    for(;i<str.size();i++){
        t+=convert::toInt(str.at(i))*p;
        p*=10;
    }
    t*=s;
    return t;
}

// Split at decimal point, divide 1 by the second half, and add the two halves together
float convert::toFloat(std::string& str){
    size_t d=str.find('.');
    std::string s1 = str.substr(0,d-1); // Make sure we don't include the decimal point
    std::string s2 = str.substr(d+1); // Make sure we don't include the decimal point
    // Is this needed?
    // int p = 1/pow(10,s2.size()); // p=1^-x
    return (toInt(s1)+(1/toInt(s2)));
}

bool convert::toBool(std::string& str){
    if(str.compare("true") == 0){
        return true;
    }else if(str.compare("false") == 0){
        return false;
    }else{
        assert(false&&"str must == 'true' or 'false'!"); // Fail
    }
    return false; // This will never execute, but it is here to satisfy the compiler.
}

int convert::toVector(std::string& str,std::vector<std::string>& v){
//    size_t i=0;
    std::string n = str.substr(1,str.size()-1); // Chop off [ and ]
//    while(i!=std::string::npos){
//        i=n.find(',',i); // Find the next ','
//        v.push_back(str.substr(i,n.find(',',i)-1)); // add substring of element to vector (chop off ',')
//    }
    return strings::split(n,',',v);
}

int convert::toMap(std::string& str,std::map<std::string,std::string>& m){
    // Disable the Disabler (Troll Lv30.)
    //assert(!"WARNING! THIS FUNCTION IS NOT FINISHED YET");
    size_t i=0;
    size_t x=0;
    std::string n = str.substr(1,str.size()-1); // Chop off { and }
    while(i!=std::string::npos){
        i=n.find(',',i); // Find the next ','
        // get the next set (this is wrong, fix it) Did I fix it yet? Can somebody check for me?
        std::string set = n.substr(i-1,x);
        x=i;
        m.at(set.substr(0,set.find(':')-1)) = set.substr(set.find(':')+1); // Get key and set it to value in m
    }
    return 0;
}

bool is::isInt(char c){
	return (c<'9' || c>'0'); // is c a number (all 'number' characters are between 0 and 9
}
bool is::isInt(std::string& str){
	size_t i=0;
	if(str.at(0) == '-' || isInt(str.at(0)))
		i=1;
	for(;i<str.size();i++) // For every character
		if(!isInt(str.at(i)))
			return false;
	return true;
}
bool is::isFloat(std::string& str){
	size_t i=0;
	if(str.at(0) == '-' || isInt(str.at(0)))
		i=1;
	for(;i<str.size();i++)
		if(!isInt(str.at(i)))
			if(str.at(i) != '.') // If it isn't a number or a '.'
				return false;
	return true;
}
bool is::isBool(std::string& str){
	return (str.compare("true") || str.compare("false"));
}
bool is::isString(std::string& str){
	return (str.at(0) == '"' && str.at(str.size()-1) == '"');
}
bool is::isVector(std::string& str){
	return (str.at(0) == '[' && str.at(str.size()-1) == ']') ||
			(str.at(0) == '(' && str.at(str.size()-1) == ')');
}
bool is::isMap(std::string& str){
	return (str.at(0) == '{' && str.at(str.size()-1) == '}');
}
