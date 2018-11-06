/* 
 * File:   Token.cpp
 * Author: John Connolly
 *
 * Created on September 20, 2017, 3:24 PM
 */

#include "Token.h"

Token::Token(){
    //default sets type and prioirty
    type = invalid;
    priority = -1;
}

Token::Token(string s){
    set(s);
}

void Token::set(string s){
    priority = -1;
    token = s;
    
    if(token == "="){
        type = equals;
    }
    else if(token == "("){
        type = openbrace;
    }
    else if(token == ")"){
        type = closebrace;
    }
    //checks if first character is letter
    else if(isalpha(token[0])){
        //goes through string and checks if everything else is either digit or letter
        for(int i = 0; i < token.size(); i++){
            if(!isalpha(token[i]) && !isdigit(token[i])){
                type = invalid;
                break;
            }
            type = identifier;
        }
        
    }
    //checks if interger starts with a 0
    else if (token[0] == '0'){
        type = invalid;
    }
    //if everything is an integer then type is integer
    else if(token.find_first_not_of("0123456789") == std::string::npos){
        type = integer;
    }
    //checks operators
    else if(token == "+", "-", "*", "/", "%"){
        type = operators;
    }
    else{
        type = invalid;
    }
}

int Token::value() const{
    if(type == identifier || type == invalid){
        return -1;
    }
    if(type == integer){
        //returns the integer value of string
        return atoi(token.c_str());
    }
    
    return -1;
}

void Token::display() const{
    //sets enum numbers to actual words
    string str_typ = "invalid";
    if(type == 0)
        str_typ = "identifier";
    if(type == 1)
        str_typ = "integer";
    if(type == 2)
        str_typ = "operators";
    if(type == 3)
        str_typ = "equals";
    if(type == 4)
        str_typ = "openbrace";
    if(type == 5)
        str_typ = "closebrace";
    if(type == 6)
        str_typ = "invalid";
    
    //outputs
    cout << "type = " << str_typ << endl
         << "token = " << token <<endl
         << "priority = " << priority << endl;
}

Token_type Token::get_type() const{
    return type;
}

string Token::get_token() const{
    return token;
}

int Token::get_priority() const{
    return priority;
}

