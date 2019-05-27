/**
 * editor.c
 * 
 * You must implement the functions in editor.h in this file.
 * Consult the assignment handout for the detailed specifications of each of the functions.
 * 
 * Student ID: 300436382
 * Name: Tomais Williamson
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "editor.h"

/**
 * A debug function for displaying the viewing buffer
 * 
 * @param viewing_buffer the viewing buffer to display
 */
void display_viewing_buffer(char viewing_buffer[VIEWING_ROWS][VIEWING_COLS]) {
    for (int row = 0; row < VIEWING_ROWS; row++) {
        printf("%s\n", viewing_buffer[row]);
    }
}

/**
 * Entry point for the program
 * Used for testing purposes
 */
int main() {
    char editing_buffer[EDITING_BUFLEN] = { }; //Initialised with empty braces as otherwise it gets random junk for no reason
    char viewing_buffer[VIEWING_ROWS][VIEWING_COLS] = { };
   
    editor_insert_char(editing_buffer, 'a', 0);
    editor_replace_str(editing_buffer, "a", "The quick brown\nfox jumps over\n\nthe lazy dog\n", 0);
    editor_replace_str(editing_buffer, "quick ", "", 4);
    editor_delete_char(editing_buffer, 'o', 20);

    editor_view((char**) viewing_buffer, editing_buffer, 1);
    display_viewing_buffer(viewing_buffer);
    
    return 0;
}

/**
 * Inserts a character into the editing buffer, shifting the contents of the buffer right
 * 
 * @param editing_buffer the buffer to insert a character into
 * @param to_insert the character to insert
 * @param pos the position to insert to
 * @return 1 if successful, 0 otherwise
 */
int editor_insert_char(char* editing_buffer, char to_insert, int pos) {
    if (pos < 0 || pos >= EDITING_BUFLEN)
        return 0;
    
    for (int i = EDITING_BUFLEN - 1; i > pos; i--)
        editing_buffer[i] = editing_buffer[i - 1];

    editing_buffer[pos] = to_insert;

    return 1;
}

/**
 * Deletes a character from the viewing buffer, shifting the contents of the buffer left
 *
 * @param editing_buffer the buffer to remove a character from
 * @param to_delete the character to delete
 * @param offset the position in the buffer to start the search from
 * @return 1 if succesful, 0 otherwise
 */
int editor_delete_char(char* editing_buffer, char to_delete, int offset) {
    if (offset < 0 || offset >= EDITING_BUFLEN)
        return 0;

    for (int i = offset; i < EDITING_BUFLEN; i++) {
       if (editing_buffer[i] == to_delete) {
            for (int j = i; j < EDITING_BUFLEN; j++)
                editing_buffer[j] = editing_buffer[j + 1];

            return 1;
        }
    }

    return 0;
}

/**
 * Replaces a string in the editing buffer with another
 *
 * @param editing_buffer the buffer to modify
 * @param str the string to search for
 * @param replacement the replacement string
 * @param offset the position in the buffer to start the search from
 * @return -1 if the replacement was unsuccessful, otherwise the last index of the inserted string
 */
int editor_replace_str(char* editing_buffer, const char* str, const char* replacement, int offset) {    
    size_t str_len = strlen(str);
    size_t replacement_len = strlen(replacement);
    size_t len_diff = str_len > replacement_len ? str_len - replacement_len : replacement_len - str_len;
    
    if (offset < 0 || str_len == 0 || offset >= EDITING_BUFLEN || offset + str_len >= EDITING_BUFLEN)
        return -1;

    for (int i = offset; i < EDITING_BUFLEN; i++) {
        unsigned long j;

        //Compare the next n characters in the buffer to see if they match the string
        for (j = 0; j < str_len; j++)
            if (editing_buffer[i + j] != str[j])
                break;

        //Continue if the strings don't match
        if (j < str_len)
            continue;
        
        if (str_len < replacement_len) { //Move contents right
            for (j = EDITING_BUFLEN - 1; j > i + str_len; j--)
                editing_buffer[j] = editing_buffer[j - len_diff];
        }
        else if (str_len > replacement_len) { //Move contents left
            for (j = i; j < EDITING_BUFLEN; j++)
                editing_buffer[j] = editing_buffer[j + len_diff];
        }

        //Insert the replacement string (but being careful not to go past the edge of the buffer)
        for (j = 0; j < replacement_len && i + j < EDITING_BUFLEN; j++)
            editing_buffer[i + j] = replacement[j];

        //Return the index of the last character replaced
        return i + j - 1;
    }
    
    return -1;
}

/**
 * Copies the contents of the editing buffer to the viewing buffer, with optional word wrap
 *
 * @param viewing_buffer the buffer to copy to
 * @param editing_buffer the buffer to copy from
 * @param wrap non-zero indicates that text should wrap to the next line instead of being discarded
 */
void editor_view(char** viewing_buffer, const char* editing_buffer, int wrap) {
    int row;
    int col;
    char* lines[VIEWING_ROWS]; //An easier to use conversion of viewing_buffer

    //Reset the viewing_buffer to all null characters and also set up lines[]
    for (row = 0; row < VIEWING_ROWS; row++) {
        lines[row] = (char*) viewing_buffer + VIEWING_COLS * row;
        
        for (col = 0; col < VIEWING_COLS; col++)
            lines[row][col] = '\0';
    }

    row = 0;
    col = 0;
    for (unsigned long i = 0; i < EDITING_BUFLEN; i++) {
        char c = editing_buffer[i];
        
        if (c == '\0') { //End of editing_buffer
            break;
        }
    
        if (c == '\n') { //Go to next line
            row++;
            col = 0;
            continue;
        }

        if (wrap && col >= VIEWING_COLS - 1) {
            row++;
            col = 0;
        }
        
        if (col >= VIEWING_COLS - 1) {
            continue;
        }
        else if (row >= VIEWING_ROWS) {
            break;
        }

        //Assign the character
        lines[row][col] = c;

        col++;
    }
}
