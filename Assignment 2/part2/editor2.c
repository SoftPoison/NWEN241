//Username: williatoma
//Student ID: 300436382

#include <stdio.h>
#include "editor2.h"

size_t editor_count_lines(const char* editing_buffer, size_t buffer_size) {
    //Return if the buffer has 0 size
    if (!buffer_size)
        return 0;

    size_t line_count = 0;
    
    char c;
    for (size_t i = 0; i < buffer_size; i++) {
        //Get the character at index i (using pointer notation)
        c = *(editing_buffer + i);

        //Break if c is the null character, or increment line count if it's \n
        if (c == '\0')
            break;
        else if (c == '\n')
            line_count++;
    }

    return line_count;
}

size_t editor_search_multiple(const char* editing_buffer, size_t buffer_size, const char* search_str, size_t* positions, size_t positions_size) {
    size_t search_str_len = strlen(search_str);
    
    //Return if anything important has zero size
    if (!buffer_size || !positions_size || !search_str_len)
        return 0;
    
    size_t num_positions = 0;
    size_t search_str_offset = 0;

    char c;
    for (size_t i = 0; i < buffer_size; i++) {
        //Get the character at index i
        c = *(editing_buffer + i);

        //Stop if the null character is encountered
        if (c == '\0')
            break;

        //Increment search_str_offset if the current character matches the current character in the search string,
        //otherwise reset it to 0
        if (c != *(search_str + search_str_offset++))
            search_str_offset = 0;

        //If search_str_offset equals search_str_len then a match was found, so add it to the positions array
        if (search_str_offset == search_str_len) {
            search_str_offset = 0;
            *(positions + num_positions++) = i - search_str_len + 1;
        }

        //If there are no spaces left in the positions array, then we are done searching
        if (num_positions >= positions_size)
            break;
    }

    return num_positions;
}
