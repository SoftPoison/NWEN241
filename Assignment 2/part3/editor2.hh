//Username: williatoma
//Student ID: 300436382

#ifndef __EDITOR2_HH__
#define __EDITOR2_HH__

#include <string>

namespace editor2 {
    class EditorUtilities {
    public:
        /**
         * Counts the number of words in the given editing buffer.
         * This method counts any sequence of one or more non-whitespace characters as a word.
         *
         * @param editing_buffer buffer to count the number of words of
         * @param buffer_size the size of the buffer
         * @returns the number of words in the buffer
         */
        static size_t countWords(const char* editing_buffer, size_t buffer_size);

        /**
         * Finds all of the positions that a string occurs in the given editing buffer, ignoring case.
         * Using size_t (= unsigned long) instead of int as it makes more sense (can't have negative sizes or indicies).
         *
         * @param editing_buffer buffer to search through
         * @param buffer_size the size of the buffer
         * @param search_str the string to search for
         * @param positions an array which is modified to contain the indices of where the string was found
         * @param positions_size the size of the positions array
         * @returns the number of occurences of the string in the buffer
         */
        static size_t searchMultipleNoCase(const char* editing_buffer, size_t buffer_size, const std::string search_str, size_t* positions, size_t positions_size);
    };
}

#endif //__EDITOR2_HH__
