#include "flights.h"

#include <algorithm>
#include <fstream>
#include <list>
#include <queue>
#include <string>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

#include "meta_data_entry.h"
#include "utilities.h"

using namespace std;
/*
CSV Format:

Directed graph: reachability.txt
Transportation reachability of cities in the United States and Canada
(edge from i to j if the estimated travel time from i to j is less than a threshold)
Edges are weighted by similarity (more negative --> more dissimilar)
How far apart they are the farther apart is more negative
Nodes: 456 Edges: 71959
FromNodeId ToNodeId Weight


Default constructor

Input: Takes in file name of the data
Output: Assigns everything into the graph representation

*/
Flights::Flights(const std::string& pathname, const std::string& airportname) : vertices_(parseFile(airportname)) {
  size_ = vertices_.size();

  ifstream file(pathname);

  if (!file.is_open()) throw invalid_argument("I can't open this file :(");

  for (int i = 0; i <= 455; i++) adj_.insert({i, unordered_map<int, int>()});

  string line;
  while (getline(file, line)) {
    vector<string> input_vec = split(line, ' ');
    if (input_vec.size() != 3) throw invalid_argument("Need 3 elements for valid edge" );
    adj_[stoi(input_vec[0])].insert({stoi(input_vec[1]), -stoi(input_vec[2])});
  }
}

bool Flights::findPathBFS(int to, int from) {
  if (to == from) {
    return true;
  }
  std::queue<int> bfsqueue;
  std::vector<int> visited;

  bfsqueue.push(from);
  visited.push_back(from);

  while (!bfsqueue.empty()) {
    int current = bfsqueue.front();
    bfsqueue.pop();
    std::vector<int> adjlist;
    for (std::pair<int, int> relation : getAdjacencyList(current)) {
      // std::cout << current << ' ' << relation.first << ' ' << relation.second << std::endl;
      adjlist.push_back(relation.first);
    }
    for (int relation : adjlist) {
      bool alreadyseen = (std::find(visited.begin(), visited.end(), relation) != visited.end());
      if (!alreadyseen) {
        bfsqueue.push(relation);
        visited.push_back(relation);
      }
    }
    if (current == from) {
      return true;
    }
  }
  return false;
}

bool Flights::findPathSimilarityThresholdBFS(int to, int from, int threshold) {
  if (to == from) {
    return true;
  }
  std::queue<int> bfsqueue;
  std::vector<bool> visited(456);

  bfsqueue.push(from);
  visited.push_back(from);
  int runningTotal;
  while (!bfsqueue.empty()) {
    int current = bfsqueue.front();
    bfsqueue.pop();
    std::vector<int> adjlist;
    for (std::pair<int, int> relation : getAdjacencyList(current)) {
      adjlist.push_back(relation.first);
    }
    for (int relation : adjlist) {
      bool alreadyseen = visited[relation];
      if (!alreadyseen) {
        bfsqueue.push(relation);
        visited[relation] = true;
      }
    }
    if (current == from) {
      return true;
    }
  }
  return false;
}

/*
getAdjacencyList method

Input: Index (Airport ID) between [0-455]
Output: list<int> of airports that the <index> reaches to.
        i.e. what flights from <index> go towards airport <output> ?

*/
unordered_map<int, int> Flights::getAdjacencyList(int id) const {
  if (id < 0 or id > size_) {
    throw invalid_argument("Out of index bounds. Please enter a valid value from 0-455");
  }

  return adj_.at(id);
}

/*
getAirport method

Input: Index (Airport ID) between [0-455]
Output: A DataEntry Class of all the metadata of the airport.
*/
DataEntry Flights::getAirport(int id) const {
  if (id < 0 or id > size_) {
    throw invalid_argument("Out of index bounds. Please enter a valid value from 0-455");
  }
  return vertices_.at(id);
}


/*
  Compare 
  returns a boolean value true if the first parameter's second value is greater than the second parameter's second value, false otherwise
*/
struct Compare {
    bool operator()(std::pair<int, int> a, std::pair<int, int> b) {
        return a.second > b.second;
    }
};

/*
  Dijkstras Algorithm
  parameters: starting vertex (int) and ending vertex (int)
  returns: the shortest path between the two vertices
*/
std::vector<int> Flights::dijkstras(int start, int end) {
  priority_queue<pair<int,int>, vector<pair<int,int>>,Compare> q;
  vector<int> dist(size_, INT_MAX); 
  vector<int> prev(size_, -1); 
  vector<bool> visited(size_, false);

  // adding nodes to queue and initializing start values
  dist[start] = 0;
  visited[start] = true;
  for (DataEntry v : vertices_) {
    q.push(make_pair(v.node_id, dist[v.node_id]));
  }

  // traversing nodes
  while (!q.empty()) {
    int curNode = q.top().first;
    int curDist = q.top().second;
    q.pop();

    if (curNode == end) { break; }

    // checking neighbors
    for (const pair<int, int> neighbor : getAdjacencyList(curNode)) {
      int alt = curDist + neighbor.second;
      // if the alternate distance is smaller, add it to the queue
      if (alt < dist[neighbor.first] && !visited[neighbor.first]) {
        dist[neighbor.first] = alt;
        prev[neighbor.first] = curNode;
        q.push(make_pair(neighbor.first, alt));
      }
    }
    visited[curNode] = true;
  }

  // building path between start and end vertices
  std::vector<int> path;
  int u = end;
  if (prev[u] != -1 || u == start) {
    while (u != -1) {
        path.insert(path.begin(), u);
        u = prev[u];
    }
  }

  return path;
}

/* 
  Uses Dijkstra's Algorithm and maps the node id's to the respective airport name, and prints the results 
  parameters: start and end airports 
*/
void Flights::printShortestPath(int start, int end) {
  vector<string> strs; 
  vector<int> path = dijkstras(start, end);
  if (path.empty()) {
    cout << "There are no flights that go from " + getAirport(start).name + " to " + getAirport(end).name << endl;
  } else {
    for (int i = 0; i < (int)path.size(); i++) { 
      cout << to_string(i + 1) + ". " + getAirport(path[i]).name << endl; 
    }
  }
}