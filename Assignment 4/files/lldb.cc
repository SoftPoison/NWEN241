#include "lldb.hh"
#include <iostream>

using namespace dbms2;
using namespace std;

unsigned long LinkedListDbTable::rows() {
    //If the list is empty
    if (movies == nullptr)
        return 0;

    //Count the number of rows one by one
    unsigned long rows = 1;
    MovieNode* node = movies;
    while (node->next != nullptr) {
        node = node->next;
        rows++;
    }

    return rows;
}

bool LinkedListDbTable::show(unsigned long row) {
    //If the list is empty
    if (movies == nullptr)
        return false;
    
    //Traverse the list
    unsigned long current = 0;
    MovieNode* node = movies;
    while (node->next != nullptr && current != row) {
        node = node->next;
        current++;
    }

    //Print the movie if we've reached the right row
    if (current == row) {
        movie m = node->value;

        cout << "---------- Movie Information ----------" << endl;
        cout << "ID: " << m.id << endl;
        cout << "Title: " << m.title << endl;
        cout << "Year: " << m.year << endl;
        cout << "Director: " << m.director << endl;

        return true;
    }
    
    return false;
}

bool LinkedListDbTable::add(movie &m) {
    //If the list is empty
    if (movies == nullptr) {
        movies = new MovieNode;
        if (movies == nullptr) //Fails if out of heap memory
            return false;

        movies->value = m;
        movies->next = nullptr;
        return true;
    }

    //Traverse to the last node
    MovieNode* node = movies;
    while (node->next != nullptr)
        node = node->next;

    //Attempt to add the movie to the list
    MovieNode* child = new MovieNode;
    if (child == nullptr)
        return false;
    
    child->value = m;
    child->next = nullptr;
    node->next = child;

    return true;
}

bool LinkedListDbTable::remove(unsigned long id) {
    //If the list is empty
    if (movies == nullptr)
        return false;

    //If the root node matches
    if (movies->value.id == id) {
        //Relink the list and free the node
        MovieNode* child = movies->next;
        delete movies;
        movies = child;
        return true;
    }
    else if (movies->next == nullptr) { //No point searching if there are no children
        return false;
    }
    
    //Traverse the list, keeping track of the previous node too
    MovieNode* parent = movies;
    MovieNode* node = movies->next;
    while (node->next != nullptr) {
        //If we've found the correct node
        if (node->value.id == id) {
            //Relink the list and free the node
            MovieNode* child = node->next;
            delete node;
            parent->next = child;
            return true;
        }

        parent = node;
        node = node->next;
    }

    return false;
}

movie* LinkedListDbTable::get(unsigned long row) {
    //If the list is empty
    if (movies == nullptr)
        return nullptr;
    
    //Traverse through the list
    unsigned long current = 0;
    MovieNode* node = movies;
    while (node->next != nullptr && current != row) {
        node = node->next;
        current++;
    }

    //Return the node's value if we've reached the right row
    if (current == row)
        return &node->value;

    return nullptr;
}

LinkedListDbTable::LinkedListDbTable() {
    movies = nullptr;
}

LinkedListDbTable::~LinkedListDbTable() {
    //Go through the list, freeing the memory that has been previously allocated
    MovieNode* node = movies;
    while (node != nullptr) {
        MovieNode* next = node->next;
        delete node;
        node = next;
    }
}