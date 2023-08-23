#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <list>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

#include "meta_data_entry.h"

using namespace std;
class Flights {
 public:
  Flights(const std::string& pathname, const std::string& airportname);  // Deafult constructor

  unordered_map<int, int> getAdjacencyList(int id) const;  // Get Adjacency List
  DataEntry getAirport(int id) const;
  bool findPathBFS(int to, int from);
  bool findPathSimilarityThresholdBFS(int to, int from, int threshold);
  unordered_map<int, unordered_map<int, int>> adj_;  // Adjacency List (or Matrix)


  std::vector<int> dijkstras(int start, int end); // Dijktras Algorithm
  void printShortestPath(int start, int end);
  
 private:
  vector<DataEntry> vertices_;  // Store all vertices
  int size_;                    // Store size of the graph
};

#endif
