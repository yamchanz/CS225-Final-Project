#pragma once

#include <fstream> 
#include <utility>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>

#include "graph.h"
#include "edge.h"
#include "Values.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;
using namespace cs225;

class Airport {
  public:
    /**
     * Constructor to create a graph, `g_`, representing all of the routes through
     * airports. Vertices are airport IATA codes, edges are routes and edge 
     * weights are distances.
     */
    Airport();
    /**
     * Constructor to create a graph, `g_`, representing all of the routes through
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
     * @param coord1 - source pair of <latitude, longitude> coordinates.
     * @param coord2 - destination pair of <latitude, longitude> coordinates.  
     * @returns distance between two points.
     */
    long double calcDistance(pair<long double, long double> coord1, pair<long double, long double> coord2);
    /**
     * Helper function for calcDistance, converts pair of <latitude, longitude> from
     * degrees to radians.
     * on Earth.
     * @param coord - pair of <latitude, longitude> coordinates to convert.
     * @returns pair of <latitude, longitude> in radians.
     */
    pair<long double, long double> toRadians(const pair<long double, long double> coord);
    /**
     * Finds shortest path between two airport vertices using BFS and not factoring in edge weights
     * @param g - graph of the airports
     * @param source - departure airport
     * @param destination - arrival aiport
     * @returns vector of vertices of path.
     */
    vector<Vertex> findShortestUnweightedPath(Vertex source, Vertex destination);
    vector<Vertex> findShortestUnweightedPath(Graph g, Vertex source, Vertex destination);
    /**
     * Finds shortest path between two airport vertices using Dijkstra's algorithm.
     * @param g - graph of the airports (defaults to g_ -> private variable if not given)
     * @param source - departure airport
     * @param destination - arrival aiport
     * @returns vector of vertices of path.
     */
    vector<Vertex> findShortestWeightedPath(Vertex source, Vertex destination);
    vector<Vertex> findShortestWeightedPath(Graph g, Vertex source, Vertex destination);
    /**
     * Draws vertices and edges onto a mercator projection PNG.
     * Using mercator image from Geocart map projection software 
     * Needs Graph g_ to be subset of data to work. 
     * @returns PNG of mercator map with graph.
     */
    PNG* drawMap();
    /**
     * Helper for drawMap().
     * @param map - PNG to edit
     * @param sLat - source latitude in a route
     * @param sLong - source longitude in a route
     * @param dLat - destination latitude in a route
     * @param dLong - destination longitude in a route
     */
    void drawMapHelper(PNG* map, long double sLat, long double sLong, long double dLat, long double dLong);
    /**
     * Converts coordinates to pair of x, y values for PNG output.
     * @param latitude 
     * @param longitude
     * @returns pair of x, y cootdinates
     */
    pair<int, int> coordToXY(long double latitude, long double longitude);
    /**
     * @returns airportList private variable.
     */ 
    std::unordered_map<string, Values> getAirportList();
    /** 
     * @returns g_ (graph) private variable.
     */ 
    Graph getGraph();

    void drawPath(vector<Vertex> path);
  private:
    Graph g_;
    Vertex startingVertex_;
    std::unordered_map<std::string, Values> airportList;

};












