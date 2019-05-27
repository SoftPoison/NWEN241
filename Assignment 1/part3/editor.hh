#ifndef __EDITOR_HH__
#define __EDITOR_HH__

#define VIEWING_ROWS 25
#define VIEWING_COLS 80

namespace editor {
    class Editor {
    public:
        /**
         * Displays the editor to the screen
         * As the main buffer is declared globally, we do not need to pass it as a parameter
         * This method handles loading the main buffer into the viewing buffer, and also
         * displaying it to the screen
         * Declared as public as the main_buffer could be modified at any point
         */
        void display();

        /**
         * Displays the editor at the given row
         * 
         * @param row the row of the editor to display from
         */
        void display(unsigned long row) {
            current_row = row;
            display();
        };
        
        /**
         * Scrolls the editor by given number of rows
         *
         * @param num_rows the number of rows to scroll by. +ve to scroll down, -ve to scroll up
         */
        void scroll(long num_rows);

        /**
         * Enables or disables word wrap
         * 
         * @param wrap true to enable word wrap, false to disable it
         */
        void set_word_wrap(bool wrap) {
            word_wrap = wrap;
            display();
        };

        /**
         * Enables or disables line numbering
         *
         * @param numbering true to enable line numbering, false to disable it
         */
        void set_line_numbering(bool numbering) {
            line_numbering = numbering;
            display();
        };

        //Getter methods.
        //Uses may include debugging, and possibly saving the state externally for when a program is rerun later

        /**
         * Gets whether word wrapping is enabled
         */
        bool get_word_wrap() {
            return word_wrap;
        };

        /**
         * Gets whether line numbering is enabled
         */
        bool get_line_numbering() {
            return line_numbering;
        };

        /**
         * Gets what row the editor is displaying from
         */
        unsigned long get_current_row() {
            return current_row;
        };

        /**
         * Creates a new instance of the editor
         */
        Editor();

    private:
        //These variables are made private to prevent unwanted modification of them, disrupting the internal state
        //They may be accessed and modified through public methods however
        
        //The internal viewing buffer
        char view_buffer[VIEWING_ROWS][VIEWING_COLS] = { };
        //Whether or not to wrap words to the next line
        bool word_wrap = false;
        //Whether or not to display numbers on each line
        bool line_numbering = false;
        //The current row to display from. Want to keep track of this for scrolling the buffer up and down
        unsigned long current_row = 0;
    };
}

#endif //__EDITOR_HH__
