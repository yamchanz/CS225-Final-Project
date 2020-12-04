#include "Airport.h"
#include <fstream> // new
#include <utility>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "Values.h"

using std::string;

//NICK A's ITERATION ####################################33
//Main constructor, builds based on our two full database txt data
Airport::Airport()
: g_(true,true)
{Airport("airports.txt", "routes.txt");}

//builds graph, and unorderedmap of airports, where edges are the routes
Airport::Airport(std::string portFile, std::string routeFile)
: g_(true,true)
{
    std::ifstream airportFile(portFile);
    string line;
    if (airportFile.is_open()) {
        while (getline(airportFile, line)) {
            Values V = Values();
            int commas = 0;
            int prev = 0;
            int curr = 0;
            string str;
            //goes through each line, character by character
            for (char c : line) {
                if (c == ',') {
                    commas++;
                    curr++;
                    //parse the sections and save to the value keyed pair
                    str = line.substr(prev + 1, curr-prev);
                    if (commas == 2) {V.name_ = str;}
                    else if (commas == 3) {V.city_ = str;}
                    else if (commas == 4) {V.country_ = str;}
                    //doesnt add the item if the code isn't exactly 3 letters
                    else if (commas == 5) {if (str.length() != 3) {continue;}
                        V.code_ = str;}
                    else if (commas == 7) {V.latitude_ = std::stod(str);}
                    else if (commas == 8) {
                        V.longitude_ = std::stod(str);

                        g_.insertVertex(V.code_);
                        airportList[V.code_] = V;
                    }
                    prev = curr;
                }
            }
        }
    }

    //populates edges
    std::ifstream edgeFile(routeFile);
    string line2;
    if (edgeFile.is_open()) {
        while (getline(edgeFile, line2)) {
            int commas = 0;
            int prev = 0;
            int curr = 0;
            string str, source;
            //goes through each line, character by character
            for (char c : line2) {
                if (c == ',') {
                    commas++;
                    curr++;
                    //parse source and destination 3 letter codes
                    str = line2.substr(prev + 1, curr-prev);
                    if (commas == 3) {source = str;}
                    else if (commas == 5) {
                        //populates graph with weighted edge of distance
                        g_.insertEdge(source,str);
                        g_.setEdgeWeight(source, str, findWeight(source, str) );
                    }
                    prev = curr;
                }
            }
        }
    }
}
//###############################################333



/*Airport::Airport(   ){
    for(Vertex i : AirportList){
        g_.insertVertex(Vertex code);
    }
    for(Vertex j, k : RouteList){
        g_.insertEdge(Vertex code1, Vertex code2);
        long double weight = findWeight(Vertex code1, Vertex code2);
        g_.setEdgeWeight(Vertex code1, Vertex code2);
    }
}*/

long double Airport::findWeight(string code1, string code2) {
    Values src = airportList[code1];
    Values des = airportList[code2];
    pair<long double, long double> coord1(src.latitude_, src.longitude_);
    pair<long double, long double> coord2(des.latitude_, des.longitude_);
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
	ans = asin(sqrt(ans) * 2); 
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

    for (unsigned i = 0; i < vertices.size(); i++) {
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
        for (unsigned i = 0; i < adj.size(); i++) {
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
/*
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
}*/
/*
pair<long double, long double> Airport::toRadians(const pair<double, double> coord){
	pair<long double, long double> temp;
	temp.first = coord.first * M_PI / 180;
	temp.second = coord.second * M_PI / 180;
	return temp; 
}*/



////////////////////////////////////////////////////////////////////////////////////////////