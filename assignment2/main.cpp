/* 
 * File:   main.cpp
 * Author: John Connolly
 *
 * Created on September 20, 2017, 3:23 PM
 */

#include <cstdlib>
#include "Token.h"
#include "Expression.h"

using namespace std;

int main(int argc, char** argv) {
    //Token checking
    Token a = Token("a1?23");   //checks for invalid
    a.display();
    Token b = Token("=");   //checks for equals
    b.display();
    Token c = Token("(");   //checks for parentheses
    c.display();
    Token d = Token("0123");    //checks for nums starting with 0
    d.display();
    Token e = Token("a123");    //checks for identifiers
    e.display();
    Token f = Token("123");     //checks for numbers
    f.display();
    
    //Expression Checking
    //checks random string ending in nondelim
    Expression example = Expression("a1(2 = 1?ab +g *-a");
    example.display();
    
    //checks just delims
    Expression example12 = Expression("(**=+");
    example12.display();
    
    //checks ending in delim with random characers
    Expression example2 = Expression("(( ((a12 = 1?ab + - a 0123 ca + 123 )*(ab - (3 + 4 ))");
    example2.display();
    
    //checks multiple of same delim together
    Expression example3 = Expression("=====+/%");
    example3.display();
    
    //checks no delims
    Expression example4 = Expression("a123848439");
    example4.display();
    
    //checks with lots of spaces and identifiers
    Expression example5 = Expression("b84 =    1$ar - = a0712 aaa + 3 )*(7)");
    example5.display();
    
    return 0;
}


