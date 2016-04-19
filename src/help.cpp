/*
 * RobotVikings
 * help.cpp
 * 12/6/15
 * Defines help functions to help with whatever we may need them for.
 */

#include <cassert>
#include <stdio.h>
#include <cstring>
#include <cmath>
#include <climits>

#include "help.h"
#include "types.h"

using namespace help;

// RANGE
int misc::range(int start,int stop,int step,std::vector<int>& store){
    for(int i=start;i<stop;i+=step){
        store.push_back(i);
    }
    return 0;
}

// STARTSWITH
bool strings::startswith(std::string& input, std::string& check){
    if(input.size() < check.size()) return false;
    for(size_t i=0;i<check.size();i++){
        if(input.at(i) != check.at(i)) return false;
    }
    return true;
}

bool strings::startswith(std::string& input, cstr check){
    if(input.size() < strlen(check)) return false;
    for(size_t i=0;i<strlen(check);i++){
        if(input.at(i) != check[i]) return false;
    }
    return true;
}

bool strings::startswith(cstr input, cstr check){
    if(strlen(input) < strlen(check)) return false;
    for(size_t i=0;i<strlen(check);i++){
        if(input[i] != check[i]) return false;
    }
    return true;
}

bool strings::startswith(cstr input, std::string& check){
    if(strlen(input) < check.size()) return false;
    for(size_t i=0;i<check.size();i++){
        if(input[i] != check.at(i)) return false;
    }
    return true;
}

// ENDSWITH
bool strings::endswith(std::string& input, std::string& check){
    if(input.size() < check.size()) return false;
    for(size_t i=check.size()-1;i>0;i--){
        if(input.at(input.size()-i) != check.at(i)) return false;
    }
    return true;
}

bool strings::endswith(std::string& input, cstr check){
    if(input.size() < strlen(check)) return false;
    for(size_t i=strlen(check)-1;i>0;i--){
        if(input.at(i) != check[i]) return false;
    }
    return true;
}

bool strings::endswith(cstr input, cstr check){
    if(strlen(input) < strlen(check)) return false;
    for(size_t i=strlen(check)-1;i>0;i--){
        if(input[strlen(input)-i] != check[i]) return false;
    }
    return true;
}

bool strings::endswith(cstr input, std::string& check){
    if(strlen(input) < check.size()) return false;
    for(size_t i=check.size();i>0;i++){
        if(input[strlen(input)-i] != check.at(i)) return false;
    }
    return true;
}

// SPLIT
int strings::split(std::string& str, char delim, std::vector<std::string>& store){
	return strings::split(str,delim,INT_MAX,store);
}

int strings::split(std::string& str, char delim, int limit, std::vector<std::string>& store){
    std::string fstr = str.substr();
    std::string nstr;
    size_t i=fstr.find(delim,0);
    int n2=0;

    while(i!=std::string::npos && n2!=limit){
        nstr = fstr.substr(0,i); // Get the next bit of the string
        log_test("store.push_back(nstr)");
        store.push_back(nstr);
        fstr = fstr.substr(i+1);
        i=fstr.find(delim,0);
        n2++;
    }

    log_test("store.push_back(fstr);");
    store.push_back(fstr); // Put whatever the last value is into store. This kills the off-by-one error.
    log_test("split(...) END");
    return 0;
}

// TOTYPE
int convert::toInt(char c){
    assert(c < '9' && c > '0');
    return (int)((c)-'0');
}

int convert::toInt(std::string& str){
    size_t i=0; // start
    int s=1; // sign
    int t=0; // total
    int p=1; // place
    log_test("str=%s",str.c_str());
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

// ISTYPE
bool is::isInt(char c){
	return (c<'9' && c>'0'); // is c a number (all 'number' characters are between 0 and 9
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
	return !(str.compare("true") || str.compare("false"));
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

