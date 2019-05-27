#include <cstdlib>
#include <iostream>
#include "dbms.hh"

using namespace std;
using namespace dbms;

DbTable::DbTable() {
    //Initialise table as an array of 5 albums
    table = (album*) calloc(5, sizeof(album));

    rowsUsed = 0;
    rowsTotal = 5;
}

DbTable::~DbTable() {
    //Free the previously allocated memory
    free(table);
}

bool DbTable::show(unsigned long row) {
    //Return false if the row is out of range
    if (row >= rowsUsed)
        return false;

    //Get the album from the table
    album a = *(table + row);

    //Print out the information
    cout << "---------- Album Information ----------" << endl;
    cout << "ID: " << a.id << endl;
    cout << "Title: " << a.title << endl;
    cout << "Year: " << a.year << endl;
    cout << "Artist: " << a.artist << endl;

    return true;
}

bool DbTable::add(album &a) {
    //If we're out of free rows
    if (rowsUsed == rowsTotal) {
        rowsTotal += 5;
        //Attempt to allocate the extra rows
        album* newTable = (album*) realloc(table, sizeof(album) * rowsTotal);

        //If new memory wasn't assigned
        if (newTable == NULL)
            return false;

        //Update the table pointer
        table = newTable;
    }

    //Add the album to the table
    *(table + rowsUsed) = a;
    rowsUsed++;

    return true;
}

bool DbTable::remove(unsigned long id) {
    //Find which row the album with the given id is at
    unsigned long row = rowsUsed;
    for (unsigned long i = 0; i < rowsUsed; i++) {
        if ((*(table + i)).id == id) {
            row = i;
        }
    }

    //If the album could not be found
    if (row == rowsUsed)
        return false;

    //Shift all the albums from `row + 1` left, effectively removing the album at `row`
    for (unsigned long i = row; i < rowsUsed - 1; i++) {
        *table = *(table + 1);
    }

    rowsUsed--;

    //Shrink the number of rows in the table if necessary
    if (rowsUsed > 0 && rowsTotal - rowsUsed == 5) {
        rowsTotal -= 5;
        table = (album*) realloc(table, sizeof(album) * rowsTotal);
    }

    return true;
}
