#include "graph.h"
#include "Airport.h"
#include <fstream>
#include <iostream>
#include <string>
using std::string;

int main() {

/*
    //populates graph with all the airports, unconnected
    std::ifstream airportFile("airports.txt");
    string line;
    if (airportFile.is_open()) {
        while (getline(airportFile, line)) {
            Value currNode = Value();
            int commas = 0;
            int prev = 0;
            int curr = 0;
            string str;
            //goes through each line, character by character
            //push each to dictionary with keys
            for (char c : line) {
                if (c == ',') {
                    commas++;
                    curr++;
                    //parse the section
                    str = line.substr(prev + 1, curr-prev);
                    //name case
                    if (commas == 2) {currNode.name_ = str;}
                    //city case
                    else if (commas == 3) {currNode.city_ = str;}
                    //country case
                    else if (commas == 4) {currNode.country_ = str;
                    //populate graph here
                    }
                    //3-letter code case
                    else if (commas == 5) {currNode.code_ = str;}
                    //latitude case
                    else if (commas == 7) {currNode.latitude_ = std::stod(str);}
                    //longitude case and pushes to graph
                    else if (commas == 8) {
                        currNode.longitude_ = std::stod(str);
                        //needs graph to be working
                        //graph.insertVertex(currNode);
                    }
                    prev = curr;
                }
            }
        }
    }

    //populates edges
    std::ifstream edgeFile("routes.txt");
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


                    //#######NEEDS TO CHECK DIRECTIONS MAYBE################


                    //parse the section
                    str = line2.substr(prev + 1, curr-prev);
                    //source case | need to check for 3 letter
                    if (commas == 3) {source = str;}
                    //destintion case | need to check for 3 letter
                    else if (commas == 5) {
                        //needs graph set up
                        //graph.setEdgeLabel(source,str,#SOMELABELMAYBE#)
                    }
                    prev = curr;
                }
            }
        }
    }*/


    return 0;
}