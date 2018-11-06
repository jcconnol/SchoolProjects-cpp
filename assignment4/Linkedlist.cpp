/* 
 * File:   Linkedlist.cpp
 * Author: John Connolly
 *
 * Created on October 25, 2017, 3:07 PM
 */

#include "Linkedlist.h"

Linkedlist::Linkedlist(){ //default constructor for empty list
                          //make no nodes
    head = NULL;
    tail = NULL;
}

// constructor that initializes the linked list with n nodes,
// with elem value from 0 to n-1
Linkedlist::Linkedlist(unsigned int n){
    //make first node
    head = new Node();
    head->elem = 0;
    head->prev = NULL;
    head->next = NULL;
    tail = head;

    // Create a doubly linked list from the nodes
    for (int i = 1; i < n; i++)
    {
        // Create the new node and set elem
        Node* current = new Node();
        current->elem = i;
        current->prev = tail;
        current->next = NULL;
        
        // Fold it into the list
        tail->next = current;
        
        // Move the tail
        tail = current;
    }
}

Linkedlist::~Linkedlist(){ 
    //destructor to free nodes dynamically created to support the linklist
    this->clear();
}

bool Linkedlist::empty() const{
    if(head != NULL)
        return false;
    else
        return true;
}

void Linkedlist::clear(){
    Node * current = head;
    //loops through, deletes all nodes
    while (current != NULL)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = NULL;
    tail = NULL;
}

Linkedlist::reference Linkedlist::back(){
    return tail->elem;
}

Linkedlist::const_reference Linkedlist::back() const{
    return tail->elem;
}

Linkedlist::reference Linkedlist::front(){
    return head->elem;
}

Linkedlist::const_reference Linkedlist::front() const{
    return head->elem;
}

Linkedlist& Linkedlist::operator=(const Linkedlist& l){
    if(this == &l){
        //clear list
        clear();
        //loop through other list and add all elem from l to this
        for(Node * pt = l.head; pt != NULL; pt = pt->next){
            push_back(pt->elem);
        }
    }
    return *this;
}

void Linkedlist::pop_back(){
    //remove last elem
    if(!(this->empty())){
        tail = tail->prev;
        tail->next->prev = NULL;
        delete tail->next;
        tail->next = NULL;
    }
}

void Linkedlist::pop_front(){
    //remove first elem
    if(!(this->empty())){
        head = head->next;
        head->prev->next = NULL;
        delete head->prev;
        head->prev = NULL;
    }
}

void Linkedlist::push_back( const element_type& x ){
    //add elem to back with x elem
    if(!(this->empty())){
        Node* back = new Node();
        back->prev = tail;
        tail->next = back;
        tail = back;
        back->elem = x;
    } else {
        //add new node if empty
        Node * current = new Node();
        current->elem = x;
        head = current;
        tail = current;
    }
}

void Linkedlist::push_front( const element_type& x ){
    //add elem to front with x elem
    if(!(this->empty())){
        Node* front = new Node();
        front->next = head;
        head->prev = front;
        head = front;
        front->elem = x;
    } else {
        //add new node if empty
        Node * current = new Node();
        current->elem = x;
        head = current;
        tail = current;
    }
}

void Linkedlist::sort(){
    //loops through list
    for(Node * lowest = head; lowest != NULL; lowest = lowest->next){
        //goes through last part, finds lowest and swaps with first elem
        for(Node * current = lowest; current != NULL; current = current->next){
            if(lowest->elem > current->elem){
                int temp = lowest->elem;
                lowest->elem = current->elem;
                current->elem = temp;
            }
        }
    }
}

// print the linked list in the forward direction,
void Linkedlist::check() const{
    Node* current = head;
    
    if (current == NULL)
        cout << "It is an empty list!" << endl;
    
    int i = 0;
    while (current != NULL) 
    {
        cout << "Node "          << i << "   "
             << "Elem: "         << current->elem << "   "
             << "Address: "      << current       << "   "
             << "Next Address: " << current->next << "   "
             << "Prev Address: " << current->prev << "   "
             << endl;
        current = current->next;
        i++;
    }
    
    cout << "------------------------------------------------------------------------------------------" << endl;
}

// print the linked list in the backward direction,
// similar to the reverse_show function of lab7
void Linkedlist::rcheck() const{
    Node* current = tail;
    
    if (current == NULL)
        cout << "It is an empty list!" << endl;
    
    int i = 0;
    while (current != NULL) 
    {
        cout << "Node "          << setw(3) << i             << "   "
             << "Elem: "         << setw(3) << current->elem << "   "
             << "Address: "      << setw(8) << current       << "   "
             << "Next Address: " << setw(8) << current->next << "   "
             << "Prev Address: " << setw(8) << current->prev << "   "
             << endl;
        current = current->prev;
        i++;
    }
    
    cout << "------------------------------------------------------------------------------------------" << endl;
}

// insert a node with value specified by x AFTER the node
// specified by pos. The first node has position 0.
// if the number of nodes in the linked list is less than
// pos, the node is inserted at the end.
void Linkedlist::insert(unsigned int pos, const element_type& x){
    if(!(this->empty())){
        //go to position
        Node* tmp = head;
        for(int i = 0; i < pos; i++){
            if(tmp->next != NULL){
                tmp = tmp->next;
            }
            else {
                break;
            }
        }

        //if last elem
        if(tmp->next == NULL){
            //if pos is larger than list size
            Node * adding = new Node();
            tmp->next = adding;
            adding->prev = tmp;
            tail = adding;
            tail->elem = x;

        } else {
            //if pos is less than list size
            Node * adding = new Node();
            Node * behind = tmp;
            Node * ahead = tmp->next;

            behind->next = NULL;
            ahead->prev = NULL;

            behind->next = adding;
            adding->next = ahead;
            ahead->prev = adding;
            adding->prev = behind;

            adding->elem = x;
        }
    } else {
        //add new node if empty
        Node * current = new Node();
        current->elem = x;
        head = current;
        tail = current;
    }
}

// remove the node specified by pos.
// if the number of nodes in the linked list is less than
// pos, the node at the end if any is removed.
void Linkedlist::erase(unsigned int pos){
    if(!(this->empty())){
        Node* tmp = head;
        for(int i = 0; i < pos; i++){
            if(tmp->next != NULL){
                tmp = tmp->next;
            }
            else {
                break;
            }
        }

        if(tmp->next != NULL){
            //set up pointers to before and after tmp
            Node* behind = tmp->prev;
            Node* ahead = tmp->next;

            //remove pointers to tmp
            behind->next = NULL;
            tmp->prev = NULL;
            ahead->prev = NULL;
            tmp->next = NULL;

            //make behind and ahead linked
            behind->next = ahead;
            ahead->prev = behind;

            delete tmp;

        } else if (tmp != head){
            //if 2 or more elements
            this->pop_back();
        } else {
            //only one element, clear it
            this->clear();
        }
    }
}


