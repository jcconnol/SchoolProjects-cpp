 /*
 * File:   strtok.h
 * Author: John Connolly
 *
 * Created on September 5, 2017, 1:39 PM
 */

#ifndef MYSTRTOK_H
#define MYSTRTOK_H

//#include <cstdlib>
#include <cstdio>

char* find_first_delimiter(char *, const char *);
char* find_first_non_delimiter(char *, const char *);
char* mystrtok(char *, const char *);

#endif /* STRTOK_H */

