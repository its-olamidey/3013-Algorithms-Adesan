/************************************************************
 *
 *    Author:           Olamide Adesdan
 *    Email:            Olamideadesan2016@gmail.com
 *    Label:            P04
 *    Title:            Processing in Trie Tree Time
 *    Course:           CMPS 3013
 *    Semester:         Spring 2022
 *    Description:
 *         To generate a dictionary, this software uses a Trie data structure. 
 *         It will read the dictionary terms from a file. The application 
 *         will calculate the time it takes to discover the words and display 
 *         the top ten results, as well as using getching to hold keyboard input.
 *      
 *    Files:
 *         main.cpp
 *         Timer.hpp
 *         mygetch.hpp
 *         termcolor.hpp
 *         dictionary.txt
 *
 *    Usage:
 *           main.cpp         : driver program
 *             
 *           dictionary.txt   : Input file
 *
 *           
 *
 ****************************************************************/

#include "mygetch.hpp"

#include <bits/stdc++.h>

#include "termcolor.hpp"

#include "timer.hpp"

#include <fstream>

#include <iostream>

#include <vector>

using namespace std;

/**
 * TrieNode
 *
 * Description:
 *      A struct to create all nodes in the Trie Tree.
 *      This function is only called in the Trie class.
 *      Each node keeps a flag to know if a word ends 
 *      at its location and will create and point to
 *      26 individual pointers, each one representing
 *      a letter of the alphabet to move to for the next
 *      letter in the word. 
 * 
 * Public Methods:
 *      - TrieNode()
 * 
 * Private Methods:
 *      - None
 *
 * Usage:
 *
 *  TrieNode Q;
 * 
 */
struct TrieNode {
  bool isLeaf; //Flag to determine if a word ends here
  TrieNode * character[26]; //Point to all letters of alphabet

  TrieNode() {
    isLeaf = false; //Not yet considered the end of a word

    for (int i = 0; i < 26; i++) //Create pointer for each alphabet letter
    {
      character[i] = nullptr; //Set pointers to NULL/No new letter yet
    }
  }
};

/**
 * Trie
 *
 * Description:
 *      A Trie Tree class to hold the words from the txt file. The trie
 *      stores words by its individual letters pointing to a TrieNode containing
 *      the next letter in the word. When the last letter of a word is added to 
 *      the Trie tree, then the node for that letter will be marked true as a word
 *      to indicate that a word ends at this TrieNode. When a given word is typed
 *      the user, the class can determine how many substrings match the given word
 *      and store the words in a vector to print out the first ten matching words
 *      and the total numbers of matches found overall in the Trie tree.
 *      
 *
 * Public Methods:
 *      - Trie()
 *      - void Insert(string)
 *      - int find_all(string)
 *      - void PrintSuggested()
 * 
 * Private Methods:
 *      - void find_all(TrieNode*&, string)
 *
 * Usage:
 *
 *  Trie J;
 *  J.Insert("dict_word");
 *  int num = J.find_all("words");
 *  J.PrintSuggested();
 * 
 */
class Trie {
  private:
    TrieNode * root; //Head of the Trie tree, pointing to alphabet
  vector < string > results; //Vector of matching words

  public:
    /**
     * Trie
     *    Default constructor for Trie class. Creates a TrieNode
     *    pointing to all 26 letters of the alphabet with each pointer
     *    set to NULL.
     * Params:
     *    None
     *
     * Returns:
     *    Void
     */
    Trie() {
      root = new TrieNode;
    }

  /**
   * Public: insert
   *    Function to directly place words into
   *    the Trie. Traverses through each letter of the word
   *    and if the Trie tree does not point to the next letter, then
   *    it will create a new TrieNode to go the the next letter. Once the
   *    last letter of the word has been reached, then the function will 
   *    set the last letter's pointer isLeaf to true to indicate that a 
   *    word ends at that location. 
   * Params:
   *    string :   word string to go into data
   *
   * Returns:
   *    void
   */
  void insert(string word) {
    TrieNode * currentLetter = root; // start from the root node

    for (int i = 0; i < word.length(); i++) //Continue til word's last letter
    {

      //Create a new node if path doesn't exist
      if (currentLetter -> character[word[i] - 97] == nullptr) {
        //Implement new TrieNode
        currentLetter -> character[word[i] - 97] = new TrieNode();
      }

      //Go to next letter's node of the word
      currentLetter = currentLetter -> character[word[i] - 97];
    }

    //Last letter of word/ Mark Node as complete word/leaf
    currentLetter -> isLeaf = true;

  }

