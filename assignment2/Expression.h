/* 
 * File:   Expression.h
 * Author: John Connolly
 *
 * Created on September 20, 2017, 3:24 PM
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>
#include <vector>
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
        string get_original() const;
        vector<Token> get_tokenized() const;
        
    private:
        string original;
        vector<Token> tokenized;
        vector<Token> postfix;
        bool valid;
        Exp_type type;
};

#endif /* EXPRESSION_H */


