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
    vector<Edge> findShortestPath(Graph g, Vertex source, Vertex destination);
    pair<long double, long double> calcDistance(pair<long double, long double> coord1, pair<long double, long double> coord2);
    pair<long double, long double> toRadians(const pair<long double, long double> coord)

  private:
    Graph g_;
    Vertex startingVertex_;
};












