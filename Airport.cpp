#include "Airport.h"
#include <utility>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <algorithm>

Airport::Airport(   ){
    for(Vertex i : AirportList){
        g_.insertVertex(Vertex code);
    }
    for(Vertex j, k : RouteList){
        g_.insertEdge(Vertex code1, Vertex code2);
        long double weight = findWeight(Vertex code1, Vertex code2);
        g_.setEdgeWeight(Vertex code1, Vertex code2);
    }
}

long double Airport::findWeight(Vertex code1, Vertex code2){
    pair<long double, long double> coord1 = findCoord(Vertex code1);
    pair<long double, long double> coord2 = findCoord(Vertex code2);
    return calcDistance(coord1, coord2);
}

// lat is first, long is second
long double Airport::calcDistance(pair<long double, long double> coord1, pair<long double, long double> coord2){
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

pair<long double, long double> Airport::toRadians(const pair<long double, long double> coord){
	pair<long double, long double> temp;
	temp.first = coord.first * M_PI / 180;
	temp.second = coord.second * M_PI / 180;
	return temp; 
}

vector<Vertex> Airport::findShortestPath(Graph g_, Vertex source, Vertex destination){
    long double maxDist = 24859.734; //earth's circumference
    unordered_map<Vertex, double> distances;
    unordered_map<Vertex, Vertex> prev;
    vector<Vertex> vertices = g_.getVertices();
    vector<Vertex> v;
    vector<Vertex> path;

    auto compare = [&](Vertex left, Vertex right) { 
        return distances[left] > distances[right]; 
    };

    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == source) {
            distances[source] = 0;
        } else {
            distances[vertices[i]] = maxDist;
        }
        v.push_back(vertices[i]);
        std::push_heap(std::begin(v), std::end(v), compare);
    }
    
    while (!(v.empty())) {
        std::pop_heap(std::begin(v), std::end(v), compare);
        Vertex min = v.back();
        v.pop_back();
        if (min == destination) {
            while (prev.find(min) != std::end(prev)) {
                path.push_back(min);
                min = prev[min];
            }
            break;
        }
        if (distances[min] == maxDist) {
            break;
        }
        std::vector<Vertex> adj = g_.getAdjacent(min);
        for (int i = 0; i < adj.size(); i++) {
            double comp = distances[min] + findWeight(min, adj[i]);
            if (comp < distances[adj[i]]) {
                distances[adj[i]] = comp;
                prev[adj[i]] = min;
                std::make_heap(std::begin(v), std::end(v), compare);
            }
        }
    }
    return path;
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
