#include "Airport.h"
#include <fstream>
#include <utility>

using std::string;
using std::ifstream;

Airport::Airport(   ){
    for(i : AirportList){
        g_.insertVertex(Vertex code);
    }
    for(j : RouteList){
        g_.insertEdge(Vertex code1, Vertex code2);
        weight = findWeight(Vertex code1, Vertex code2);
        g_.setEdgeWeight(Vertex code1, Vertex code2);
    }
}

double Airport::findWeight(Vertex code1, Vertex code2){
    pair<double, double> coord1 = findCoord(Vertex code1);
    pair<double, double> coord2 = findCoord(Vertex code2);
    return findDistance(coord1, coord2);
}

double Airport::findDistance(pair<double, double> coord1, pair<double, double> coord2){
    double temp;
    // on geeksforgeeks
    return temp;
}

/*
Airport::Airport(string name, string city, string country, string code, double latitude, double longitude)
 : name_(name), city_(city), country_(country), code_(code), latitude_(latitude), longitude_(longitude)
{}

Airport::~Airport() {

}
Airport::Airport() {

}
*/

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