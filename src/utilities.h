#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "flights.h"
#include "meta_data_entry.h"
#include "page_rank.h"
using namespace std;

/**
 * Splits a string with a delimiter (automatically deals with quotes that may appear in csv)
 */
vector<string> split(const string &s, const char &delim);


void display();
void checkAirportId(int id, std::vector<DataEntry> entries);
void pathBFS(int to, int from, Flights f,std::vector<DataEntry> entries);
void DijkstrasPath(int to, int from, Flights f,std::vector<DataEntry> entries);
void pageRankDisplay(int node, int level, double alpha, PageRank page_rank,Flights f,std::vector<DataEntry> entries, int displaylimit);
/**
 * Print out a vector
 */
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
  for (const auto &element : vec)
    os << element << '\n';
  return os;
}