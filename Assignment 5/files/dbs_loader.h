#ifndef __DBS_LOADER_H__
#define __DBS_LOADER_H__

#include "dbs_common.h"

#define DBS_LINE_LENGTH 128

/**
 * Loads a CSV file and parses it into a movielist
 */
movielist_t* loadTable(const char* filename);

/**
 * Deletes the movielist from memory
 */
void deleteTable(movielist_t* movies);

#endif //__DBS_LOADER_H__