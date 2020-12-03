#pragma once

#include <vector>
#include <algorithm>
#include <queue>

#include "graph.h"
#include "edge.h"

//code is key
class Airport {
  public:
    Airport();
    long double findWeight(Vertex code1, Vertex code2);
    long double findDistance(pair<long double, long double> coord1, pair<long double, long double> coord2);
    pair<long double, long double> toRadians(const pair<long double, long double> coord);
    vector<Vertex> findShortestPath(Graph g, Vertex source, Vertex destination);
        
  private:
    Graph g_;
    Vertex startingVertex_;
};












