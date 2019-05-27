//Username: williatoma
//Student ID: 300436382

#include <cstring>

#include "editor2.hh"

using namespace std;
using namespace editor2;

size_t EditorUtilities::countWords(const char* editing_buffer, size_t buffer_size) {
    //Return if the buffer is empty
    if (!buffer_size)
        return 0;

    size_t word_count = 0;

    char c;
    size_t char_count = 0;
    for (size_t i = 0; i < buffer_size; i++) {
        //Get the character at index i
        c = *(editing_buffer + i);

        switch (c) {
            //Reset upon a whitespace character
            case '\0':
            case ' ':
            case '\t':
            case '\n':
            case '\v':
            case '\f':
            case '\r':
                if (char_count) {
                    char_count = 0;
                    word_count++;
                }
                break;
            //Otherwise increment char_count
            default:
                char_count++;
        }
    }

    //Case for when there is a word right at the end of the buffer
    if (char_count)
        word_count++;
    
    return word_count;
}

size_t EditorUtilities::searchMultipleNoCase(const char* editing_buffer, size_t buffer_size, const string search_str, size_t* positions, size_t positions_size) {
    size_t search_str_len = search_str.length();

     //Return if anything important has zero size
    if (!buffer_size || !positions_size || !search_str_len)
        return 0;

    //Make a copy of search_str, except where all of the characters are lowercase
    char* str = new char[search_str_len + 1];
    strcpy(str, search_str.c_str());
    for (size_t i = 0; i < search_str_len; i++)
        *(str + i) = tolower(*(str + i));

    size_t num_positions = 0;
    size_t search_str_offset = 0;

    char c;
    for (size_t i = 0; i < buffer_size; i++) {
        //Get the character at index i and convert it to lowercase
        c = tolower(*(editing_buffer + i));

        //Stop if the null character is encountered
        if (c == '\0')
            break;

        //Increment search_str_offset if the current character matches the current character in the search string,
        //otherwise reset it to 0
        if (c != *(str + search_str_offset++))
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

    //Deallocate the string now that we are done with it
    delete[] str;

    return num_positions;
}
