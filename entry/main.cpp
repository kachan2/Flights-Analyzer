#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "flights.h"
#include "meta_data_entry.h"
#include "page_rank.h"
#include "utilities.h"
using namespace std;

int main() {
  bool shouldrun = true;
  // Initiate file paths
  string airportpath = "../data/reachability-meta.csv";
  string flightpath = "../data/reachability.txt";

  // set up flight paths as well as airport metadata
  Flights f(flightpath, airportpath);
  vector<DataEntry> entries = parseFile(airportpath);
  PageRank page_rank(f);

  while (shouldrun) {
    std::cout << "Hello Welcome to the airport database! Please select an option:" << std::endl;
    display();
    int option;
    std::cin >> option;
    if (option > 4 || option < 1) {
      std::cout << "Please enter a valid option" << std::endl;
      std::cout << " " << std::endl;
    }
    switch (option) {
      case 1:
        std::cout << "Please enter the id of the airport you want to check. The IDs are Valid from 1-455." << std::endl;
        std::cout << "If you want to display all airports, enter 999" << std::endl;
        std::cout << " " << std::endl;
        int id;
        std::cin >> id;
        if (id >= 1 && id <= 455) {
          checkAirportId(id, entries);
          std::cout << " " << std::endl;
        } else if (id == 999) {
          vector<DataEntry> first_ten = {entries.begin(), entries.end()};
          cout << first_ten;
          std::cout << " " << std::endl;
        } else {
          std::cout << "Please enter a valid id" << std::endl;
          std::cout << " " << std::endl;
        }
        break;
      case 2:
        std::cout << "Welcome to BFSPathChecker(TM)! Please Enter your starting point (1-455)" << std::endl;
        int from;
        std::cin >> from;
        std::cout << " " << std::endl;
        std::cout << "Enter your destination! (1-455)" << std::endl;
        std::cout << " " << std::endl;
        int to;
        std::cin >> to;
        std::cout << " " << std::endl;
        pathBFS(to, from, f, entries);
        std::cout << " " << std::endl;
        break;
      case 3:
        std::cout << "Welcome to PageRanker, we will try to guess the probability you go somewhere" << std::endl;
        std::cout << "Enter your starting point (1-455)" << std::endl;

        std::cin >> from;
        std::cout << " " << std::endl;
        std::cout << "Enter levels (>1)" << std::endl;
        int levels;
        std::cin >> levels;
        std::cout << " " << std::endl;
        std::cout << "How many entries do you want displayed maximum? (1-25)" << std::endl;
        int displays;
        std::cin >> displays;
        std::cout << " " << std::endl;
        std::cout << "Enter your alpha value (0.1 < alpha < 0.8)" << std::endl;
        double alphalevel;
        std::cin >> alphalevel;
        std::cout << " " << std::endl;
        pageRankDisplay(from, levels, alphalevel, page_rank, f, entries, displays);
        break;
      case 4:
        std::cout << "Welcome to Dijkstras Air Travel Agency Planner! We will help you find the shortest path between cities to save you money" << std::endl;
        std::cout << "Your wallet is our greatest concern!" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "Enter your starting point (1-455)" << std::endl;
        std::cin >> from;
        std::cout << " " << std::endl;
        std::cout << "Enter your destination! (1-455)" << std::endl;
        std::cout << " " << std::endl;
        std::cin >> to;
        std::cout << " " << std::endl;
        DijkstrasPath(to, from, f, entries);
        break;
    }
    std::cout << "Do you want to continue\"y\" or exit \"n\"" << std::endl;
    std::string decision;
    std::cin >> decision;

    if (decision == "y") {
      shouldrun = true;
    } else {
      shouldrun = false;
      std::cout << "Have a great day";
    }
  }
  return 0;

  // test parsing and entries
  // cout << "Parsed " << entries.size() << " entries from " << flightpath << endl;
  // cout << "\nPrinting the first 10 entires" << '\n';
  // vector<DataEntry> first_ten = {entries.begin(), entries.begin() + 10};
  // cout << first_ten;

  // Test adjacency list for airport 2 and different paths to and from
  // cout << "\nPrinting out the graph for champaign airport" << '\n';
  // int airport_id = 65;
  // DataEntry airport = f.getAirport(airport_id);
  // for (const pair<int, int> edge : f.getAdjacencyList(airport_id)) {
  //   DataEntry neighbor = f.getAirport(edge.first);
  //   int dist = edge.second;
  //   cout
  //       << "Airport " << neighbor.name
  //       << " has a route from " << airport.name
  //       << " with a similarity of " << dist
  //       << '\n';
  // }

  // testing Dijkstra's for some simpler cases
  // cout << "\n" << endl;
  // cout << "The shortest path from " << f.getAirport(40).name << " to " << f.getAirport(33).name << ": " << endl;
  // f.printShortestPath(40, 33);

  // cout << "\n" << endl;
  // cout << "The shortest path from " << f.getAirport(0).name << " to " << f.getAirport(80).name << ": " << endl;
  // f.printShortestPath(0, 80);

  // Testing PageRank
  // cout << "\nPageRank for Champaign\n";

  // auto travel = page_rank.Traverse(455, 100, .5);
  // long double total = 0;

  // vector<pair<int, long double>> v;
  // for (const auto& pair : travel) v.push_back(pair);

  // sort(v.begin(), v.end(), [](auto pair1, auto pair2) {
  //   return pair1.second > pair2.second;
  // });

  // vector<pair<int, long double>> first_25 = {v.begin(), v.begin() + 25};
  // for (const auto& [neighbor, prob] : first_25) {
  //   cout << "ID: " << f.getAirport(neighbor).name << " Probability: " << prob << '\n';
  // }

  // test BFS find path
  //  std::cout<<f.findPathBFS(3,144)<<std::endl;
}