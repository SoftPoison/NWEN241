#ifndef __VDB_HH__
#define __VDB_HH__

#include "dbms2.hh"
#include <vector>

namespace dbms2 {
    class VectorDbTable : public AbstractDbTable {
    public:
        unsigned long rows();
        bool show(unsigned long row);
        bool add(movie &m);
        bool remove(unsigned long id);
        movie* get(unsigned long row);

        VectorDbTable();
        ~VectorDbTable();
    private:
        std::vector<movie>* movies;
    };
}

#endif //__VDB_HH__