/* 
 * File:   main.cpp
 * Author: John Connolly
 *
 * Created on November 8, 2017, 3:09 PM
 */

#include <cstdlib>
#include "Token.h"
#include "Expression.h"
#include "Sequence.h"

using namespace std;

int main(int argc, char** argv) {
    
    cout << "=== Expression Evaluation Program Started ===" << endl;
    cout << "Expression Input: ";
    string input = "";
    string action = "";
    
    getline(cin, input, '\n');
    
    //adds input string to expression
    Sequence sequence = Sequence(input);
    
    cout << "Action: ";
    getline(cin, action, '\n');
    
    //actions: = < > f q c s
    while(action[0] != 'Q' && action[0] != 'q'){
        //if no errors
        if(!sequence.isError()){
            if(action[0] == '='){
                //evaluate expression
                sequence.outEvaluate();
            }
            else if(action[0] == '<'){
                //postfix
                sequence.outPostfix();
            }
            else if(action[0] == '>'){
                //prefix
                sequence.outPrefix();
            }
            else if(action[0] == 'F' || action[0] == 'f'){
                //fully parenthesize sequence
                sequence.outParenth();
            }
            else if(action[0] == 'C' || action[0] == 'c'){
                //add expressions to Expression vector
                string hold = sequence.getOrig();
                sequence.clear();
                cout << "Expression Input: ";
                getline(cin, input, '\n');
                sequence.addTo(hold+input);
            }
            else if(action[0] == 'S' || action[0] == 's'){
                //start over with new sequence of tokens
                sequence.clear();
                cout << "Input: ";
                getline(cin, input, '\n');
                sequence.addTo(input);
            }
            else{
                //not an action
                cout << "Not A Viable Action" << endl;
            }

            cout << "Action: ";
            getline(cin, action, '\n');
        }
        else{
            //if error output error and input new expression
            sequence.getError();
            sequence.clear();
            cout << "Expression Input: ";
            getline(cin, input, '\n');
            
            //adds input string to expression
            sequence = Sequence(input);
            
            cout << "Action: ";
            getline(cin, action, '\n');
            
        }
    }
    
    cout << "=== Expression Evaluation Program Has Ended ===" << endl;
    return 0;
}


