#include "dbs_common.h"

void printMovie(FILE* f, movie_t m) {
    fprintf(f, "%s\t| %s\t| %hu\t| %hu\t| %s\n", m.title, m.director, m.year, m.unknown, m.country);    
}

void printTable(movielist_t* movies) {
    //Loops through the entire table, outputting it to stdout
    movielist_t* node = movies->next;
    while (node != NULL) {
        movie_t m = node->value;
        printMovie(stdout, m);

        node = node->next;
    }
}