/* 
 * File:   main.cpp
 * Author: John Connolly
 *
 * Created on October 4, 2017, 3:00 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "Mystring.h"

#define string Mystring

using namespace std;

void check (const string& s, const string& name){
    cout << "Checking " << name << endl
         << name << " contains " << s << endl
         << name << " capacity() is " <<  s.capacity() << endl
         << name << " length() is " << s.length() << endl
         << name << " size() is " << s.size() << endl
         << name << " max_size() is " << s.max_size() << endl << endl;
}


int main() 
{   
    string s0, s1, s2;
    
    if(s0.empty()){
        //cout works, s0 is empty
        cout << "s0 is empty" << endl;
    }
    s0.reserve(40);
    
    s1 = "Hello, World!";
    cout << "if s0 empty? " << s1.empty() << endl;
    cout << "is 0 so it is not empty" << endl;
    s2 = " whateverasdfjfasdsjsk";
    s2=s1;  //assignment worked
    s2=s2;  //error checking for same pointers
    
    //reserved 50
    s2.reserve(50);
    
    //pushed A onto end of string
    s1.push_back('A');
    
    check(s2, "s2");
    check(s1, "s1");
    check(s0, "s0");
    
    //adds s2 onto end of s1 correctly
    s1.append(s2);   
    
    check(s2, "s2");
    check(s1, "s1");
    check(s0, "s0");
    
    //inserted the string at 5th place
    s1.insert(5, "yolo  A shoo bibbity; bop; boii");
    
    check(s2, "s2");
    check(s1, "s1");
    check(s0, "s0");
    
    //replace works
    s2.replace(3, 5, "= ++");
    
    check(s2, "s2");
    check(s1, "s1");
    check(s0, "s0");
    
    //+ operator works, uses append
    s0 = s1 + " " + s2;
    
    check(s2, "s2");
    check(s1, "s1");
    check(s0, "s0");
    
    //reserve works
    s0.reserve(100);
    
    s1.clear();
    char c = s0[3];
    cout << "c = " << c << endl << endl;
    //push_back works
    s1.push_back(c);
    
    //append works
    s2.append(s2);
    
    check(s2, "s2");
    check(s1, "s1");
    check(s0, "s0");
    
    //replace works, uses append at place 14 and replaces 2 spots
    s2.replace(14, 2, "= ++");
    
    check(s2, "s2");
    check(s1, "s1");
    check(s0, "s0");
    
    //c_str works, returns cstr
    const char * p = s2.c_str();
    
    cout << "p pointer is " << p << endl;
    
    //== operator works
    if(p == s2){
        cout << "p and s2 are equivalent." << endl << endl;;
    }
    
    //assignment operator with array operator work
    s2[1] = s0[5];
   
    check(s1, "s1");
    check(s0, "s0");
    
    //testing clear for variable reuse
    s0.clear();
    s2.clear();
    
    cout << "p pointer is " << p << endl; 
    
    check(s2,"s2");
    check(s1,"s1");
    
    //test find first of
    //gives same output as find first of with normal string
    string what = "this is a test!";
    cout << "what, 5, 7 = " << what.find_first_of("esa", 5, 7) << endl;
    //gives same output as find first of with normal string
    cout << "what, 35, 7 = " << what.find_first_of("sss", 35, 7) << endl;
    
    //test find last not of
    
    string yolo = "wiggity wobbly woopty doo!";
    //parse whole yolo string
    cout << "yolo, whole = " << yolo.find_last_not_of("wigyobld!", yolo.length()) << endl;
    //start at 15th position
    cout << "yolo, 15 = " << yolo.find_last_not_of("wigyobld!", 15) << endl;
    
    //testing ==, != operator,
    if(s1 == s1)
        cout << "s1 == s1" << endl;
    
    if(s1 == s2)
        cout << "s1 == s2" << endl;
    
    if(s1 != s1)
        cout << "s1 != s1" << endl;
    
    if(s1 != s2)
        cout << "s1 != s2" << endl;
    
    string s_it = "iterator test";
    for (Mystring::iterator it = s_it.begin(); it != s_it.end(); ++it)
        cout << ' ' << *it;
    cout << '\n';
    
    return 0;
}
