#include "meta_data_entry.h"

#include "utilities.h"

DataEntry::DataEntry(const string& input) {
  vector<string> input_vec = split(input, ',');
  if (input_vec.size() != 5) throw invalid_argument("Need 5 elements for a data entry");
  node_id = stoi(input_vec.at(0));
  name = input_vec.at(1), population = stoi(input_vec.at(2));
  latitude = stod(input_vec.at(3)), longitude = stod(input_vec.at(4));
}

vector<DataEntry> parseFile(const string& filepath) {
  ifstream file(filepath);
  if (!file.is_open()) throw invalid_argument("I can't open this file :(");

  string line;
  getline(file, line);
  vector<string> expected_headers = {"node_id",
                                     "name",
                                     "metro_pop",
                                     "latitude",
                                     "longitude"};
  if (split(line, ',') != expected_headers)
    throw invalid_argument("Looks like your data has different column names than I expected");

  vector<DataEntry> entries;
  while (getline(file, line))
    entries.push_back(DataEntry(line));

  return entries;
}

ostream& operator<<(std::ostream& os, const DataEntry& d) {
  os << "Node ID: " << d.node_id
     << " Name: " << d.name
     << " Population: " << d.population
     << " Latitude: " << d.latitude
     << " Longtitude: " << d.longitude;
  return os;
}
