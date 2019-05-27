#include "vdb.hh"
#include <iostream>

using namespace dbms2;
using namespace std;

unsigned long VectorDbTable::rows() {
    return movies->size();
}

bool VectorDbTable::show(unsigned long row) {
    if (row >= movies->size())
        return false;
    
    movie m = movies->at(row);
    
    cout << "---------- Movie Information ----------" << endl;
    cout << "ID: " << m.id << endl;
    cout << "Title: " << m.title << endl;
    cout << "Year: " << m.year << endl;
    cout << "Director: " << m.director << endl;
    
    return true;
}

bool VectorDbTable::add(movie &m) {
    try {
        movies->push_back(m);
    }
    catch (exception &e) { //Fails if out of memory
        return false;
    }

    return true;
}

bool VectorDbTable::remove(unsigned long id) {
    //Look through the vector for the movie with a matching id and remove it
    for (unsigned long i = 0; i < movies->size(); i++) {
        if (movies->at(i).id == id) {
            movies->erase(movies->begin() + i);
            return true;
        }
    }
    
    return false;
}

movie* VectorDbTable::get(unsigned long row) {
    if (row >= movies->size())
        return nullptr;

    return &movies->at(row);
}

VectorDbTable::VectorDbTable() {
    movies = new vector<movie>;
}

VectorDbTable::~VectorDbTable() {
    delete movies;
}