///////////////////////////////////////////////////////////////////////////////

//

// Author: Olamide Adesan

// Email: olamideadesan2016@gmail.com

// Label: P01

// Title: Program 1 - Resizing the stack

// Course: 3013

// Semester: Spring 2021

//

// Description:

// Implementation of array based stack

//

//

/////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <fstream>

#include <iomanip>

using namespace std;

/**

* ArrayStack

*

* Description:

* This class implements array based stack

*

* Public Methods:

* ArrayStack()

* ArrayStack(double fullThresh)

* ArrayStack(double fullThresh, double emptyThresh)

* ArrayStack(double fullThresh, double emptyThresh, double enlargeThresh)

* ArrayStack(double fullThresh, double emptyThresh, double enlargeThresh, double shrinkThresh)

* ArrayStack(int s)

* bool Empty()

* bool Full()

* bool TooSmall()

* int Peek()

* void Pop()

* void Print()

* void CheckResize()

* void Push(int x)

* void ContainerGrow()

* void ContainerShrink()

*

* Usage:

* - See main program

*

*/

class ArrayStack {

private:

int * A; // pointer to array of int's

int top; // top of stack

public:

double size; // current max stack size

int ct = 0; // count of times stack resizes

double fullThresh; // Too Full Threshold

double emptyThresh; //Too Empty Threshold

double enlargeThresh; //Enlarging Threshold

double shrinkThresh; //Shrinking Threshold

/**

* ArrayStack

*

* Description:

* Default Constructor

*

* Params:

* - None

*

* Returns:

* - NULL

*/

ArrayStack() {

size = 10;

A = new int[size];

top = -1;

fullThresh = 1;

emptyThresh = 0.15;

enlargeThresh = 2;

shrinkThresh = 0.5;

}

/**

* ArrayStack

*

* Description:

* overloaded Constructor

*

* Params:

* [double] Too Full Threshold - threshold to grow

*

* Returns:

* - NULL

*/

ArrayStack(double ft) {

size = 10;

A = new int[size];

top = -1;

this -> fullThresh = ft;

emptyThresh = 0.15;

enlargeThresh = 2;

shrinkThresh = 0.5;

}

/**

* ArrayStack

*

* Description:

* overloaded Constructor

*

* Params:

* [double] Too Full Threshold - threshold to grow

* [double] Too Empty Threshold - threshold to shrink

*

* Returns:

* - NULL

*/

ArrayStack(double fullThresh, double emptyThresh) {

size = 10;

A = new int[size];

top = -1;

this -> fullThresh = fullThresh;

this -> emptyThresh = emptyThresh;

enlargeThresh = 2;

shrinkThresh = 0.5;

}

/**

* ArrayStack

*

* Description:

* overloaded Constructor

*

* Params:

* [double] Too Full Threshold - threshold to grow

* [double] Too Empty Threshold - threshold to shrink

* [double] Enlarging Threshold - how much to grow

*

* Returns:

* - NULL

*/

ArrayStack(double fullThresh, double emptyThresh, double enlargeThresh) {

size = 10;

A = new int[size];

top = -1;

this -> fullThresh = fullThresh;

this -> emptyThresh = emptyThresh;

this -> enlargeThresh = enlargeThresh;

shrinkThresh = 0.5;

}

/**

* ArrayStack

*

* Description:

* overloaded Constructor

*

* Params:

* [double] Too Full Threshold - threshold to grow

* [double] Too Empty Threshold - threshold to shrink

* [double] Enlarging Threshold - how much to grow

* [double] Shrinking Threshold - how much to shrink

*

* Returns:

* - NULL

*/

ArrayStack(double fullThresh, double emptyThresh, double enlargeThresh, double shrinkThresh) {

size = 10;

A = new int[size];

top = -1;

this -> fullThresh = fullThresh;

this -> emptyThresh = emptyThresh;

this -> enlargeThresh = enlargeThresh;

this -> shrinkThresh = shrinkThresh;

}

/**

* ArrayStack

*

* Description:

* Constructor size param

*

* Params:

* - int size

*

* Returns:

* - NULL

*/

ArrayStack(int s) {

size = s;

A = new int[s];

top = -1;

fullThresh = 1;

emptyThresh = 0.15;

enlargeThresh = 2;

shrinkThresh = 0.5;

}

/**

* Public bool: Empty

*

* Description:

* Stack empty?

*

* Params:

* NULL

*

* Returns:

* [bool] true = empty

*/

bool Empty() {

return (top <= -1);

}

/**

* Public bool: Full

*

* Description:

* Stack full?

*

* Params:

* NULL

*

* Returns:

* [bool] true = full

*/

bool Full() {

return (top >= (size * fullThresh) - 1);

}

/**

* Public bool: TooSmall

*

* Description:

* Stack too small?

*

* Params:

* NULL

*

* Returns:

* [bool] true = full

*/

bool TooSmall() {

if (size < 10)

return true;

return (size > 10 && top <= size * emptyThresh);

}

/**

* Public int: Peek

*

* Description:

* Returns top value without altering the stack

*

* Params:

* NULL

*

* Returns:

* [int] top value if any

*/

int Peek() {

if (!Empty()) {

return A[top];

}

return -99; // some sentinel value

// not a good solution

}

/**

* Public int: Pop

*

* Description:

* Returns top value and removes it from stack

*

* Params:

* NULL

*

* Returns:

* [int] top value if any

*/

void Pop() {

if (!Empty()) {

top--;

}

CheckResize();

}

/**

* Public void: Print

*

* Description:

* Prints stack to standard out

*

* Params:

* NULL

*

* Returns:

* NULL

*/

void Print() {

for (int i = 0; i <= top; i++) {

cout << A[i] << " ";

}

cout << endl;

}

/**

* Public void: CheckResize

*

* Description:

* Resizes the container for the stack by doubling

* its capacity or havling its capacity

*

* Params:

* NULL

*

* Returns:

* NULL

*/

void CheckResize() {

if (Full()) {

ContainerGrow();

ct++;

}

if (TooSmall()) {

ContainerShrink();

ct++;

}

}

/**

* Public bool: Push

*

* Description:

* Adds an item to top of stack
*

* Params:

* [int] : item to be added

*

* Returns:

*

*/

void Push(int x) {

CheckResize();

A[++top] = x;

}

/**

* Public void: ContainerGrow

*

* Description:

* Resizes the container for the stack by increasing

* its capacity

*

* Params:

* NULL

*

* Returns:

* NULL

*/

void ContainerGrow() {

int newSize = size * enlargeThresh; // double size of original

int * B = new int[newSize]; // allocate new memory

for (int i = 0; i < size; i++) { // copy values to new array

B[i] = A[i];

}

delete[] A; // delete old array

size = newSize; // save new size

A = B; // reset array pointer

}

/**

* Public void: ContainerShrink

*

* Description:

* Resizes the container for the stack by reducing

* its capacity

*

* Params:

* NULL

*

* Returns:

* NULL

*/

void ContainerShrink() {

int newSize = size * shrinkThresh; // half size of original

int * C = new int[newSize]; // allocate new memory

for (int i = 0; i < newSize; i++) { // copy values to new array

C[i] = A[i];

}

delete[] A; // delete old array

size = newSize; // save new size

A = C; // reset array pointer

}

};

