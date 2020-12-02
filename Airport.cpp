#include "Airport.h"
#include <fstream>

using std::string;
using std::ifstream;

Airport::Airport(string name, string city, string country, string code, double latitude, double longitude)
 : name_(name), city_(city), country_(country), code_(code), latitude_(latitude), longitude_(longitude)
{}

Airport::~Airport() {

}
Airport::Airport() {

}


/* FROM ANAGRAM
ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            if (dict.find(word) == dict.end()) {
                string s = word;
                std::sort(s.begin(), s.end());
                dict[word] = vector<string>();
                dict[word].push_back(s);
            }
        }
    }
    */