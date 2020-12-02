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

vector<Edge> Airport::findShortestPath(Vertex code1, Vertex code2){
/*
Dijkstra(Graph, source, destination):

  initialize distances  // initialize tentative distance value
  initialize previous   // initialize a map that maps current node -> its previous node
  initialize priority_queue   // initialize the priority queue
  initialize visited

  while the top of priority_queue is not destination:
      get the current_node from priority_queue
      for neighbor in current_node's neighbors and not in visited:
          if update its neighbor's distances:
              previous[neighbor] = current_node
      save current_node into visited

  extract path from previous
  return path and distance
*/
}



////////////////////////////////////////////////////////////////////////////////////////////


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