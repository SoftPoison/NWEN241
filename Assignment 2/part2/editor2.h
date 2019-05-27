//Username: williatoma
//Student ID: 300436382

#ifndef __EDITOR2_H__
#define __EDITOR2_H__

#include <string.h>

/**
 * Counts the number of lines in the given editing buffer.
 * From what I can tell it just counts the number of "\n"'s.
 *
 * @param editing_buffer buffer to count the lines of
 * @param buffer_size the size of the buffer
 * @returns the number of lines in the buffer
 */
size_t editor_count_lines(const char* editing_buffer, size_t buffer_size);

/**
 * Finds all of the positions that a string occurs in the given editing buffer.
 * Using size_t (= unsigned long) instead of int as it makes more sense (can't have negative sizes or indices).
 *
 * @param editing_buffer buffer to search through
 * @param buffer_size the size of the buffer
 * @param search_str the string to search for
 * @param positions an array which is modified to contain the indices of where the string was found
 * @param positions_size the size of the positions array
 * @returns the number of occurences of the string in the buffer
 */
size_t editor_search_multiple(const char* editing_buffer, size_t buffer_size, const char* search_str, size_t* positions, size_t positions_size);

#endif //__EDITOR2_H__
