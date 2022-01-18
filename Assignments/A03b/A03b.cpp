/*****************************************************************************

*

* Author: Olamide

* Email:

* Label: A03b

* Title: Linked List Class

* Course: CMPS 3013

* Semester: Spring 2020

*

* Description:

* This program implements a class that allows a linked list to be used just like

* an array. It overloads the "[]" (square brackets) to simulate accessing seperate

* array elements, but really it traverses the list to find the specified node using

* an index value. It also overloads the "+" and "-" signs allowing a user to "add"

* or "push" items onto the end of the list, as well as "pop" items off the end of our

* array. This class is not meant to replace the STL vector library, its simply a project

* to introduce the beginnings of creating complex / abstract data types.

*

* Usage:

* - $ ./main

*

* Files:

* main.cpp : driver program with linked list implementationt

*****************************************************************************/

#include <iostream>

using namespace std;

int A[100];

// Definition of a node in linked list

struct Node {

int x; // value present in the node

Node *next; // hold the address of the next node

// present in the List

// Default constructor which creates a default node

Node() {

x = -1;

next = NULL;

}

// parametarised constuctor which creates a node with given key

Node(int n) {

x = n;

next = NULL;

}

};

/**

* List

*

* Description:

* The class implements linked list data structure

* with extra feautre to use '+' operator to concotonate the two lists

* also it defines the usage of [] operator which returns an

* int value as if the list were an array.

*

* Public Methods:

* List()

* void Push(int val)

* void Insert(int val)

* void PrintTail()

* string Print()

* int Pop()

* List operator+(const List &Rhs)

* List operator[](int index)

* ostream operator<<(ostream &os, List L)

*

* Usage:

*

* List L1; // Create instance of List

* L1.push(val) // insert node at the end of List

* L1.PrintTail(); // print last node of the list

* List L3 = L1 + L2; // to concatenate the two list and store

* // them in a new list

* L3[5] // to access a particular node of list

*

*/

class List {

private:

Node *Head; // points to the first node of the list

Node *Tail; // points to the last node of the list

int Size; // current number of nodes in the list

public:

/**

* Public : List

*

* Description:

* This constructor creates a empty list

*/

List() {

Head = Tail = NULL;

Size = 0;

}

/**

* Public : Push

*

* Description:

* This inserts a node at the end of the list

*

* Params:

* [int] val - value to be inserted

*

*/

void Push(int val) {

// allocate new memory and init node

Node *Temp = new Node(val);

// if it is empty

if (!Head && !Tail) {

Head = Tail = Temp;

} else {

// not empty then insert at the end of the list

Tail->next = Temp;

Tail = Temp;

}

Size++;

}

/**

* Public : Insert

*

* Description:

* inserts a node at the begining of the list

*

* Params:

* [int] val - value to be inserted

*

*/

void Insert(int val) {

// allocate new memory and init node

Node *Temp = new Node(val);

// figure out where it goes in the list

// insert at the beginning of the list

Temp->next = Head;

Head = Temp;

// if empty

if (!Tail) {

Tail = Head;

}

// increase size of the list

Size++;

}

/**

* Public : PrintTail

*

* Description:

* print last node of the list

*

*/

void PrintTail() {

// print last node of the list

cout << Tail->x << endl;

}

/**

* Public : Print

*

* Description:

* Describe the functions purpose
