#pragma once

#include <vector>
#include <algorithm>
#include <queue>

#include "graph.h"
#include "edge.h"


using std::string;
//code is key
class Airport {
  public:
    Airport();
    findWeight(Vertex code1, Vertex code2);
    findDistance(pair<double, double> coord1, pair<double, double> coord2);
/*
    Airport(string name, string city, string country, string code, double latitude, double longitude);
    ~Airport();
    Airport();
    string name_;
    string city_;
    string country_;
    string code_;
    double latitude_;
    double longitude_;
    private:
*/
  private:
    Graph g_;
    Vertex startingVertex_;
};












