#pragma once

#include <vector>
#include <algorithm>
#include <queue>

#include "graph.h"
#include "edge.h"
#include "Values.h"

class Airport {
  public:
    /**
     * Constructor to create a graph, `g_` representing all of the routes through
     * airports. Vertices are airport IATA codes, edges are routes and edge 
     * weights are distances.
     */
    Airport();
    /**
     * Constructor to create a graph, `g_` representing all of the routes through
     * airports. Vertices are airport IATA codes, edges are routes and edge 
     * weights are distances.
     * @param portFile - raw Airport data file to parse.
     * @param routeFile - raw Route data file to parse.  
     */
    Airport(std::string portFile, std::string routeFile);
    /**
     * Finds weights for each edge.
     * @param code1 - source IATA.
     * @param code2 - destination IATA.  
     * @returns weight for the edge.
     */
    long double findWeight(string code1, string code2);
    /**
     * Helper function for findWeight, calculates distance between two coordinates
     * on Earth.
     * @param coord1 - source pair of latitude, longitude coordinates.
     * @param coord2 - destination pair of latitude, longitude coordinates.  
     * @returns distance between two points.
     */
    long double calcDistance(pair<long double, long double> coord1, pair<long double, long double> coord2);
    /**
     * Helper function for calcDistance, converts pair of <latitude, longitude> from
     * degrees to radians.
     * on Earth.
     * @param coord - pair of latitude, longitude coordinates to convert.
     * @returns pair of <latitude, longitude> in radians.
     */
    pair<long double, long double> toRadians(const pair<long double, long double> coord);
    /**
     * Finds shortest path between two airport vertices using Dijkstra's algorithm.
     * @returns vector of vertices of path.
     */
    vector<Vertex> findShortestPath(Graph g, Vertex source, Vertex destination);
        
  private:
    Graph g_;
    Vertex startingVertex_;
    std::unordered_map<std::string, Values> airportList;

};












