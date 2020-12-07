#include "../cs225/catch/catch.hpp"

#include "../Airport.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"
#include <iostream>

using std::string;

TEST_CASE("basic constructor unordered map", "[weight=1][part=1]") {
  Values x1("name:1","city:1","country:1","C:1",1.1,1.1);
  Values x2("name:2","city:2","country:2","C:2",2.22,2.22);
  Values x3("name:3","city:3","country:3","C:3",3.333,3.333);
  Values x4("name:4","city:4","country:4","C:4",4.4444,4.4444);
  Values x5("name:5","city:5","country:5","C:5",5,5.55);
  Values x6("name:6","city:6","country:6","C:6",6.66,6);
  Values x7("name:7","city:7","country:7","C:7",7,7);
  Values x8("name:8","city:8","country:8","C:8",8,8);
  Values x9("name:9","city:9","country:9","C:9",9,9);
  Values x10("name:10","city:10","country:10","C10",10,10);
  Values xx("name:1000","city:1000","country:1000","Cxx",1000,1000);
  vector<Values> compare;
  compare = {x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,xx};

  Airport temp("data/testAirports.txt", "data/testRoutes.txt");
  std::unordered_map<string, Values> map = temp.getAirportList();
  REQUIRE(map.size() == 11);
  for (auto &val : compare) {
    Values mapped = map.at(val.code_);
    REQUIRE(val == mapped);
  }
}

TEST_CASE("basic constructor graph creation", "[weight=1][part=1]") {
  Values x1("name:1","city:1","country:1","C:1",1.1,1.1);
  Values x2("name:2","city:2","country:2","C:2",2.22,2.22);
  Values x3("name:3","city:3","country:3","C:3",3.333,3.333);
  Values x4("name:4","city:4","country:4","C:4",4.4444,4.4444);
  Values x5("name:5","city:5","country:5","C:5",5,5.55);
  Values x6("name:6","city:6","country:6","C:6",6.66,6);
  Values x7("name:7","city:7","country:7","C:7",7,7);
  Values x8("name:8","city:8","country:8","C:8",8,8);
  Values x9("name:9","city:9","country:9","C:9",9,9);
  Values x10("name:10","city:10","country:10","C10",10,10);
  Values xx("name:1000","city:1000","country:1000","Cxx",1000,1000);

  Airport temp("data/testAirports.txt", "data/testRoutes.txt");
  Edge e1("C:1","C:2");
  Edge e2("C:2","C:5");
  Edge e3("C10","C:4");
  Edge eFail("C50","C:2");
  vector<Values>compare = {x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,xx};
  vector<Edge> edges = {e1,e2,e3};
  Graph graph = temp.getGraph(); 
  
  
  REQUIRE(graph.getVertices().size() == 11);
  for (auto &val : compare) {
    REQUIRE(graph.vertexExists(val.code_));
  }
  REQUIRE(graph.getEdges().size() == 3);
  for (auto &edge : edges) {
    REQUIRE(graph.edgeExists(edge.source, edge.dest));
  }
  REQUIRE(!graph.edgeExists(eFail.source, eFail.dest));
}