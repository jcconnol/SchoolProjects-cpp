/*
 * By: John Connolly
 * mystrlen.cpp
 * Assignment one
 */

#include "mystrlen.h"

size_t mystrlen(const char* str){
    size_t holder = 0;
    while(str[holder] != '\0'){
        holder++;
    }
    return holder;
}
