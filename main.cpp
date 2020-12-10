#include "graph.h"
#include "Airport.h"
#include <fstream>
#include <iostream>
#include <string>


int main() {
    
    Airport airport("data/hardAirports.txt","data/hardRoutes.txt");
    PNG* map = new PNG();
    map->readFromFile("mercatorMap.png");
    //airport.drawMap();
    airport.drawMapHelper(map, -80,-90, 80, 100);
    airport.drawMapHelper(map, 80,-90, -80, 100);

    map->writeToFile("Out.png");
    return 0;
}