#include "dbs_common.h"
#include "dbs_loader.h"
#include "dbs_service.h"

#include <signal.h>

static movielist_t* table = NULL;

void exiting(int i) {
    deleteTable(table);
    putchar('\n');
    exit(0);
}

int main() {
    table = loadTable("scifi.csv");

    if (table == NULL) {
        perror("Failed to load CSV\n");
        return 1;
    }

    //Trap all of the relevant interrupts so that the db is deleted on exit
    signal(SIGINT, exiting);
    signal(SIGABRT, exiting);
    signal(SIGTERM, exiting);
    signal(SIGTSTP, exiting);

    //Start the server
    runServer(table);

    //If execution gets to here, some error probably occurred

    //free the table
    deleteTable(table);
    return 1;
}

