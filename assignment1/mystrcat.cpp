/*
 * By: John Connolly
 * mystrcat.cpp
 * Assignment one
 */

#include "mystrcat.h"

char* mystrcat(char * first, const char * second){
    int dest = 0;
    while(first[dest] != '\0'){
        dest++;
    }

    int holder = 0;
    while(second[holder] != '\0'){
        first[dest] = second[holder];
        dest++;
        holder++;
    }

    return first;
}
