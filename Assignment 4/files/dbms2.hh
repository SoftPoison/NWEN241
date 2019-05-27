#ifndef __DBMS2_HH__
#define __DBMS2_HH__

namespace dbms2 {
    struct movie {
        unsigned long id;
        char title[50];
        unsigned short year;
        char director[50];
    };

    class AbstractDbTable {
    public:
        virtual unsigned long rows() = 0;
        virtual bool show(unsigned long row) = 0;
        virtual bool add(movie &m) = 0;
        virtual bool remove(unsigned long id) = 0;
        virtual movie* get(unsigned long row) = 0;

        AbstractDbTable() { };
        virtual ~AbstractDbTable() { };

        bool loadCSV(const char* infn);
        bool saveCSV(const char* outfn);
    };
}

#endif //__DBMS2_HH__