// MAIN DRIVER

// Simple Array Based Stack Usage:

int main(int argc, char ** argv) {

ArrayStack * stack;

if (argc == 1) {

stack = new ArrayStack();

} else if (argc == 2) {

stack = new ArrayStack(atof(argv[1]));

} else if (argc == 3) {

stack = new ArrayStack(atof(argv[1]), atof(argv[2]));

} else if (argc == 4) {

stack = new ArrayStack(atof(argv[1]), atof(argv[2]), atof(argv[3]));

} else if (argc == 5) {

stack = new ArrayStack(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]));

}

ofstream outfile;

outfile.open("Prog 1 output");

outfile << "######################################################################\n" <<

" Program 1 - Resizing the Stack\n" <<

" CMPS 3013\n" <<

" Olamide Adesan \n\n";

ifstream fin;

int num; //Number from infile

int max = stack -> size; //Tracks stack max size

int FinSize; //Is the final size of stack

fin.open("nums_test.dat");

while (!fin.eof()) {

fin >> num;

if (num % 2 == 0) {

stack -> Push(num);

if (max < stack -> size) {

max = stack -> size;

}

} else {

stack -> Pop();

}

FinSize = stack -> size;

}

int count = stack -> ct; //Tracks number of time stack resizes
  outfile << " Max Stack Size: " <<

max <<

"\n End Stack Size: " <<

stack->size <<

"\n Stack Resized: " <<

count <<

" times\n\n" <<

"######################################################################";

outfile.close();

return 0;

}
