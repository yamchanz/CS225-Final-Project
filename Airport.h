#pragma once

#include <vector>
#include <algorithm>
#include <queue>

#include "graph.h"
#include "edge.h"
#include "Values.h"

//code is key
class Airport {
  public:
    Airport();
    long double findWeight(string code1, string code2);
    long double findDistance(pair<long double, long double> coord1, pair<long double, long double> coord2);
    pair<long double, long double> toRadians(const pair<long double, long double> coord);
    vector<Vertex> findShortestPath(Graph g, Vertex source, Vertex destination);
    //Nick a's maybe add stuff
    long double calcDistance(pair<long double, long double> coord1, pair<long double, long double> coord2);
    Airport(std::string portFile, std::string routeFile);
        
  private:
    Graph g_;
    Vertex startingVertex_;
    //new
    std::unordered_map<std::string, Values> airportList;

};












