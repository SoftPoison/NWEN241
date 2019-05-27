#ifndef __DBS_COMMON_H__
#define __DBS_COMMON_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct movie {
    char title[50];
    char director[50];
    unsigned short year; //6 chars
    unsigned short unknown;
    char country[20];
} movie_t;

typedef struct movielist {
    movie_t value;
    struct movielist* next;
} movielist_t;

/**
 * Outputs the movie to the given filestream
 */ 
void printMovie(FILE* f, movie_t movie);

/**
 * Prints the movielist
 */
void printTable(movielist_t* movies);

#endif //__DBS_COMMON_H__