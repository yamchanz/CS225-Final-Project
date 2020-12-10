#include "graph.h"
#include "Airport.h"
#include <fstream>
#include <iostream>
#include <string>


int main() {
    
    Airport airport("data/airports.txt","data/smallerRoutes.txt");
    std::cout << "constructor done" << std::endl;
    airport.drawMap();
    //PNG* map = new PNG();
    //map->readFromFile("mercatorMap.png");
    //vector<Vertex> path = airport.findShortestWeightedPath("C:6","C13");
    //airport.drawPath(path);
    /*airport.drawMapHelper(map, -88,0, 88, 0);
    airport.drawMapHelper(map, -88,-179, 88, 179);
    airport.drawMapHelper(map, 88,-179, -88, 179);
    airport.drawMapHelper(map, -44,-179, 44, 179);
    airport.drawMapHelper(map, 44,-179, -44, 179);
    airport.drawMapHelper(map, -22,-179, 22, 179);
    airport.drawMapHelper(map, 22,-179, -22, 179);
    airport.drawMapHelper(map, -11,-179, 11, 179);
    airport.drawMapHelper(map, 11,-179, -11, 179);
    airport.drawMapHelper(map, 0,-179, 0, 179);
    // ORD to LHR
    airport.drawMapHelper(map, 41.9742, -87.9073, 51.4700, -0.4543);*/
    //map->writeToFile("Out.png");
    return 0;
}