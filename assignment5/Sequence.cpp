
#include "Sequence.h"


Sequence::Sequence(const string& adding){
    //inbetween ;'s are expressions
    addTo(adding);
}

void Sequence::addTo(const string& adding){
    //for every expression in the string
    //; divider
    original = adding;
    ifError = false;
    int size = adding.length();
    int pos = 0;
    while(pos < size){
        int end = adding.find_first_of(";", pos);
        //error checking for if delimiter is on end
        if(end != string::npos){
            string one_expr = adding.substr(pos, end-pos);
            Expression new_expression = Expression(one_expr);
            if(new_expression.getType() != 2){
                exps.push_back(new_expression);
                pos = end + 1;
            }
            else{
                error = new_expression.errorMessage();
                ifError = true;
                break;
            }
        }
        else{
            error = "Missing delimiter \';\' at end of Expression";
            ifError = true;
            break;
        }
    }
}

void Sequence::clear(){
    exps.clear();
    eval.clear();
    mapped.clear();
    parenth.clear();
    original = "";
    error = "";
    ifError = 0;
}

string Sequence::getOrig(){
    return original;
}

void Sequence::outPrefix(){
    int size = exps.size();
    for(int i = 0; i < size; i++){
        if(exps[i].getType() == 1){
            cout << "The prefix of ";
            int inf_size = exps[i].get_tokenized().size();
            int pref_size = exps[i].get_prefix().size();
            for(int j = 0; j < inf_size; j++)
                cout << exps[i].get_tokenized()[j].get_token() << " ";

            cout << " is ";
            for(int j = 0; j < pref_size; j++)
                cout << exps[i].get_prefix()[j].get_token() << " ";

            cout << endl;
        }
        else if(exps[i].getType() == 2){
            cout << exps[i].errorMessage() << endl;
        }
    }
}

void Sequence::outPostfix(){
    int size = exps.size();
    for(int i = 0; i < size; i++){
        if(exps[i].getType() == 1){
            cout << "The postfix of ";
            int inf_size = exps[i].get_tokenized().size();
            int pref_size = exps[i].get_postfix().size();
            for(int j = 0; j < inf_size; j++)
                cout << exps[i].get_tokenized()[j].get_token() << " ";

            cout << " is ";
            for(int j = 0; j < pref_size; j++)
                cout << exps[i].get_postfix()[j].get_token() << " ";

            cout << endl;
        }
        else if(exps[i].getType() == 2){
            cout << exps[i].errorMessage() << endl;
        }
    }
}

void Sequence::evaluate(){
    int size = exps.size();
    bool todo = 1;
    map<string, int> assign;
    stack<int> values;
    
    //assign all the variables with values in map, most efficient data structure
    for(int i = 0; i < size; i++){
        if(exps[i].getType() == 0){
            //sets the assignment variables to values
            int num = exps[i].get_tokenized()[2].value();
            string token = exps[i].get_tokenized()[0].get_token();
            assign [ token ] = num;
        }
    }
    
    mapped.resize(size);
    
    //put the answers into evaluate vector
    for(int i = 0; i < size; i++){      //goes through expression vector
        if(exps[i].getType() == 1){     //if type is arithmetic
            int exp_size = exps[i].get_postfix().size();
            //goes through expression
            for(int j = 0; j < exp_size; j++){
                //if is operator
                if(exps[i].get_postfix()[j].get_type() == 2){
                    int first = values.top();
                    values.pop();
                    int second = values.top();
                    values.pop();
                    
                    switch(exps[i].get_postfix()[j].get_token()[0]){
                        case '+':
                            values.push(second + first);
                            break;
                        case '-':
                            values.push(second - first);
                            break;
                        case '/':
                            if(second == 0){
                                cout << "Can't divide by zero";
                                break;
                            }
                            values.push(second / first);
                            break;
                        case '*':
                            values.push(second * first);
                            break;
                        case '%':
                            values.push(second % first);
                            break;
                    }
                }
                //if is number
                else if(exps[i].get_postfix()[j].get_type() == 1){
                    values.push(exps[i].get_postfix()[j].value());
                }
                
                //if variable
                else if(exps[i].get_postfix()[j].get_type() == 0){
                    //get from map then push
                    if(assign.find(exps[i].get_postfix()[j].get_token()) == assign.end()){
                        //error
                        mapped[i] = "No assignment of variable: " + exps[i].get_postfix()[j].get_token();
                        todo = 0;
                        break;
                    }
                    else{
                        values.push(assign[ exps[i].get_postfix()[j].get_token() ]);
                    }
                }
            }
                        
            if(todo){
                //last entry is answer
                eval.push_back(values.top());
                values.pop();
                todo = 1;
            }
            else{
                while(!values.empty())
                    values.pop();
            }
           
        }
        else if(exps[i].getType() == 2){
            error = "Cannot Evaluate " + exps[i].get_original() + " which is invalid expression.\n";
        }
    }
}

void Sequence::parenthesize(){
    stack<string> par;
    int size = exps.size();
    
    //put the answers into evaluate vector
    for(int i = 0; i < size; i++){      //goes through expression vector
        if(exps[i].getType() == 1){     //if type is arithmetic
            int exp_size = exps[i].get_postfix().size();
            //goes through expression
            for(int j = 0; j < exp_size; j++){
                //if is operator
                if(exps[i].get_postfix()[j].get_type() == 2){
                    string par1 = par.top();
                    par.pop();
                    string par2 = par.top();
                    par.pop();
                    
                    switch(exps[i].get_postfix()[j].get_token()[0]){
                        case '+':
                            par.push("(" + par2 + "+" + par1 + ")");
                            break;
                        case '-':
                            par.push("(" + par2 + "-" + par1 + ")");
                            break;
                        case '/':
                            par.push("(" + par2 + "/" + par1 + ")");
                            break;
                        case '*':
                            par.push("(" + par2 + "*" + par1 + ")");
                            break;
                        case '%':
                            par.push("(" + par2 + "%" + par1 + ")");
                            break;
                    }
                }
                //if is number
                else if(exps[i].get_postfix()[j].get_type() == 1){
                    par.push(exps[i].get_postfix()[j].get_token());
                }
                //variable
                else if(exps[i].get_postfix()[j].get_type() == 0){
                    par.push(exps[i].get_postfix()[j].get_token());
                }
            }
            
            parenth.push_back(par.top());
            par.pop();
           
        }
        else if(exps[i].getType() == 2){
            error = "Cannot Evaluate " + exps[i].get_original() + " which is invalid expression.\n";
        }
    }
}

void Sequence::outEvaluate(){
    int size = exps.size();
    int j = 0;
    evaluate();
    
    for(int i = 0; i < size; i++){
        //if arithmetic
        if(mapped[i] == ""){
            if(exps[j].getType() == 1){
                cout << exps[i].get_original() << " = " << eval[j] << endl;
                j++;
            }
            //if invalid
            else if(exps[j].getType() == 2){
                cout << "Invalid expression: " + exps[i].get_original() << endl;
                j++;
            }
        }
        else{
            cout << mapped[i] << endl;
        }
    }
}

void Sequence::outParenth(){
    int size = exps.size();
    int j = 0;
    parenthesize();
    
    for(int i = 0; i < size; i++){
        //if arithmetic
        if(exps[i].getType() == 1){
            cout << exps[i].get_original() << " fully parenthesized is " << parenth[j] << endl;
            j++;
        }
        //if invalid
        else if(exps[i].getType() == 2){
            cout << exps[i].errorMessage();
        }
    }
}

void Sequence::getError(){
    cout << error << endl << endl;
}

bool Sequence::isError(){
    return ifError;
}
