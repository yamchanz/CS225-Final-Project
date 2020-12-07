#include "graph.h"
#include "Airport.h"
#include <fstream>
#include <iostream>
#include <string>


int main() {
    std::cout << "start" << std::endl;
    Airport temp("testAirports.txt", "testRoutes.txt");
    std::cout << "past constructor" << std::endl;
    std::unordered_map<string, Values> list = temp.getAirportList();
    std::cout << "past list" << std::endl;
    for (auto code : list) {
        std::cout << code.second.to_string() << std::endl;
    }

    return 0;
}