/**
 * t11test.cc
 * Sample test program for Task 10
 *
 * To compile with your implementation:
 * g++ t11test.cc editor2.cc -o t11test
 *
 * If successful, executable file t11test should have been
 * created.
 */

#include <iostream>
#include "editor2.hh"

#define TEST_STRING "The good, the bad and the lucky."

using namespace editor2;
using namespace std;

int main(void)
{
  char buffer[] = TEST_STRING;
  size_t positions[20];
  size_t *pp = positions;

  cout << "Buffer contents: " << buffer << endl;
  size_t r = EditorUtilities::searchMultipleNoCase(buffer, sizeof(buffer), string("the"), positions, 20);
  cout << "Output of EditorUtilities::searchMultipleNoCase(): " << r << endl;
  cout << "Positions: ";
  for(size_t i=0; i<r; i++) { cout << *pp << " "; pp++; }
  cout << endl << "Actual number of occurrences in buffer of 'the': 3" << endl;
  cout << "Positions: 0 10 22" << endl;

  return 0;
}
