#ifndef __LLDB_HH__
#define __LLDB_HH__

#include "dbms2.hh"

namespace dbms2 {
    struct MovieNode {
        movie value;
        MovieNode* next;
    };

    class LinkedListDbTable : public AbstractDbTable {
    public:
        unsigned long rows();
        bool show(unsigned long row);
        bool add(movie &m);
        bool remove(unsigned long id);
        movie* get(unsigned long row);

        LinkedListDbTable();
        ~LinkedListDbTable();
    private:
        MovieNode* movies;
    };
}

#endif //__LLDB_HH__