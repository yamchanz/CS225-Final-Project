#include "Airport.h"
#include <utility>
#include <cmath>

Airport::Airport(   ){
    for(Vertex i : AirportList){
        g_.insertVertex(Vertex code);
    }
    for(Vertex j, k : RouteList){
        g_.insertEdge(Vertex code1, Vertex code2);
        double weight = findWeight(Vertex code1, Vertex code2);
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

int Airport::minDistance(Graph g_, double distances[], bool included[]) {
    double min = 24,859.734; //earth's circumference
    int minIdx;
    std::vector<Vertex> vertices = g_.getVertices();
    for (int i = 0; i < vertices.size(); i++) {
        if (!(included[i]) && distances[i] <= min) {
            min = dist[i];
            minIdx = i;
        }
    }
    return minIdx;
}

vector<Edge> Airport::findShortestPath(Graph g_, Vertex source, Vertex destination){
    double maxDist = 24,859.734; //earth's circumference

    std::vector<Vertex> vertices = g_.getVertices();
    int sourceIdx;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == source) {
            sourceIdx = i;
            break;
        }
    }
    double distances[g_.getVertices().size()];
    bool included[g_.getVertices().size()];
    for (int i = 0; i < g_.getVertices().size(); i++) {
        distances[i] = maxDist;
        included[i] = false;
    }
    distances[sourceIdx] = 0;

    for (int i = 0; i < vertices.size() - 1; i++) {
        int u = minDistance
    }
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

// lat is first, long is second
long double Airport::calcDistance(pair<double, double> coord1, pair<double, double> coord2){
	pair<long double, long double> radCoord1 = toRadians(coord1);
	pair<long double, long double> radCoord2 = toRadians(coord2);
	long double dlong = radCoord2.second - radCoord1.second;
	long double dlat = radCoord2.first - radCoord1.first;
	long double ans = pow(sin(dlat / 2), 2) + 
			      cos(radCoord1.first) * cos(radCoord2.first) *
			      pow(sin(dlong / 2), 2);
	ans = asin(sqrt(ans) * 2; 
	long double R = 3958.8;
	return ans * R;
}

pair<long double, long double> Airport::toRadians(const pair<double, double> coord){
	pair<long double, long double> temp;
	temp.first = coord.first * M_PI / 180;
	temp.second = coord.second * M_PI / 180;
	return temp; 
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