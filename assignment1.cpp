/*
 * By: John Connolly
 * main.cpp
 * Assignment one
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "mystrtok.h"

using namespace std;

int main() {
    
    // string 1 test, just random stuff with one using mystrtok and one using strtok
    char str[] = "-.,fjdjai biv,dna..fdsa..";
    
    char * pch;
    printf("Splitting string \"%s\" into tokens:\n", str);
    pch = mystrtok(str, " ,.-");
    
    while (pch != NULL) {
        printf("%s\n", pch);
        pch = mystrtok(NULL, " ,.-");
    }

    char str2[] = "-.,fjdjai biv,dna..fdsa..";
    char * pch2;
    pch2 = strtok(str2, " ,.-");
    while (pch2 != NULL) {
        printf("%s\n", pch2);
        pch2 = strtok(NULL, " ,.-");
    }
    
    //testing a blank string
    char blankstr[] = "";
    char * pch3;
    printf("Splitting string \"%s\" into tokens:\n", blankstr);
    pch3 = mystrtok(blankstr, " ,.-");

    while (pch3 != NULL) {
        printf("%s\n", pch3);
        pch3 = mystrtok(NULL, " ,.-");
    }

    char blankstr2[] = "";
    char * pch4;
    pch4 = strtok(blankstr2, " ,.-");
    while (pch4 != NULL) {
        printf("%s\n", pch4);
        pch4 = strtok(NULL, " ,.-");
    }

    //testing just delimiters
    char deli_str[] = "- ,....";
    char * pch5;
    printf("Splitting string \"%s\" into tokens:\n", deli_str);
    pch5 = mystrtok(deli_str, " ,.-");

    while (pch5 != NULL) {
        printf("%s\n", pch5);
        pch5 = mystrtok(NULL, " ,.-");
    }
    
    char deli_str2[] = "- ,....";
    char * pch6;
    pch6 = strtok(deli_str2, " ,.-");
    while (pch6 != NULL) {
        printf("%s\n", pch6);
        pch6 = strtok(NULL, " ,.-");
    }

    //testing just non-delimiters
    char nondeli_str[] = "Thishasnodelimiters";
    char * pch7;
    printf("Splitting string \"%s\" into tokens:\n", nondeli_str);
    pch7 = mystrtok(nondeli_str, " ,.-");

    while (pch7 != NULL) {
        printf("%s\n", pch7);
        pch7 = mystrtok(NULL, " ,.-");
    }
    
    char nondeli_str2[] = "Thishasnodelimiters";
    char * pch8;
    pch8 = strtok(nondeli_str2, " ,.-");
    while (pch8 != NULL) {
        printf("%s\n", pch8);
        pch8 = strtok(NULL, " ,.-");
    }
    
    //first char isn't delimiter
    char deli_not_first_str[] = "wuba luba,. dub-dub,";
    char * pch9;
    printf("Splitting string \"%s\" into tokens:\n", deli_not_first_str);
    pch9 = mystrtok(deli_not_first_str, " ,.-");
    
    while (pch9 != NULL) {
        printf("%s\n", pch9);
        pch9 = mystrtok(NULL, " ,.-");
    }
    
    char deli_not_first_str2[] = "wuba luba,. dub-dub,";
    char * pch10;
    pch10 = strtok(deli_not_first_str2, " ,.-");
    while (pch10 != NULL) {
        printf("%s\n", pch10);
        pch10 = strtok(NULL, " ,.-");
    }
    
    //using different delimiter
    char diff_deli_str[] = "wuba luba,. dub-dub,";
    char * pch11;
    printf("Splitting string \"%s\" into tokens:\n", diff_deli_str);
    pch11 = mystrtok(diff_deli_str, "wl.,");

    while (pch11 != NULL) {
        printf("%s\n", pch11);
        pch11 = mystrtok(NULL, "wl.,");
    }

    char diff_deli_str2[] = "wuba luba,. dub-dub,";
    char * pch12;
    pch12 = strtok(diff_deli_str2, "wl.,");
    while (pch12 != NULL) {
        printf("%s\n", pch12);
        pch12 = strtok(NULL, "wl.,");
    }
  
    return 0;
}
