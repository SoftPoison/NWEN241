#ifndef __DBS_SERVICE_H__
#define __DBS_SERVICE_H__

#include "dbs_common.h"

#define DBS_PORT 12345

/**
 * Runs the server
 */
int runServer(movielist_t* movies);

/**
 * Handles a client connection
 */
void handleClient(int socket_fd, movielist_t* movies);

#endif //__DBS_SERVICE_H__