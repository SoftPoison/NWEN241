#include "dbms2.hh"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;
using namespace dbms2;

bool AbstractDbTable::loadCSV(const char* infn) {
    ifstream file(infn);

    //If the file doesn't exist or just can't be read
    if (!file.is_open()) {
        cerr << "Couldn't open file" << endl;
        return false;
    }

    //Iterate through the lines of the file
    string line;
    while (getline(file, line)) {
        string items[4];
        short count = 0;

        //Iterate through the comma separated items on the line
        string item;
        istringstream linestream(line);
        while (getline(linestream, item, ',')) {
            if (count > 3) {
                cerr << "Malformed csv - too many tokens" << endl;
                file.close();
                return false;
            }

            items[count++] = item;
        }

        if (count < 4) {
            cerr << "Malformed csv - too few tokens" << endl;
            file.close();
            return false;
        }

        //Just in case the strings are too long
        if (items[1].size() >= 50 || items[3].size() >= 50) {
            cerr << "Malformed csv - string too long" << endl;
            file.close();
            return false;
        }

        try {
            //Construct the movie
            movie m;
            m.id = stoul(items[0], nullptr, 10);
            strcpy(m.title, items[1].c_str());
            m.year = (unsigned short) stoul(items[2], nullptr, 10); //Pretty safe to go from ulong -> ushort
            strcpy(m.director, items[3].c_str());

            //And add it to database
            add(m);
        }
        catch (exception &e) {
            cerr << "Malformed csv - could not parse token" << endl;
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

bool AbstractDbTable::saveCSV(const char* outfn) {
    ofstream file(outfn);

    //If the file doesn't exist or just can't be read
    if (!file.is_open()) {
        cerr << "Couldn't open file" << endl;
        return false;
    }

    for (unsigned long row = 0; row < rows(); row++) {
        try { //Attempt to write the row
            movie* m = get(row);
            file << m->id << ',' << m->title << ',' << m->year << ',' << m->director << endl;
        }
        catch (exception &e) { //Write failure
            cerr << "Failed to write to file" << endl;
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}