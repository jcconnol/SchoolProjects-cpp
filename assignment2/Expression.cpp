/* 
 * File:   Expression.cpp
 * Author: John Connolly
 *
 * Created on September 20, 2017, 3:24 PM
 */

#include "Expression.h"

Expression::Expression(){
    //default constructor
    original = "";
    valid = 0;
    type = illegal;
}

Expression::Expression(const string& s){
    set(s);
}

void Expression::set(const string& s){
    original = s;
    type = illegal;
    valid = 0;
    
    //
    int beg = 0;
    int i;
    string delim = " /%+)*-(=";
    string space = " ";
    for(i = 0; i < s.size(); i++){
        //finds delimiter
        string tok_part;
        if(delim.find(s[i]) != std::string::npos){
            //adds substring before delimiter to vector
            tok_part = s.substr(beg, i-beg);
            tok_part.erase(remove(tok_part.begin(), tok_part.end(), ' '), tok_part.end());
            if( space.find(tok_part) == std::string::npos){
                tokenized.push_back(Token(tok_part));
            }
            beg = i;
            //adds delimiter to vector then goes onto next
            tok_part = s.substr(beg, 1);
            tok_part.erase(remove(tok_part.begin(), tok_part.end(), ' '), tok_part.end());
            if(space.find(tok_part) == std::string::npos){
                tokenized.push_back(Token(tok_part));
                beg++;
            }
        }
    }
    
    //end error checking for if doesn't end in delimiter
    if(s.find_last_of(delim)+1 != s.size()){
        int last_pos = s.find_last_of(delim);
        string tok_part = s.substr(last_pos+1, s.size());
        tok_part.erase(remove(tok_part.begin(), tok_part.end(), ' '), tok_part.end());
        if(space.find(tok_part) == std::string::npos){
            tokenized.push_back(Token(tok_part));
        }
    }
}

void Expression::display() const{
    
    cout << "original = " << original << endl;
    cout << "tokenized = ";
    
    //cout empty if tokenized is empty
    if(tokenized.empty()){
        cout << "empty" << endl;
    }
    //outputs tokenized
    for(int i = 0; i < tokenized.size(); i++){
        cout << tokenized[i].get_token() << ";";
    }
    cout << endl;
    
    cout << "postfix = " << endl;
    for(int i = 0; i < postfix.size(); i++){
        postfix[i].display();
    }
    
    cout << "valid = " << valid << endl;
    
    //set enum numbers to actual words and outputs
    string str_typ = "illegal";
    if(type == 0)
        str_typ = "assignment";
    if(type == 1)
        str_typ = "arithmetic";
    
    cout << "type = " << str_typ << endl;
    cout << endl;
}

string Expression::get_original() const{
    return original;
}

vector<Token> Expression::get_tokenized() const{
    return tokenized;
}
