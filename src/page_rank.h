#pragma once

#include <unordered_set>

#include "flights.h"
using namespace std;
class PageRank {
 public:
  /**
   * Constructs a probability graph based on a flight graphs
   */
  PageRank(const Flights& flight_graph);
  /**
   * Method to return a list of accessible aiports given a certain number of levels in terms
   * of the probability of the airport being and end destination from the source airport
   */
  unordered_map<int, long double> Traverse(int start_airport_id, int levels, double alpha = .85);
  /**
   * Recursive helper functions for PageRank Traverse Method
   */
  void Traverse(int node, int levels, double alpha, unordered_map<int, long double>& res, unordered_set<string>& edges);

  /**
   * Member variables to store the probability graph
   */
  unordered_map<int, unordered_map<int, long double>> adj_;
};