/* 
 * File:   Sequence.h
 * Author: John Connolly
 *
 * Created on November 18, 2017, 5:50 PM
 */

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Expression.h"

using namespace std;

class Sequence{
    public:
        //don't need base constructor, nothing to initialize
        Sequence(const string&);
        bool isError();
        void clear();
        void addTo(const string&);
        void outPrefix();
        void outPostfix();
        void outEvaluate();
        void outParenth();
        void evaluate();
        void parenthesize();
        void getError();
        string getOrig();

    private:
        string error;
        string original;
        bool ifError;
        vector<Expression> exps;
        vector<int> eval;
        vector<string> parenth;
        vector<string> mapped;
};

#endif /* SEQUENCE_H */


