
#include "Airport.h"
#include <iostream>
#include <stdlib.h>
#include <exception>
#include <algorithm>

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
                    
                    if (commas == 2) {
                        if (curr-prev <= 1) {break;}
                        str = line.substr(prev + 1, curr-prev - 3);
                        V.name_ = str;}
                    else if (commas == 3) {
                        if (curr-prev <= 1) {break;}
                        str = line.substr(prev + 1, curr-prev - 3);
                        V.city_ = str;}
                    else if (commas == 4) {
                        if (curr-prev <= 1) {break;}
                        str = line.substr(prev + 1, curr-prev - 3);
                        V.country_ = str;}
                    //doesnt add the item if the code isn't exactly 3 letters
                    else if (commas == 5) {
                        if (curr-prev <= 1) {break;}
                        str = line.substr(prev + 1, curr-prev - 3);
                        if (str.length() != 3) {
                            break;}
                        V.code_ = str;}
                    else if (commas == 7) {
                        if (curr-prev <= 1) {break;}
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
                        if (curr-prev <= 1) {break;}
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
                    str2 = line2.substr(prev2, curr2-prev2 - 1);
                    if (commas2 == 3) {
                        if (curr2-prev2 <= 1) {break;}
                        source = str2;
                    }
                    else if (commas2 == 5) {
                        if (curr2-prev2 <= 1) {break;}
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
	ans = asin(sqrt(ans)) * 2;
	long double R = 3958.8;
	return ans * R;
}

pair<long double, long double> Airport::toRadians(const pair<long double, long double> coord){
	pair<long double, long double> temp;
	temp.first = coord.first * M_PI / 180;
	temp.second = coord.second * M_PI / 180;
	return temp; 
}

vector<Vertex> Airport::findShortestUnweightedPath(Graph g, Vertex source, Vertex destination){
    unordered_map<Vertex, Vertex> prev; //stores previous vertices for every visited vertex
    std::queue<Vertex> q; //queues all vertices for the BFS
    unordered_map<Vertex, bool> visited; //keeps track of which vertices have been visited
    vector<Vertex> vertices = g.getVertices(); //vertices from our graph

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
        vector<Vertex> adj = g.getAdjacent(v); //neighbors of current vertex

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

vector<Vertex> Airport::findShortestWeightedPath(Graph g, Vertex source, Vertex destination){
    long double maxDist = 24859.734; //earth's circumference and the maximum possible distance of a flight
    unordered_map<Vertex, double> distances; //stores each vertex with its distance from the source vertex
    unordered_map<Vertex, Vertex> prev; //stores each vertex's previous vertex from the path to reach the vertex from the source
    vector<Vertex> vertices = g.getVertices(); //vertices from our graph
    vector<Vertex> v; //vector to store vertices of interest   
    vector<Vertex> path; //path of vectors from the source to the destination

    //compare function to find the vertex with a shorter distance from the source
    auto compare = [&](Vertex left, Vertex right) { 
        return distances[left] > distances[right]; 
    };

    //initializes all the data structures with the appropiate values
    for (unsigned i = 0; i < vertices.size(); i++) {
        if (vertices[i] == source) {
            distances[source] = 0; //source's distance is 0
        } else {
            distances[vertices[i]] = maxDist; //every other vertex's distance is intially set to maxDist
        }
        v.push_back(vertices[i]);
        std::push_heap(std::begin(v), std::end(v), compare); //creates a min-heap priority queue of every vertex
    }
    
    bool flag = true; //flag to check if the destination is found

    while (!(v.empty())) {
        std::pop_heap(std::begin(v), std::end(v), compare); //pop's minimum distance vertex from queue and re-heapifies adding the min to the back
        Vertex min = v.back(); //minimum distance vertex extracted from the back of v
        v.pop_back();
        
        //if the destination has been reached
        if (min == destination) {

            //create a path from the destination to the vertex
            /*while (prev.find(min) != std::end(prev)) {
                path.push_back(min);
                min = prev[min];
                
            }*/
            Vertex curr = destination;
            while(curr != source) {
                path.push_back(curr);
                curr = prev[curr];
                //std::cout<<prev[curr]<<std::endl;
            }
            path.push_back(source);
            std::reverse(path.begin(), path.end()); //reverses path so its from source to destination
            flag = false; //change flag to mark destination as found
            break;
        }

        //break while loop if node is disconnected
        if (distances[min] == maxDist) {
            break;
        }
        
        //add proper distances to neighbor nodes of v
        std::vector<Vertex> adj = g.getAdjacent(min);
        for (unsigned i = 0; i < adj.size(); i++) {
            double comp = distances[min] + g.getEdgeWeight(min, adj[i]);
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

PNG* Airport::drawMap(){
    PNG* map = new PNG;
    map->readFromFile("mercatorMap.png");

    vector<Edge> edges = g_.getEdges();
    for (auto edge : edges) {
        Values src = airportList[edge.source];
        Values des = airportList[edge.dest];
        std::cout << src.latitude_ << "," <<  src.longitude_ << "," << des.latitude_ << "," << des.longitude_ << std::endl;
        drawMapHelper(map,src.latitude_, src.longitude_, des.latitude_, des.longitude_);
    }
/*
    for(auto it = airportList.begin(); it != airportList.end(); it++){
        Vertex source = it->first;
        Values val = it->second;
        long double source_lat = val.latitude_;
        long double source_long = val.longitude_;
        vector<Vertex> destinations = g_.getAdjacent(source);
        for(Vertex & dest : destinations){
            long double dest_lat = airportList[dest].latitude_;
            long double dest_long = airportList[dest].longitude_;
            drawMapHelper(map, source_lat, source_long, dest_lat, dest_long);
        }
    }*/

    map->writeToFile("Out.png");
    return map;
}

void Airport::drawMapHelper(PNG* map, long double sLat, long double sLong, long double dLat, long double dLong){
    pair<int , int> sourceXY = coordToXY(sLat, sLong);
    pair<int , int> destXY = coordToXY(dLat, dLong);
    int x0 = sourceXY.first; 
    int y0 = sourceXY.second;
    int x1 = destXY.first;
    int y1 = destXY.second;

    int dx, dy;
    int stepx, stepy;
    dx = x1 - x0;
    dy = y1 - y0;

    const int mapWidth = 1200;
    const int mapHeight = 1200;
    
    //bresenham's algorithm adapted from csustan.edu
    if(dy < 0){ dy = -dy; stepy = -1; }
    else{ stepy = 1; }
    if(dx < 0){ dx = -dx; stepx = -1; }
    else{ stepx = 1; }
    dy <<= 1; 
    dx <<= 1;
    
    if((0 <= x0) && (x0 < mapWidth) && (0 <= y0) && (y0 < mapHeight)){
        HSLAPixel & pixel = map->getPixel(x0, y0);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
    }
    
    if(dx > dy){
        int fraction = dy - (dx >> 1);
        while(x0 != x1){
            if(fraction >= 0){
                y0 += stepy;
                fraction -= dx;
            }
            x0 += stepx;
            fraction += dy;
            if((0 <= x0) && (x0 < mapWidth) && (0 <= y0) && (y0 < mapHeight)){
                HSLAPixel & pixel = map->getPixel(x0, y0);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        }
    }
    else{
        int fraction = dx - (dy >> 1);
        while(y0 != y1){
            if(fraction >= 0){
                x0 += stepx;
                fraction -= dy;
            }
            y0 += stepy;
            fraction += dx;
            if((0 <= x0) && (x0 < mapWidth) && (0 <= y0) && (y0 < mapHeight)){
                HSLAPixel & pixel = map->getPixel(x0, y0);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        }

    }

}

pair<int , int> Airport::coordToXY(long double latitude, long double longitude){
    pair<int, int> XY;
    const int mapWidth = 1200;
    const int mapHeight = 1200;

    //get x val 
    long double x = fmod((longitude + 180) * mapWidth / 360, mapWidth + (mapWidth / 2));

    //get y val
    long double latRad = latitude * M_PI / 180;
    long double mercN = log(tan((M_PI / 4) + (latRad / 2)));
    long double y = (mapHeight / 2) - (mapWidth * mercN / (2 * M_PI));

    XY.first = x; XY.second = y;
    return XY;
}