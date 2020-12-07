
#include "Airport.h"
#include <iostream>
#include <stdlib.h>
#include <exception>

using std::string;

//Main constructor, builds based on our two full database txt data
Airport::Airport()
: g_(true,true)
{Airport("data/airports.txt", "data/routes.txt");}

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
                curr++;
                if (c == ',') {
                    commas++;
                    //parse the sections and save to the value keyed pair
                    if (curr-prev <= 1) {break;}
                    if (commas == 2) {
                        str = line.substr(prev + 1, curr-prev - 3);
                        V.name_ = str;}
                    else if (commas == 3) {
                        str = line.substr(prev + 1, curr-prev - 3);
                        V.city_ = str;}
                    else if (commas == 4) {
                        str = line.substr(prev + 1, curr-prev - 3);
                        V.country_ = str;}
                    //doesnt add the item if the code isn't exactly 3 letters
                    else if (commas == 5) {
                        str = line.substr(prev + 1, curr-prev - 3);
                        if (str.length() != 3) {
                            break;}
                        V.code_ = str;}
                    else if (commas == 7) {
                        //i have no idea why this is minus 1 and not 2
                        str = line.substr(prev, curr-prev - 1);
                        //catch blocks in case position does not have double data
                        try {V.latitude_ = std::stold(str);}
                        catch (std::exception& e) {
                            std::cout << "LATITUDE EXCEPTION" << std::endl;
                            continue;
                        }
                    }
                    else if (commas == 8) {
                        str = line.substr(prev, curr-prev - 1);
                        try{V.longitude_ = std::stold(str);}
                        catch (std::exception& e) {
                            std::cout << "LONGITUDE EXCEPTION" << std::endl;
                            continue;
                        }
                        //std::cout << V.to_string() << std::endl;
                        g_.insertVertex(V.code_);
                        airportList[V.code_] = V;
                    }
                    //std::cout << "P: " << prev << " C: " << curr << " " << str << std::endl;
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
            int commas2 = 0;
            int prev2 = 0;
            int curr2 = 0;
            string str2, source;
            //goes through each line, character by character
            for (char c : line2) {
                curr2++;
                if (c == ',') {
                    commas2++;
                    //parse source and destination 3 letter codes
                    if (curr2-prev2 <= 1) {break;}
                    str2 = line2.substr(prev2, curr2-prev2 - 1);
                    if (commas2 == 3) {source = str2;}
                    else if (commas2 == 5) {
                        //populates graph with weighted edge of distance
                        //if (source.length() != 3 || str2.length() != 3) {break;}
                        g_.insertEdge(source,str2);
                        g_.setEdgeWeight(source, str2, findWeight(source, str2) );
                    }
                    prev2 = curr2;
                }
            }
        }
    }
}

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

vector<Vertex> Airport::findShortestUnweightedPath(Graph g_, Vertex source, Vertex destination){
    unordered_map<Vertex, Vertex> prev; //stores previous vertices for every visited vertex
    std::queue<Vertex> q; //queues all vertices for the BFS
    unordered_map<Vertex, bool> visited; //keeps track of which vertices have been visited
    vector<Vertex> vertices = g_.getVertices(); //vertices from our graph

    //initializes our data structures
    for (unsigned i = 0; i < vertices.size(); i++) {
        if (vertices[i] == source) {
            visited[source] = true;
            prev[source] = destination; //no other vertex should have a predecessor of the destination
            q.push(source);
        } else {
            visited[vertices[i]] = false;
        }
    }

    bool flag = false; //used to exit while loop once our destination is found
    while (!(q.empty())) {
        Vertex v = q.front();
        q.pop();
        vector<Vertex> adj = g_.getAdjacent(v); //neighbors of current vertex

        //goes through current nodes neighbors and adds them to queue
        for (unsigned i = 0; i < adj.size(); i++) {
            if (visited[adj[i]] == false) {
                visited[adj[i]] = true; //marks vertex as visited
                prev[adj[i]] = v; //adds current vertex as predecessor for its neighbor
                q.push(adj[i]);

                //if the destination is reached, exit the for loop
                if (adj[i] == destination) {
                    flag = true;
                    break;
                }
            }
        }
        //if the destination has been found, exit the while loop
        if (flag) {
            break;
        }
    }

    vector<Vertex> path; //stores the vertices needed to form a path between the source and destination

    //if flag is still false, then the destination was never found
    if (flag == false) {
        std::cout<<"No path between source and destination exists \n";
        return path;
    } else {
        Vertex curr = destination;

        //add predecessors of the current vertex until the source is reached
        while(prev[curr] != destination) {
            path.push_back(curr);
            curr = prev[curr];
        }
        path.push_back(source); //add the source to the path
        std::reverse(path.begin(), path.end()); //reverse the path so that it goes from the source to the destination
        return path;
    }
}

vector<Vertex> Airport::findShortestWeightedPath(Graph g_, Vertex source, Vertex destination){
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
    
    bool flag = true;

    while (!(v.empty())) {
        std::pop_heap(std::begin(v), std::end(v), compare);
        Vertex min = v.back();
        v.pop_back();
        if (min == destination) {
            while (prev.find(min) != std::end(prev)) {
                path.push_back(min);
                min = prev[min];
            }
            flag = false;
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
    if (flag) {
        std::cout<<"No path between source and destination exists \n";
    }
    return path;
}
std::unordered_map<string, Values> Airport::getAirportList() {
    return airportList;
}
Graph Airport::getGraph() {
    return g_;
}

PNG* Airport::drawMap(vector<Vertex> vertices, vector<Edge> edges){
    PNG* map = new PNG;
    map->readFromFile("mercatorMap.png");


    // in progress..
    return map;
}