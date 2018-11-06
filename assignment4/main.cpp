/* 
 * File:   main.cpp
 * Author: John Connolly
 *
 * Created on October 25, 2017, 3:06 PM
 */

#include <cstdlib>
#include "Linkedlist.h"
using namespace std;

int main() {
    Linkedlist mylist = Linkedlist();
    if(mylist.empty())
        cout << "mylist is empty" << endl;
    
    //checking functions with empty list
    mylist.pop_back();      //does nothing
    mylist.pop_front();     //does nothing
    mylist.push_back(5);    //add to empty LL
    mylist.clear();
    mylist.push_front(5);   //add to empty LL
    mylist.clear();
    mylist.sort();          //do nothing
    mylist.check();
    mylist.erase(5);        //does nothing
    mylist.insert(8, 50);   //insert 1 element
    mylist.sort();          //sort 1 element
    mylist.check();         
    mylist.erase(10);       //remove only element
    mylist.check();
    
    Linkedlist mylist2 = Linkedlist(5);
    mylist2.check();
    mylist2.rcheck();
    if(mylist2.empty())     //doesn't get called
        cout << "mylist is empty" << endl;
    
    cout << "front of mylist2: " << mylist2.front() << endl;
    cout << "back of mylist2: " << mylist2.back() << endl;
    
    mylist2.pop_back();
    mylist2.check();
    mylist2.pop_front();
    mylist2.check();
    mylist2.push_back(44);
    mylist2.check();
    mylist2.push_front(100);
    mylist2.check();
    mylist2.sort();
    mylist2.check();
    mylist2.rcheck();
    mylist2.insert(2, 1000);
    mylist2.check();
    mylist2.erase(3);
    mylist2.check();
    
    
    mylist2.clear();
    mylist2.push_back(1);
    mylist2.push_back(5);
    Linkedlist mylist5 = Linkedlist(10);
    mylist5.check();
    
    Linkedlist mylist3;
    mylist3 = mylist5;
    mylist3.check();
    
    mylist5 = mylist5;
    mylist5.check();
    
    return 0;
}


