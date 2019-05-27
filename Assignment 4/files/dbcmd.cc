#include <iostream>
#include <cstring>

#include "lldb.hh"

using namespace std;
using namespace dbms2;

int showall() {
    //Attempt to load the file
    LinkedListDbTable* db = new LinkedListDbTable();
    if (!db->loadCSV("default.csv")) {
        delete db;
        return 1;
    }
    
    for (unsigned long i = 0; i < db->rows(); i++)
        db->show(i);
    
    delete db;
    return 0;
}

int show(unsigned long row) {
    //Attempt to load the file
    LinkedListDbTable* db = new LinkedListDbTable();
    if (!db->loadCSV("default.csv")) {
        delete db;
        return 1;
    }

    if (!db->show(row)) {
        cerr << "Row out of range" << endl;
        delete db;
        return 1;
    }
    
    delete db;
    return 0;
}

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        cout << "Usage:" << endl;
        return 0;
    }
    else if (argc >= 2 && !strcmp(argv[1], "showall")) {
        return showall();
    }
    else if (argc == 3 && !strcmp(argv[1], "show")) {
        //Try to parse the following arg as a number
        errno = 0;
        char* endptr = NULL;
        int row = strtoul(argv[2], &endptr, 10);

        if (argv[2] == endptr) {
            cerr << "Cannot parse number \"" << argv[2] << '"' << endl;
            return 1;
        }
        else {
            return show(row);
        }
    }
    else {
        cerr << "Unknown argument \"" << argv[1] << '"' << endl;
        return 1;
    }
}
