/*
 * RobotVikings
 * help.h
 * 12/6/15
 * Declares helper functions to help with whatever we may need.
 */

#ifndef _HELP_H_
#define _HELP_H_

#include <math_help.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <locale>
#include <cctype>

#include "macros.h"

namespace help{
 // Make it so that the "math" namespace is inside help. This is allowed according to Standard C++ 7.3.2/3. Fite me.
 namespace math = math_help;

 namespace misc{
  /*
   * range
   * Accepts an int (stop) and a vector<int> (store)
   * Returns an int as status (0 upon success, 1 upon failure)
   * Creates a range of ints from 0 to stop and stores them in store.
   * Example:
   * stop=5
   * 0,1,2,3,4
   */
  inline int range(int,std::vector<int>&);

  /*
   * range
   * Accepts an int (start), an int (stop) and a vector<int> (store)
   * Returns an int as status (0 upon success, 1 upon failure)
   * Creates a range of ints from start to stop and stores them in store.
   * Example:
   * start=1,stop=5
   * 1,2,3,4
   */
  inline int range(int,int,std::vector<int>&);

  /*
   * range
   * Accepts an int (start), an int (stop), an int (step) and a vector<int> (store)
   * Returns an int as status (0 upon success, 1 upon failure)
   * Creates a range of ints from start to stop, every step and stores them in store.
   * Example:
   * start=1,stop=5,step=2
   * 1,3
   */
  int range(int,int,int,std::vector<int>&);

 }
 namespace strings{
  /*
   * split
   * Accepts a string (str), a char (delimiter), and a vector<std::string&> (store)
   * Returns an int as status (0 upon success, 1 upon failure)
   * Splits a string str by delim and stores them in a vector store
   * Example:
   * str="hello,there",delim=','
   * ["hello","there"]
   */
  int split(std::string&,char,std::vector<std::string>&);

  /*
   * split
   * Accepts a string (str), a char (delimiter), an int (n), and a vector<std::string&> (store)
   * Returns an int as status (0 upon success, 1 upon failure)
   * Splits a string str by delim and stores them in a vector store
   * Example:
   * str="hello,there,world",delim=',',n=1
   * ["hello","there,world"]
   */
  int split(std::string&,char,int,std::vector<std::string>&);

  /*
   * ltrim
   * Accepts a string
   * Returns a string
   * Trims all whitespace from the left side of the string
   */
  inline int ltrim(std::string& s,std::string& store){
      store = s.substr();
      // erase from beginning to first character that isn't a whitespace character
      // erase(pos,len) - erases all characters from pos to len
      //   pos is the start, len is
      // find_if(first,last,pred) - finds the first index between first and last where pred is true
      //  pred is
      // not1(pred) - returns the opposite of pred
      //  pred is
      // ptr_fun<class Arg, class Result>(f) - returns a function object of f, where f is a function
      //  pointer.
      // isspace - a function pointer which returns true if the passed in character is a whitespace char

      // For more information on how this works, look at the following links where I
      //  ~shamelessly copy pasted~ found this code.
      // http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
      // http://www.cplusplus.com/reference/string/string/erase/
      // http://www.cplusplus.com/reference/functional/ptr_fun/
      // http://www.cplusplus.com/reference/locale/isspace/
      // http://www.cplusplus.com/reference/functional/not1
      // http://www.cplusplus.com/reference/algorithm/find_if/
      // http://stackoverflow.com/questions/5921609/what-is-predicate-in-c
      store.erase(store.begin(),
              std::find_if(s.begin(),s.end(),
                      std::not1(std::ptr_fun<int,int>(std::isspace))
              )
      );
      return 0;
  }
  /*
   * rtrim
   * Accepts a string
   * Returns a string
   * Trims all whitespace from the right side of the string
   */
  inline int rtrim(std::string& s,std::string& store){
      store = s.substr();
      // previous stuff all compounded in one line.
      // forgive me for how hard this is to read.
      //  or don't, it's your choice.
      store.erase(std::find_if(s.rbegin(),s.rend(),std::not1(std::ptr_fun<int,int>(std::isspace))).base(),s.end());
      return 0;

      // Oh right, if you want explanation as to what the hell this does, look at ltrim.
  }
  /*
   * trim
   * Accepts a string
   * Returns a string
   * Trims all whitespace from both sides of the string
   */
  inline int trim(std::string& s,std::string& store){
    // To make sure we get a proper error value, create a special int, which uses bitwise or
    //  to ensure that both values return 0
    // We also need to send a temporary string to rtrim because the trim functions overwrite
    //  whatever is in store, meaning that it will disappear the instant it is sent to ltrim
    std::string nstore;
    int ret = strings::rtrim(s,nstore) | strings::ltrim(nstore,store);
    return ret;

    // P.S: Although, now that I'm thinking about it, we could just not have nstore and just pass
    //  nstore twice to ltrim.
    // Somebody else who wants to take a look at these, please consider this.
}
 }

 namespace is{
  /*
   * isType
   * Accepts a string
   * Returns a bool
   * Returns true if the passed string is the specified type. False otherwise.
   */
  bool isInt(char);
  bool isInt(std::string&);
  bool isFloat(std::string&);
  bool isBool(std::string&);
  bool isString(std::string&);
  bool isVector(std::string&);
  bool isMap(std::string&);
 }

 namespace convert{
 /*
  * toInt
  * Accepts a char
  * Returns an int
  * Converts the passed in char to an int. Will throw an assertion error if the passed string cannot be converted.
  */
  int toInt(char);

 /*
  * toInt
  * Accepts a string
  * Returns an int
  * Converts the passed in string to an int. Will throw an assertion error if the passed string cannot be converted.
  */
  int toInt(std::string&);

  /*
   * toFloat
   * Accepts a string
   * Returns a float
   * Converts the passed in string to a float. Will throw an assertion error if the passed string cannot be converted.
   */
  float toFloat(std::string&);

  /*
   * toBool
   * Accepts a string
   * Returns a bool
   * Converts the passed in string to a bool. Will throw an assertion error if the passed string cannot be converted.
   */
  bool toBool(std::string&);

  /*
   * toVector
   * Accepts a string and a vector
   * Returns an int as status (0 upon success and 1 upon failure)
   * Converts str to a vector of strings.
   * String example:
   *   [5,25,etc...]
   */
  int toVector(std::string&,std::vector<std::string>&);

  /*
   * toMap
   * Accepts a string and a map
   * Returns an int as status (0 upon success and 1 upon failure)
   * Converts str to a map<string,string>
   * String example:
   *   {foo:5,h:25,etc...}
   */
  int toMap(std::string&,std::map<std::string,std::string>&);
 }
}

#endif