  /**
   * Public: find_all
   *    This function takes a given word and traverses through the Trie
   *    to find all matching words and stores the matches in a vector. 
   *    This function calls the private find_all method to go through
   *    the tree recursively once it reaches to typed word's substring.
   *    After finding and storing all matches, the function then returns
   *    the size of the vector to give the total number of matches found. 
   * Params:
   *    string   :  Substring word to find matches of in tree
   *
   * Returns:
   *     int   :   Total number of similar words in Trie tree
   */
  int find_all(string Word) {
    TrieNode * currentLetter = root; //Start at the beginning of tree

    results.clear(); //Remove any previous matches added

    for (int i = 0; i < Word.length(); i++) //Traverse through tree until
    // pointing at last letter of input
    {
      //Word doesn't exist in Trie Tree
      if (currentLetter -> character[Word[i] - 97] == nullptr) {
        return 0; //No words match: leave function
      }
      //Move to next letter node
      currentLetter = currentLetter -> character[Word[i] - 97];

    }

    find_all(currentLetter, Word); //Call private function to find matches

    return results.size(); //Return number of matches found

  }

  /**
   * Public: PrintSuggested
   *    This function prints out the first 10 words found in 
   *    the Trie tree that matches with the typed word given by
   *    the user. The matches are found through the find_all method
   *    and stored into the vector results. This function prints
   *    out the first 10 words of that vector to the screen. If less
   *    than 10 words match in the Trie then the function will
   *    only print out the number of matches in the vector. The
   *    first word printed will be colored red and the rest of 
   *    the matching words will be printed in normal color. 
   * Params:
   *    None
   *
   * Returns:
   *     Void
   */
  void PrintSuggested() {
    if (results.size() >= 10) //At least 10 matches found
    {
      for (int i = 0; i < 10; i++) //Print out first 10 matches
      {
        if (i == 0) //First word to be printed
        {
          cout << termcolor::red; //Print in red color
        }

        cout << results[i] << "   "; //Print matching word to screen
        cout << termcolor::reset; //Print in normal color
      }
    } else //Less than 10 words match in tree
    {
      for (int i = 0; i < results.size(); i++) { //Print all matches found
        if (i == 0) {
          cout << termcolor::red; //Print first word in red
        }
        cout << results[i] << "   "; //Print matching word to screen
        cout << termcolor::reset; //Print in normal color
      }
    }
  }

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
    return count(istreambuf_iterator < char > (inFile), istreambuf_iterator < char > (), '\n');
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
    ifstream fin; // file to get animal names
    int count = (CountLines(file_name) + 1); // get size of input file

    fin.open(file_name); // open file for reading

    // knowing the size of the file lets us treat
    // it like an array without using .push_back(value)
    string str;
    for (int i = 0; i < count; i++) {
      fin >> str; // read in words
      insert(str);
    }
  }

  private:
    /**
     * Private: find_all
     *    This function is called from the public find_all
     *    method to traverse through the trie tree and find all
     *    nodes that are marked as a word(Leaf). This function gets
     *    called once the substring to be matched has already been pointed
     *    to and now each alphabet pointer of the last letter of the given 
     *    word is to be looked at to find all paths leading to a word. If 
     *    a word is found then it is added to the vector results to be stored
     *    in order to know the total matches and suggestions.
     * Params:
     *    TrieNode*&   : Location pointing to next letter to be checked for words
     *    string       : Current set of letters making up a possible word
     *
     * Returns:
     *    None
     */
    void find_all(TrieNode * & curr, string word) {
      if (curr -> isLeaf) //The node is the last letter of a word
      {
        results.push_back(word); //Add the word to the vector of matches
      }

      for (int i = 0; i < 26; i++) //Check to see if node points to more words
      {
        if (curr -> character[i]) //Check entire alphabet for pointers-not NULL
        { //Recall method to get new word
          find_all(curr -> character[i], word + char(i + 97));
          //Add letter to formed word                      
        }
      }

    }
};

int main() {
  Trie * DictWords = new Trie();
  char k; // holder for character being typed
  string word = ""; // var to concatenate letters to
  int counts; // count to number of matching strings
  counts = 0;

  cout << termcolor::green;
  cout << "Loading the dictionary ....\n";
  cout << termcolor::reset;

  Timer T; // create a timer
  T.Start(); // start it

  DictWords -> Loadwords("dictionary.txt");

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
    if ((int) k == 127) {
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
      if ((int) k < 97) {
        k += 32;
      }
      word += k; // append char to word
    }

    T.Start();
    counts = DictWords -> find_all(word);
    T.End();

    if ((int) k != 32) { // if k is not a space print it
      cout << "Keypressed: " << termcolor::blue << k << " = " << (int) k << termcolor::reset << endl;
      cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
      cout << "words Found: " << counts << " in " << T.Seconds() << " seconds\n";
      cout << termcolor::green;
      // This prints out all found matches
      DictWords -> PrintSuggested();
      cout << termcolor::reset << endl <<
        endl;
    }

  }
  return 0;
}
