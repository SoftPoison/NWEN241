#include "dbs_loader.h"

#include <string.h>

/**
 * Copies characters from start to dest until separator is reached
 * Only used in loadCSV()
 */
int nextToken(char** start, char separator, char* dest, size_t dest_size) {
    char* end = strchr(*start, separator);

    //Could not find separator in the string, so indicate failure
    if (end == NULL)
        return 1;
    
    //Copy the string until the separator to the destination
    size_t i;
    for (i = 0; *start != end && i < dest_size - 1; i++)
        dest[i] = *(*start)++;
    
    //Always end the string in a null byte
    dest[i] = '\0';
    *start = *start + 1;

    return 0;
}

movielist_t* loadTable(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        return NULL;

    //First node is empty so it's easier to manipulate
    movielist_t* movies = (movielist_t*) malloc(sizeof(movielist_t));
    if (movies == NULL) {
        fprintf(stderr, "Out of memory!\n");
        return NULL;
    }

    unsigned char error;
    movielist_t* tail = movies;
    char line[DBS_LINE_LENGTH];
    while (fgets(line, DBS_LINE_LENGTH, file) != NULL) {
        error = 1;

        //Format the lines to end with the same character, \0
        size_t last = strlen(line) - 1;
        if (line[last] == '\n')
            line[last] = '\0';

        movie_t m;
        char* lp = line;

        //Parse title
        if (nextToken(&lp, ',', m.title, 50))
            break;

        //Parse director
        if (nextToken(&lp, ',', m.director, 50))
            break;

        //Parse year
        char year[6];
        if (nextToken(&lp, ',', year, 6))
            break;

        //Convert year to number
        char *yearEnd;
        m.year = strtoul(year, &yearEnd, 10);
        if (*yearEnd != '\0') {
            error = 2;
            break;
        }

        //Parse oscarsWon
        char oscarsWon[6];
        if (nextToken(&lp, ',', oscarsWon, 6))
            break;

        //Convert oscarsWon to number
        char* oscarsWonEnd;
        m.oscarsWon = strtoul(oscarsWon, &oscarsWonEnd, 10);
        if (*oscarsWonEnd != '\0') {
            error = 2;
            break;
        }

        //Parse country
        if (nextToken(&lp, '\0', m.country, 20))
            break;

        //Construct a new node
        movielist_t* node = (movielist_t*) malloc(sizeof(movielist_t));
        if (node == NULL) {
            error = 3;
            break;
        }

        //Add the node to the end of the list
        node->value = m;
        node->next = NULL;
        tail->next = node;
        tail = node;

        error = 0;
    }

    //Close the file
    fclose(file);

    //Handle any errors thrown
    if (error) {
        fprintf(stderr, "Encountered error while loading CSV: ");
        switch (error) {
            case 1:
                fprintf(stderr, "Failed to parse token in string");
                break;
            case 2:
                fprintf(stderr, "Failed to parse number");
                break;
            case 3:
                fprintf(stderr, "Out of memory");
                break;
        }
        fprintf(stderr, "\nLine: %s", line);

        //Don't forget to free any allocated memory
        deleteTable(movies);
        return NULL;
    }
    
    return movies;
}

void deleteTable(movielist_t* movies) {
    //Loop through the table, freeing allocated memory
    movielist_t* tail = movies;
    while (tail != NULL) {
        movielist_t* next = tail->next;
        free(tail);
        tail = next;
    }
}