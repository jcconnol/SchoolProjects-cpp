/*
 * File:   Mystring.cpp
 * Author: John Connolly
 *
 * Mystring class that mimics the C++ string class in the standard library
 */

#include "Mystring.h"

// Default constructor
Mystring::Mystring(){
    ptr_buffer  = new char[1];
    *ptr_buffer = '\0';
    buf_size    = 1;
    len         = 0;
}

// Other constructors
Mystring::Mystring(const char * s){
    len        = strlen(s);
    buf_size   = len + 1;
    ptr_buffer = new char[buf_size];
    strcpy(ptr_buffer, s);
}

// Copy constructor, done in lab6
Mystring::Mystring(const Mystring& orig){
    len         = orig.length();
    buf_size    = orig.length()+1;
    ptr_buffer  = new char[buf_size];
    strcpy(ptr_buffer, orig.ptr_buffer);
}

// Destructor
Mystring::~Mystring(){
    if(ptr_buffer){
        delete[] ptr_buffer;
    }
}

// Iterators
Mystring::iterator Mystring::begin(){
    //make iterator to ptr_buffer beginning
    return iterator(&ptr_buffer[0]);;

}

Mystring::iterator Mystring::end(){
    //iterator variable to end of ptr_buffer
    return iterator(&ptr_buffer[len]);;
}

//=== Memory Related ===
void Mystring::reserve(size_type n){
    //if you want to reserve more space than ptr_buffer has
    if(n >= buf_size){
        //need to make ptr_buffer large enough
        char* temp = new char[n+1];
        strcpy(temp, ptr_buffer);
        buf_size = n+1;
        //then delete previous smaller ptr_buffer
        delete[] ptr_buffer; 
        ptr_buffer = temp;
    }
}

//mystring get variables
Mystring::size_type Mystring::size() const{
    return len;
}

Mystring::size_type Mystring::length() const{
    return len;
}

Mystring::size_type Mystring::capacity() const{
    return buf_size;
}

Mystring::size_type Mystring::max_size() const{
    return (int)pow(2,30) -4;
}

//check if empty. if len == 0
bool Mystring::empty() const{
    if(len == 0){
        return true;
    }
    return false;
}

//=== Overloading operators ===

// Assignment operator
Mystring& Mystring::operator=(const Mystring& str){
    //if ptr is not pointing to exact same place
    if(this != &str){
        //change ptr_buffer to be large enough to hold str
        len = strlen(str.c_str());
        reserve(len);
        //copy data from str to this
        strcpy(ptr_buffer, str.c_str());
    }
    
    return *this;
}

Mystring& Mystring::operator=(const char * str){
    //same as mystring = operator but with cstring
    if(this->c_str() != str){
        len = strlen(str);
        reserve(len);
        strcpy(ptr_buffer, str);
    }
    return *this;
}

// Array notation
char Mystring::operator[](size_type pos) const{
    //return position of ptr_buffer
    return ptr_buffer[pos];
}

char& Mystring::operator[](size_type pos){
    //return position of ptr_buffer
    return ptr_buffer[pos];
}

// Append
Mystring& Mystring::operator+=(const Mystring& str){
    //append operator
    append(str.c_str());
    return *this;
}


Mystring& Mystring::operator+=(const char * str){
    //append operator
    append(str);
    return *this;
}

//=== Methods that modifiy the string
void Mystring::clear(){
    //makes ptr_buffer a new char array that is empty
    ptr_buffer  = new char[1];
    *ptr_buffer = '\0';
    buf_size    = 1;
    len         = 0;
}

void Mystring::push_back(char c){
    //if needed makes ptr_buffer larger
    if(len >= buf_size){
        reserve(len+1);
    }
    
    //make ptr_buffer position the letter
    ptr_buffer[len] = c;
    len++;
    //puts null character back in place
    ptr_buffer[len] = '\0';
}

Mystring& Mystring::append(const Mystring& str){ 
    //append with mystring
    this->append(str.c_str());
    return *this;
}


Mystring& Mystring::append(const char * str){
    //strlen variable needed and mem allocated for it
    int str_len = strlen(str);
    reserve(str_len + len);
    
    //goes through and adds str and increments len
    for(int i = 0; i < str_len; i++){
        ptr_buffer[len] = str[i];
        len++;
    }
    
    //places null char
    ptr_buffer[len+1] = '\0';
    
    return *this;
}


Mystring& Mystring::insert(size_type pos, const Mystring& str){
    //insert with cstr just replace at pos
    return replace(pos, 0, str.c_str());
}

Mystring& Mystring::insert(size_type pos, const char * str){
    //insert with str just replace at pos
    return replace(pos, 0, str);
}

Mystring& Mystring::replace(size_type start, size_type span, const Mystring& str){
    //check
    return this->replace(start, span, str.c_str());
}

Mystring& Mystring::replace(size_type start, size_type span, const char * str){
    //reserve exact size needed to reserve
    reserve(len+ strlen(str) - span);
    
    //mystring end made
    Mystring end(ptr_buffer + start +span);
    
    //null character set
    ptr_buffer[start] = '\0';
    
    //len is start place
    len = start;
    append(str);
    append(end);
    
    return *this;
}

//=== Conversion to c-string

const char * Mystring::c_str() const{
    //return cstr holder
    return ptr_buffer;
}

//=== Two new methods not in lab 5 header file

// buffer (3) version of the overloaded method
Mystring::size_type Mystring::find_first_of (const char* s, size_type pos, size_type n) const{
    //parse through ptr_buffer
    for(int i = pos; ptr_buffer[i] != '\0'; i++){
        //parse through s variable
        for(int j = 0; s[j] != '\0' && j < n; j++){//maybe or
            if(ptr_buffer[i] == s[j])
                return i;
        }
    }
    return npos;
}

// c-string (2)
Mystring::size_type Mystring::find_last_not_of (const char* s, size_type pos) const{
    //error checking for pos out of bounds
    int size = strlen(s);
    if(pos > len)
        pos = len;
    
    //parse through ptr_buffer starting with pos
    for(int i = pos; i > 0; i--){
        //parse through s variable of characters
        for(int j = 0; j <= size; j++){
            if(ptr_buffer[i] == s[j])
                break;
            if(j == size){
                return i;
            }
        }
    }
    
    return npos;
}

//=== Overloading global operators for Mystring

// Overload operator == for Mystring
bool operator==(const Mystring& first, const Mystring& second){
    return (first.c_str() == second.c_str());
}

bool operator==(const char * first, const Mystring& second){
    return (first == second.c_str());
}

bool operator==(const Mystring& first, const char * second){
    return first.c_str() == second;
}

// Overload operator != for Mystring
bool operator!=(const Mystring& first, const Mystring& second){
    return !(first.c_str() == second.c_str());
}

bool operator!=(const char * first, const Mystring& second){
    return !(first == second.c_str());
}

bool operator!=(const Mystring& first, const char * second){
    return !(first.c_str() == second);
}

// Overload operator + for string as concatenation
Mystring operator+(const Mystring& first, const Mystring& second){
    //make new variables
    Mystring var = first;
    var += second;
    return var;
}

// Output
ostream& operator<<(ostream& out, const Mystring& str){
    //outputs to ostream out variable
    out << str.c_str();
    return out;
}

typedef Mystring::iterator iterator;
