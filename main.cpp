#include "graph.h"
#include "Airport.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include "Values.h"

using std::string;

int main(int argc, char* argv[]) {
    //command line helpers
    string call = argv[0];
    string dataAirports = "data/airports.txt";
    string dataRoutes = "data/smallerRoutes.txt";

    string outVALIDROUTE = "\n\n\n:::Shortest Route Drawn on Out.png:::\nthe cyan dot indicates the starting airport, the black dot is the destination airport";
    string outINVALIDROUTE = "Not a valid operation parameter.  Chooose between DISTANCE or STOPS to find shortest route of the respective type.";
    string outHELP = "\nFIND THE SHORTEST ROUTE, VIA DISTANCE OR # OF STOPS, USING : \n" + call
        + " [Type of operation (DISTANCE or STOPS)] [3-letter airport code source] [3-letter airport code destination]\n\nTO GET A LIST OF 100 AIRPORT CODES IN OUR DATA, USE :\n"
        + call + " list [number < 5997]\n\n";


    //Gives list of 100 airports based on argv2 number parameter 
    if (argc == 3) {
        string list = argv[1];
        if (list == "list") {
            string num = argv[2];
            int index;
            try {index = std::stoi(num);}
            catch (std::exception& e) {
                std::cout << "Not a valid number" << std::endl;
                return 0;
            }
            //Populates Graph
            if (index < 0 || index > 5997) {
                std::cout << "Not a valid number" << std::endl;
                return 0;
            }
            Airport airport(dataAirports,dataRoutes);
            std::cout << ":::Airports and Routes Populated:::" << std::endl;
            int cnt = 0;
            std::unordered_map<string, Values> airportList = airport.getAirportList();
            for (auto i : airportList) {
                cnt++;
                if (cnt >= index) {
                    std::cout << i.second.code_ << " , ";
                    if (cnt >= index + 100) {break;}
                }
            }
            std::cout << std::endl;

            return 0;
        }
    }

    //Makes sure the number of parameters is correct
    if (argc < 4) {
        std::cout << outHELP << std::endl;
        return 0;
    }
    //saves command-line arguments
    string operation = argv[1];
    string source = argv[2];
    string destination = argv[3];

    //standardizes inputs to all CAPS
    string op = "";
    for (char &c : operation) {
        op += toupper(c);
    }
    string src = "";
    for (char &c : source) {
        src += toupper(c);
    }
    string des = "";
    for (char &c : destination) {
        des += toupper(c);
    }
    
    //Populates Graph
    Airport airport(dataAirports, dataRoutes);
    std::cout << ":::Airports and Routes Populated:::" << std::endl;
    std::unordered_map<string, Values> airportList = airport.getAirportList();

    //Finds paths -- if possible -- and draws them on map using airport.h methods
    if (op == "DISTANCE") {
        std::cout << "calculating best route..." << std::endl;
        vector<Vertex> path = airport.findShortestWeightedPath(src,des);
        airport.drawPath(path,0);
        if (path.size() != 0) {
            std::cout << outVALIDROUTE << std::endl;

            std::cout << "Route: ";
            for (auto vertex : path) {
                std::cout <<  " -> " << vertex << "(" << airportList[vertex].name_ << ")";
            }
            std::cout << std::endl;
        }
    } else if (op == "STOPS") {
        std::cout << "calculating best route..." << std::endl;
        vector<Vertex> path = airport.findShortestUnweightedPath(src,des);
        airport.drawPath(path,0);
        if (path.size() != 0) {
            std::cout << outVALIDROUTE << std::endl;

            std::cout << "Route: ";
            for (auto vertex : path) {
                std::cout <<  " -> " << vertex << "(" << airportList[vertex].name_ << ")";
            }
            std::cout << std::endl;
        }
    } else if (op == "BOTH") {
        std::cout << "calculating best routes..." << std::endl;
        vector<Vertex> pathUnweighted = airport.findShortestUnweightedPath(src,des);
        airport.drawPath(pathUnweighted,0);
        if (pathUnweighted.size() != 0) {
            std::cout << outVALIDROUTE << std::endl;

            std::cout << "RouteUnweighted: ";
            for (auto vertex : pathUnweighted) {
                std::cout <<  " -> " << vertex << "(" << airportList[vertex].name_ << ")";
            }
            std::cout << std::endl;


            vector<Vertex> pathWeighted = airport.findShortestWeightedPath(src,des);
            airport.drawPathAdd(pathWeighted,280);
            if (pathWeighted.size() != 0) {
            std::cout << outVALIDROUTE << std::endl;

            std::cout << "RouteWeighted: ";
            for (auto vertex : pathWeighted) {
                std::cout <<  " -> " << vertex << "(" << airportList[vertex].name_ << ")";
            }
            std::cout << "\n\n The red line indicates the shortest route by stops, the violet indicates the shortest route by distance" << std::endl;
            }
        }
    } else {
        std::cout << outINVALIDROUTE << std::endl;
    }
    return 0;
}