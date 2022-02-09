//////////////////////////////////////////////////////////////////////////////

//

// Author: Olamide Adesan

// Email: olamideadesan2016@gmail.com

// Label: P02

// Title: Program 2- Linear Time Lookup

// Course: 3013

// Semester: Spring 2021

//

// Description: Program that will read in a dictionary file and store it in a linked list.

// 

//

//

/////////////////////////////////////////////////////////////////////////////////


#include "mygetch.hpp"
#include <bits/stdc++.h>
#include "termcolor.hpp"
#include "timer.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Node of the linkedList
struct wordNode{
 string word;  // to store word from dictionary
 wordNode *next; // to make a link between nodes
};

// head of the linkedlist
wordNode * head = NULL;

/**
 * Description:
 *      Originally wrote this to count size of input file so
 *      I could allocate enough memory for an array of strings
 *      but I went with a vector below. But I'm keeping it and
 *      using it anyway!
 * Params:
 *      string file_name - file to get the line count
 * 
 * Returns:
 *      int - line count
 */
int CountLines(string file_name) {

  ifstream inFile(file_name);
    return count(istreambuf_iterator<char>(inFile),istreambuf_iterator<char>(), '\n');
}

/**
 * Description:
 *      insert a node in the linkedlist
 * Params:
 *      string str - word to be inserted
 * 
 * Returns:
 *      NILL
 */
void insert(string str){
  wordNode * new_node = new wordNode;
  new_node-> word = str;
  new_node-> next = NULL;

  if(head == NULL){
    head = new_node;
  }
  else{
    wordNode * temp = head;
    while(temp->next != NULL){
      temp = temp->next;
    }

    temp->next = new_node;
  }
}

/**
 * Description:
 *      Loads a file of strings (words, names, whatever) reading them in
 *      with one word per line. So words must be delimited by newlines '\n'
 * Params:
 *      string file_name - file to get the line count
 * 
 * Returns:
 *      NIL
 */
void Loadwords(string file_name) {
    ifstream fin;                            // file to get animal names
    int count = (CountLines(file_name) + 1); // get size of input file
                

    fin.open(file_name); // open file for reading

    // knowing the size of the file lets us treat
    // it like an array without using .push_back(value)
    string str;
    for (int i = 0; i < count; i++) {
        fin >> str;  // read in words
        insert(str);
    }
}
  
/**
 * Description:
 *      Finds partial matches in an array of strings and returns them. 
 * Params:
 *      int*            counts      - counts to store the number of matching strings found
 *      string          substring   - substring to search for in each word
 * 
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> Findwords(int* counts, string substring) {
  vector<string> matches; // to hold any matches
  wordNode* temp = head;
  
  *counts = 0;
  while(temp != NULL){
    string word = temp->word;
    if(word.substr(0,substring.length()) == substring){
      *counts = *counts+1;
      if(matches.size()<10){
        matches.push_back(word);
      }
    }
    temp = temp->next;
  }
return matches;
}

int main() {
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    vector<string> matches; // any matches found in vector of words
    int counts;             // count to number of matching strings
    counts = 0;

    cout << termcolor::green;
    cout<<"Loading the dictionary ....\n";
    cout << termcolor::reset;
  
    Timer T;   // create a timer
    T.Start(); // start it

    Loadwords("dictionary.txt");

    T.End(); // end the current timer

    cout.setf(ios::fixed, ios::floatfield);
    cout.setf(ios::showpoint);
  
    // print out how long it took to load the words file
    cout << T.Seconds() << " seconds to load the dictionary" << endl;
    cout << "Type keys and watch what happens. Type capital Z to quit.\n" << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') {

        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127) {
            if (word.size() > 0) {
                word = word.substr(0, word.size() - 1);
            }
        } else {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) {
                k += 32;
            }
            word += k; // append char to word
        }

      
        T.Start();
        matches = Findwords(&counts, word);
        T.End();
        

        if ((int)k != 32) { // if k is not a space print it
            cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            cout << "words Found: "<<counts<<" in "<<T.Seconds()<<" seconds\n";
            cout << termcolor::green;
            // This prints out all found matches
            for (int i = 0; i < matches.size(); i++) {
                cout << matches[i] << " ";
            }
            cout << termcolor::reset << endl
                 << endl;
        }
      
    }
    return 0;
}
