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
