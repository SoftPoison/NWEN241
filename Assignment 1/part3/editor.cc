#include "editor.hh"

using namespace editor;

void Editor::display() {
    //Take the contents of main_buffer and output a section of it to view_buffer
    //and use the internal variables current_row, word_wrap, and line_numbering 
}

void Editor::scroll(long num_rows) { //Example implementation of scroll()
    //Prevent overflows and underflows
    if (current_row + num_rows < 0)
        current_row = 0;
    else if (current_row + num_rows >= VIEWING_ROWS)
        current_row = VIEWING_ROWS - 1;
    else
        current_row += num_rows;

    display();
}

Editor::Editor() {
    //Initialise some internal stuff possibly
}
