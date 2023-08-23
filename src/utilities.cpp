#include "utilities.h"

vector<string> split(const string &s, const char &delim) {
  vector<string> res;
  string current_section;
  bool open_quote = false;
  for (const char &c : s) {
    if (c == '"')  // String (ignore delim)
      open_quote = !open_quote;
    else if (open_quote || c != delim)  // valid character
      current_section += c;
    else if (!open_quote && !current_section.empty())
      res.push_back(current_section), current_section.clear();
  }
  if (!current_section.empty()) res.push_back(current_section);
  return res;
}

void display() {
  std::cout<<"Please enter a number for options:"<<std::endl;
  std::cout<<"1) Check Airport Number from ID"<<std::endl;
  std::cout<<"2) Check if a path exists using BFS"<<std::endl;
  std::cout<<"3) Check probability of going to an airport using PageRank"<<std::endl;
  std::cout<<"4) Find the shortest path between two different airports using Dijkstras"<<std::endl;
  std::cout<<"Please enter 1, 2, 3, or 4"<<std::endl;
}

void checkAirportId(int id, std::vector<DataEntry> entries) {
  std::cout << entries.at(id) <<std::endl;
}

void pathBFS(int to, int from, Flights f,std::vector<DataEntry> entries) {
  if (f.findPathBFS(to, from)) {
    std::cout<<"There exists a path to airport " << to <<" "<< entries.at(to).name <<  " from airport " << from <<" "<< entries.at(from).name <<std::endl;
    std::cout << " "<<std::endl;
    std::cout << "Feel free to use Dijkstras Short Path to plan your path now! Happy Travels!"<<std::endl;
  } else {
    std::cout<<"There is not a path to airport " << to <<" "<< entries.at(to).name <<  " from airport " << from <<" "<< entries.at(from).name <<std::endl;
  }
}

void DijkstrasPath(int to, int from, Flights f,std::vector<DataEntry> entries) {
  cout << "The shortest path from " << f.getAirport(from).name << " to " << f.getAirport(to).name << ": " << endl;
  f.printShortestPath(from, to);
}

void pageRankDisplay(int node, int level, double alpha, PageRank page_rank,Flights f,std::vector<DataEntry> entries, int displaylimit) {
  auto travel = page_rank.Traverse(node, level, alpha);
  long double total = 0;

  vector<pair<int, long double>> v;
  for (const auto& pair : travel) v.push_back(pair);

  sort(v.begin(), v.end(), [](auto pair1, auto pair2) {
    return pair1.second > pair2.second;
  });
  std::cout<<"PageRank for " <<f.getAirport(node).name <<std::endl;
  vector<pair<int, long double>> first_25 = {v.begin(), v.begin() + displaylimit};
  for (const auto& [neighbor, prob] : first_25) {
    cout << "ID: " << f.getAirport(neighbor).name << " Probability: " << prob << '\n';
  }
}