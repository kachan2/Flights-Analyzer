#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

/**
 * A struct for storing the data entries in `reachability-meta.csv`
 * which is a csv containing node_idx, name, population, latitude, longitude
 */
struct DataEntry {
  int node_id;
  string name;
  int population;
  double latitude;
  double longitude;
  /**
   * Construct an entry using a csv entry line
   */
  DataEntry(const string& input);
};
/**
 * Parse a file and return a vector of all of its entries
 */
vector<DataEntry> parseFile(const string& filepath);
/**
 * Print out the contents of a DataEntry to an out-stream
 */
ostream& operator<<(std::ostream& os, const DataEntry& d);
