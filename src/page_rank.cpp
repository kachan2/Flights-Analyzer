#include "page_rank.h"

#include <string>
#include <unordered_set>
using namespace std;

PageRank::PageRank(const Flights& flight_graph) {
  for (const auto& [node, neighbors] : flight_graph.adj_) {
    unordered_map<int, long double> probability_vector;
    long double total_weight = 0;
    for (const auto& connection : neighbors) {
      total_weight += 1000 / connection.second;
    }
    for (const auto& [neighbor, weight] : neighbors) {
      probability_vector[neighbor] = (1000 / weight) / total_weight;
    }
    adj_[node] = probability_vector;
  }
}

unordered_map<int, long double> PageRank::Traverse(int start_airport_id, int levels, double alpha) {
  unordered_map<int, long double> res;
  if (!adj_.count(start_airport_id)) throw invalid_argument("Not a valid start node");
  if (levels < 1 || levels >= 456) throw invalid_argument("Not a valid number of levels");
  res[start_airport_id] = 1 / alpha;
  unordered_set<string> edges;
  Traverse(start_airport_id, levels, alpha, res, edges);
  res.erase(start_airport_id);
  return res;
}
/**
 * Helper funtion to encode an edge a string
 */
string as_edge(int a, int b) {
  return to_string(a) + "," + to_string(b);
}

void PageRank::Traverse(int node, int levels, double alpha, unordered_map<int, long double>& res, unordered_set<string>& edges) {
  if (levels == 0) return;
  for (const auto& [neighbor, prob] : adj_.at(node)) {
    if (edges.count(as_edge(node, neighbor))) return;
    edges.insert(as_edge(node, neighbor));
    long double increment = res[node] * prob * alpha;
    res[neighbor] += increment;
    Traverse(neighbor, levels - 1, alpha, res, edges);
  }
}