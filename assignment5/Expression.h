/* 
 * File:   Expression.h
 * Author: John Connolly
 *
 * Created on November 8, 2017, 3:11 PM
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Token.h"

using namespace std;

//declaration of enums
//are uppercase to be consistent with the Token class enums
enum Exp_type {assignment, arithmetic, illegal};

class Expression{
    public:
        Expression();
        Expression(const string&);
        void set(const string&);
        void display() const;
        string errorMessage();
        bool isvalid();
        void clear();
        Exp_type getType();
        string get_original() const;
        vector<Token> get_tokenized() const;
        vector<Token> get_postfix() const;
        vector<Token> get_prefix() const;
        
    private:
        void setPrefix();
        void setPostfix();
        void setType();
        
        string original;
        string error;
        vector<Token> tokenized;
        vector<Token> postfix;
        vector<Token> prefix;
        bool valid;
        Exp_type type;
};

#endif /* EXPRESSION_H */


