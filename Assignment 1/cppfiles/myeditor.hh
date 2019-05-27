/**
 * myeditor.hh
 * 
 * You must define a class that extends the EditingBuffer class in this file.
 * Consult the assignment handout for more information.
 * 
 * Student ID: 300436382
 * Name: Tomais Williamson
 */

#ifndef __MYEDITOR_HH__
#define __MYEDITOR_HH__

#include "editor.hh"

namespace editor {
    //Subclass of EditingBuffer
    class MyEditor : public EditingBuffer {
    public:
        //Override methods
        bool replace(char c, char replacement, int offset);
        int replace(std::string str, std::string replacement, int offset);
        void justify(char** viewingBuffer, int rows, int cols);

        //Default constructor is necessary
        MyEditor() : EditingBuffer() {};
    }; 
}

#endif //__MYEDITOR_HH__
