/**
 * myeditor.cc
 * 
 * You must implement the member functions, including constructors, of your class defined in myeditor.hh.
 * Consult the assignment handout for the detailed specifications of each of the member functions.
 * 
 * Student ID: 300436382
 * Name: Tomais Williamson
 */

#include <sstream>
#include <vector>
#include "editor.hh"
#include "myeditor.hh"

using namespace editor;
using namespace std;

/**
 * Splits a string into a vector (array) of the words comprising it
 * Inlined as it's only used in one method, but it's complex enough to be standalone
 *
 * Modified from https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string#236803
 */
inline vector<string> split(char* s) {
    vector<string> elems;
    stringstream ss(s); //Using stringstream as it is more efficient than alternatives
    string item;
    while (getline(ss, item, ' ')) {
        if (!item.empty()) //Only add the string if it is not an empty string
            elems.push_back(item);
    }

    return elems;
}

/**
 * Replaces a character with another, searching forwards from the given offset
 */
bool MyEditor::replace(char c, char replacement, int offset) {
    if (offset < 0 || offset >= BUFFER_LEN)
        return false;

    for (int i = offset; i < BUFFER_LEN; i++) {
        if (buffer[i] == c) {
            buffer[i] = replacement;
            return true;
        }
    }
    
    return false;
}

/**
 * Replaces a string with another, searching forwards from the given offset
 */
int MyEditor::replace(string str, string replacement, int offset) {
    size_t str_len = str.length();
    size_t replacement_len = replacement.length();
    size_t len_diff = str_len > replacement_len ? str_len - replacement_len : replacement_len - str_len;
    
    if (offset < 0 || str_len == 0 || offset >= BUFFER_LEN || offset + str_len >= BUFFER_LEN)
        return -1;
    
    for (int i = offset; i < BUFFER_LEN; i++) {
        unsigned long j;

        //Compare the next n characters in the buffer to see if they match the string
        for (j = 0; j < str_len; j++)
            if (buffer[i + j] != str[j])
                break;

        //Continue if the strings didn't match
        if (j < str_len)
            continue;

        if (str_len < replacement_len) { //Move contents right
            for (j = BUFFER_LEN - 1; j > i + str_len; j--)
                buffer[j] = buffer[j - len_diff];
        }
        else if (str_len > replacement_len) { //Move contents left
            for (j = i; j + len_diff < BUFFER_LEN; j++)
                buffer[j] = buffer[j + len_diff];
        }

        //Insert the replacement
        for (j = 0; j < replacement_len && i + j < BUFFER_LEN; j++)
            buffer[i + j] = replacement[j];

        //Return the index of the last character replaced
        return i + j - 1;
    }
    
    return -1;
}

void MyEditor::justify(char** viewingBuffer, int rows, int cols) {
    int row;
    int col;
    char* lines[rows]; //An easier to use conversion of viewingBuffer

    //Reset the viewing buffer to all null characters and also set up lines[]
    for (row = 0; row < rows; row++) {
        lines[row] = (char*) viewingBuffer + cols * row;

        for (col = 0; col < cols; col++)
            lines[row][col] = '\0';
    }

    row = 0;
    col = 0;

    //Translate the editing buffer into a multiline form
    for (unsigned long i = 0; i < BUFFER_LEN; i++) {
        char c = buffer[i];

        if (c == '\0') //End of editing buffer
            break;

        if (c == '\n') { //Go to next line
            row++;
            col = 0;
            continue;
        }

        if (col >= cols - 1) { //Wrap to next line
            row++;
            col = 0;
        }

        if (row >= rows)
            break;

        //Assign the character
        lines[row][col] = c;

        col++;
    }

    //Justify the text in the viewing buffer
    for (row = 0; row < rows; row++) {
        //Split the text in the row into it's subsequent words
        vector<string> words = split(lines[row]);

        //Only justify if there are two or more words in the line
        if (words.size() < 2)
            continue;

        //Calculate how many spaces are needed based on the line length and the number of other characters
        unsigned long spaces_needed = cols - 1;
        for (unsigned int i = 0; i < words.size(); i++)
            spaces_needed -= words.at(i).length();
        
        unsigned long num_gaps = words.size() - 1;
        //Ceiling division (so that the former gaps have more spaces than latter)
        unsigned long spaces_per_gap = spaces_needed / num_gaps + (spaces_needed % num_gaps != 0);
        unsigned long space_count = 0;

        col = 0;
        for (unsigned long i = 0; i < words.size(); i++) {
            //Write the word to the line
            string word = words.at(i);
            for (unsigned long j = 0; j < word.length(); j++)
                lines[row][col++] = word[j];

            //Write the required number of spaces to the line
            for (unsigned long j = 0; j < spaces_per_gap && space_count++ < spaces_needed; j++)
                lines[row][col++] = ' ';
        }
    }
}

//Main function is just filled with debug stuff
int main() {
    const int rows = 8;
    const int cols = 11;
    char viewing_buffer[rows][cols];

    MyEditor editor;
    editor.setBuffer("The quick brown\nfox jumps over\n\nthe lazy dog", 44);

    editor.justify((char**) viewing_buffer, rows, cols);

    for (int row = 0; row < rows; row++)
        cout << viewing_buffer[row] << endl;

    return 0;
}
