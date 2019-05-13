/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    ifstream wordsFile(word_list_fname);
    string words;
    if(wordsFile.is_open()){
      while(getline(wordsFile,words)){
        string w1 = words.substr(1);
        string w2 = words[0] + words.substr(2);
        if (d.homophones(words,w1) && d.homophones(words,w2)){
          ret.push_back(std::make_tuple(words,w1,w2));
      }//load all words to a vector
    }
  }
    /* Your code goes here! */
    return ret;
  }
