#ifndef __DBMS_HH__
#define __DBMS_HH__

namespace dbms {
    struct album {
        unsigned long id;
        char title[100];
        unsigned short year;
        char artist[100];
    };

    class DbTable {
    public:
        DbTable();
        ~DbTable();

        /**
         * Prints out the album information of the album at the given row in the database
         *
         * @param row the row to read
         * @return true if the read was successful, false otherwise (e.g, row was outside of range)
         */
        bool show(unsigned long row);

        /**
         * Adds an album to the database
         *
         * @param &a the album to add
         * @return true if the addition was successful, false otherwise
         */
        bool add(album &a);

        /**
         * Removes the album with the given id from the database
         *
         * @param id the id of the album to remove
         * @return true if the removal was successful, false otherwise
         */
        bool remove(unsigned long id);

        /**
         * Gets the number of rows in use in the database
         */
        inline unsigned long rows() { return rowsUsed; };

        /**
         * Returns the number of rows allocated in memory
         */
        inline unsigned long allocated() { return rowsTotal; };
   
    private:
        album* table;
        unsigned long rowsTotal = 0;
        unsigned long rowsUsed = 0;
    };
}

#endif //__DBMS_HH__
