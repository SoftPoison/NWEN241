#include "dbs_service.h"

#include <ctype.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

int runServer(movielist_t* movies) {
    int sock_fd, new_sock_fd; //Socket file descriptors
    struct sockaddr_in server_addr, client_addr; //Address structs

    //Attempt to open a TCP socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd < 0) {
        fprintf(stderr, "Error opening socket\n");
        return 1;
    }

    //Construct the server address struct
    bzero((char*) &server_addr, sizeof(server_addr)); //Zero out the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(DBS_PORT);

    //Attempt to bind to socket
    if (bind(sock_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Error binding to socket\n");
        return 1;
    }

    //Start listening to the socket, with a max backlog of 5
    listen(sock_fd, 5);

    unsigned int client_len = sizeof(client_addr);
    int pid;
    while (1) {
        //Clean up dead children, but don't hang
        waitpid(-1, NULL, WNOHANG);

        //Accept the next client in the queue (and wait for one if none are yet available)
        new_sock_fd = accept(sock_fd, (struct sockaddr*) &client_addr, &client_len);

        if (new_sock_fd < 0) {
            perror("Error on accept");
            exit(1);
        }

        //Fork the process (so multiple clients can be connected)
        pid = fork();

        if (pid < 0) {
            perror("Error forking process");
            exit(1);
        }

        if (pid == 0) { //Child
            close(sock_fd); //Close sock_fd on the child as it doesn't need access to it
            handleClient(new_sock_fd, movies);
            exit(0);
        }
        else { //Parent
            close(new_sock_fd); //Close new_sock_fd on the parent as it doesn't need access to it
        }
    }

    return 0;
}

/**
 * Moves charp until *charp is pointing to a non-whitespace character
 * Only used in handleClient
 */
void skipWhitespace(char** charp, int* n) {
    while (isspace(**charp)) {
        (*charp)++;
        (*n)--;
    }
}

void handleClient(int socket_fd, movielist_t* movies) {
    FILE* out = fdopen(socket_fd, "w");
    fputs("HELLO\n", out);
    fflush(out);

    int n;
    char buffer[256];

    int clientConnected = 1;
    while (clientConnected) {
        bzero(buffer, 256); //Clear the buffer
        n = read(socket_fd, buffer, 255); //Hangs until message received

        if (n < 0) {
            perror("Error reading from socket");
            exit(1);
        }
        else if (n == 0) { //Client has disconnected (e.g ctrl-c in netcat)
            clientConnected = 0;
            continue;
        }

        char* charp = buffer;
        skipWhitespace(&charp, &n);

        if (n < 3) {
            goto HC_UNKNOWN_COMMAND;
        }

        if (!strncasecmp(charp, "GET", 3)) {
            charp += 3;
            n -= 3;
            skipWhitespace(&charp, &n);

            if (n > 0) { //Has an argument
                char* end;
                unsigned long row = strtoul(charp, &end, 10);

                if (!isspace(*end)) { //Couldn't parse argument as number
                    unsigned long dist = (unsigned long) end - (unsigned long) buffer;
                    for (unsigned long i = 0; i < dist; i++)
                        fputc(' ', out);
                    
                    fputs("^\nError: invalid number\n", out);
                }
                else {
                    movielist_t* node = movies;
                    while (node != NULL) {
                        node = node->next;

                        if (row == 0)
                            break;
                            
                        row--;
                    }

                    if (node == NULL) { //Gone past end of array
                        fputs("Error: range out of bounds\n", out);
                    }
                    else {
                        //Print row
                        printMovie(out, node->value);
                    }
                }
            }
            else {
                //Print all rows
                movielist_t* node = movies->next;
                while (node != NULL) {
                    printMovie(out, node->value);
                    node = node->next;
                }
            }
        }
        else if (!strncasecmp(charp, "BYE", 3)) {
            charp += 3;
            n -= 3;
            skipWhitespace(&charp, &n);

            if (n > 0) {
                fputs("Error: BYE takes no arguments\n", out);
            }
            else {
                //Disconnect the client
                clientConnected = 0;
            }
        }
        else {
            HC_UNKNOWN_COMMAND:
            fputs("Error: unknown command\n", out);
        }

        fflush(out);
    }
}