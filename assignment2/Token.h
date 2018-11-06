/* 
 * File:   Token.h
 * Author: John Connolly
 *
 * Created on September 20, 2017, 3:23 PM
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

//declaration of enums
//changed equal to equals to stop errors from occuring with "std::equal" function
enum Token_type {identifier, integer, operators, equals, openbrace, closebrace, invalid};

class Token{
    public:
        Token();
        Token(string);
        void set(string);
        int value() const;
        void display() const;
        Token_type get_type() const;
        string get_token() const;
        int get_priority() const;
        
    private:
        Token_type type;
        string token;
        int priority;
};

#endif /* TOKEN_H */


