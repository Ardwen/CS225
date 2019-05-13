/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    //vector<string> tmpvec_words;
    ifstream wordsFile(filename);
    string words;
    if(wordsFile.is_open()){
      while(getline(wordsFile,words)){
        //tmpvec_words.push_back(words);
        string line2 = words;
        std::sort(line2.begin(),line2.end());
        dict[line2].push_back(words);
      }//load all words to a vector
    }

}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    //split a word into its letter form and them sort for future comparison of two words
    for(auto & tmp_word : words){
        string line2 = tmp_word;
        std::sort(line2.begin(),line2.end());
        dict[line2].push_back(tmp_word);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> result;
    string line2 = word;
    std::sort(line2.begin(),line2.end());
    auto lookup = dict.find(line2);
    if(lookup!=dict.end()){
        for(auto & it : lookup -> second){
            result.push_back(it);
          }
        }
      return result;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector< vector<string> > result;
    for(auto & words : dict){
      vector<string> tmp = get_anagrams(words.first);
      if(tmp.size()>1){//empty tmp may result; must use greater than 1
        result.push_back(tmp);
      }
    }
    return result;

}
