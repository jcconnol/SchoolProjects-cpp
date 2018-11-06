/* 
 * File:   Expression.cpp
 * Author: John Connolly
 *
 * Created on November 8, 2017, 3:11 PM
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

Exp_type Expression::getType(){
    return type;
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
    
    //setup the postfix vector
    setType();
    //only make arithmetic post and prefix and stuff
    if(type == 1){
        setPostfix();
        setPrefix();
    }
}

bool Expression::isvalid(){
    return valid;
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

//could do this for every expression in the sequence class or just do it here
void Expression::setPostfix(){
    stack<Token> tack;
    int post_size = tokenized.size();
    for(int i = 0; i < post_size; i++){
        //if is operator
        if(tokenized[i].get_type() == 2,3){
            while(!tack.empty() && tack.top().get_type() != 4 && tack.top().get_priority() < tokenized[i].get_priority()){
                postfix.push_back(tack.top());
                tack.pop();
            }
            tack.push(tokenized[i]);
        }
        //if is operand or equals
        else if(tokenized[i].get_type() == 0,1){
            postfix.push_back(tokenized[i]);
        }
        //if is open parenthesis
        else if(tokenized[i].get_type() == 4){
            tack.push(tokenized[i]);
        }
        //else if close parenthesis
        else if(tokenized[i].get_type() == 5){
            while(!tack.empty() && tack.top().get_type() != 4){
                postfix.push_back(tack.top());
                tack.pop();
            }
            tack.pop();
        }
    }

    while(!tack.empty()){
        postfix.push_back(tack.top());
        tack.pop();
    }
}

//could do this for every expression in the sequence class or just do it here
void Expression::setPrefix(){
    stack<Token> tack;
    int pre_size = tokenized.size();

    reverse(tokenized.begin(), tokenized.end());

    for(int i = 0; i < pre_size; i++){
        //if is operator
        if(tokenized[i].get_type() == 2,3){
            while(!tack.empty() && tack.top().get_priority() >= tokenized[i].get_priority()){
                prefix.push_back(tack.top());
                tack.pop();
            }
            tack.push(tokenized[i]);
        }
        //if is operand
        else if(tokenized[i].get_type() == 0,1){
            prefix.push_back(tokenized[i]);
        }
        //if is open parenthesis
        else if(tokenized[i].get_type() == 4){
            tack.push(tokenized[i]);
        }
        //else if close parenthesis
        else if(tokenized[i].get_type() == 5){
            while(!tack.empty() && tack.top().get_type() != 4){
                prefix.push_back(tack.top());
                tack.pop();
            }
            tack.push(tokenized[i]);
        }
        //invalid
        else{
            break;
        }
    }

    while(!tack.empty()){
        prefix.push_back(tack.top());
        tack.pop();
    }

    reverse(tokenized.begin(), tokenized.end());
}

void Expression::setType(){
    //set type and valid bool
    //if only size 3, first is variables, 2nd is = and third is number
    if(tokenized.size() == 3 && tokenized[1].get_type() == 3 && tokenized[0].get_type() == 0 && tokenized[2].get_type() == 1){
        valid = true;
        type = assignment;
    }
    else{
        //check is expression is correct
        int size = tokenized.size();
        int paren = 0;
        for(int i = 0; i < size; i++){
            if(tokenized[i].get_type() == 5){
                paren--;
            }
            else if(tokenized[i].get_type() == 4){
                paren++;
            }
        }
        for(int i = 0; i < size-1; i++){
            //go through expression, check for errors
            if(tokenized[i].get_type() == 0,1 && (tokenized[i+1].get_type() == 2 || tokenized[i+1].get_type() == 5)){
                valid = true;
            }
            else if(tokenized[i].get_type() == 2 && (tokenized[i+1].get_type() == 0,1 || tokenized[i+1].get_type() == 4)){
                valid = true; 
            }
            else if(tokenized[i].get_type() == 4 && tokenized[i+1].get_type() == 0,1){
                valid = true;
            }
            else{
                valid = false;
                stringstream s;
                s << i;
                error = "Character at position " + s.str() + " is missing or invalid";
                break;
            }
        }
        if(isvalid() && paren == 0){
            if(tokenized[size-1].get_type() != 0 && tokenized[size-1].get_type() != 1 && tokenized[size-1].get_type() != 5 && valid){
                error = "Final character: \'" + tokenized[size-1].get_token() + "\', is invalid";
                type = illegal;
                valid = false;
            }
            else
                type = arithmetic;
        }
        else if(isvalid() && paren < 0){
            error = "A close parenthesis has no opening one";
            type = illegal;
        }
        else if(isvalid() && paren > 0){
            error = "An open parenthesis has no closing one";
            type = illegal;
        }
        else{
            type = illegal;
            error = "Invalid Expression: " + original;
        }
    }
}

string Expression::errorMessage(){
    return error;
}

void Expression::clear(){
    if(!postfix.empty())
        postfix.clear();
    
    if(!prefix.empty())
        prefix.empty();
    
    if(!tokenized.empty())
        tokenized.clear();
    
    if(original != "")
        original = "";
}

string Expression::get_original() const{
    return original;
}

vector<Token> Expression::get_postfix() const{
    return postfix;
}

vector<Token> Expression::get_prefix() const{
    return prefix;
}

vector<Token> Expression::get_tokenized() const{
    return tokenized;
}
