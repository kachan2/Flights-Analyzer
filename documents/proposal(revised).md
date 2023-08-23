# Final Project Proposal (Revised)

> *By David, Dhiraj, and Kaitlyn*

This is our proposal for the final project in CS225. We are proposing to use the OpenFlights data set to gain insight into flights paths amongst airports by treating them as a graph structure.

## Leading Question

> Our primary objective is to analyze what "typical flights" look like in order to create an interactive tool that can get potentially useful data about flights

We want to study the different networks between flight data. This would include things such as looking at the shortest path between certain destinations (given by the edge weighting of net displacement for the flight path) and pair that up with data about flight frequency (since some directly flights might be less common that connected flights) to find out the "best paths" between locations. In conjuction with this analysis about "recommended" paths for certain trips, we'd also like to create a sort of analysis of the probaility distribution between airports (essentially a markov chain graph representing the typical destinations and airlines out of a given airport). This all serves to gain insight into our leading question of "what does a typical flight path look like?" by breaking down the possibilities from each airport.

## Dataset Acquisition and Format

> Describe to the best of your ability the specifics of your input dataset. At minimum this includes: What is the source of the dataset and what is the input format of said dataset? How big is the dataset? Do you plan to use all of the data or only a subset? If so, how will you define the subset?

We will be using the [OpenFlight](https://openflights.org/data.html) dataset to create a graph for the functionality in our project

This dataset provides information of the airport, and their locations (both the city+country and the geographic coordinate via latitude and longitude). Is also provides airline data with the airline, source airport, and desintaiton airport which is useful in seeing which flights most frequent certain airports. The data also include the number of "stops" (for when a flight path is not direct), which we will account for by adding a penality (since the flight would be less preferrable than a direct flight, despite having a similar net displacement). The data separated into separate `.dat` files for each "aspect" (airport, airline, route, plane). The largest file (containing all the airport information) is about 1.2MB while the rest are under 500KB. The data file of text files, so it should be feasible to parse reasonable quickly, if the larger dataset of airport traffick is too slow we may "prune" the dataset to collect a random sample of a given percentage of the dataset for efficiency purposes (most likely a random sample of n/2 of the n data entries).

## Data Correction

> In a paragraph or two, you should describe how will you parse the input data and what checks are you doing to ensure the input data is error-free. At minimum this should dicuss how you will check for missing entries and how will you correct such instances when you find them

We will do preprocessing on our data to make sure everything is usable for our given purposes. We will most likely remove data columns that aren't nessecary for our analysis (such as timezone and date data) to prevent clutter. We will also read in the multiple data files present from the dataset source as one, esssentially loading in all tables separately, but creating functio ns that allow us to cross references to find more information (such as airline information from the table description flight routes). If there are missing or inconsistent data entries with will attempt to be a custom `Entry::NotValid` type in their place, and if several of value for each entry are missing we will abonded that entry (since it will not be useful if we put invalid or interpolated values in our analysis). Instead of the airprot IDs, we will be matching them to the actual names. This is done for user input purposes as well as making it user-friendly. We will probably be making everything in lowercase and numeric format as well to account for user input aswell.

## Data Storage

> Describe what data structure are you using to store the data within your code. If you need any auxiliary data structures or preprocessed tables, you should also discuss them here. As part of this proposal you must include an estimate of the total storage costs for your dataset in Big O notation.

For us to parse the input data, we will most likely be using libraries within C++ that allow us to read the file and serialize it into the data structure needed to store the graph (we are mostly considering leverage the [Boost Graph Library](https://www.boost.org/doc/libs/1_46_1/libs/graph/doc/index.html) as a convenient structure to store our data in program).

Our datastorage will be in a graph format, with a node for each airport, and probably a vector storing all the paths to other airports (with information on the path). This should result in a space complexity of $O(V+E)$, since each edge for each vertex has to be stored w/ all the accessory data needed. We will aim to make our graph contain as all the data, so even though it might be heavy, it will make traversals and processing easier for us. The edges in our graph will also be weighted according to the physical distance between the start and end destination of the flight path (and a correction term to make paths with multiple stops longer as they would take more time the real world despite having the same net displacement).

## Graph Algorithms

> Describe what algorithms you will use to answer the leading question. You should spend some time considering what algorithms you might try and, for all major functions you plan to use, include the following details in your proposal: function input, function outputs, function efficiency.

### Traversal (BFS)

Our primary traversal for our graph structure will be Breadth-First search. We will implement this on our own instead of using the prebuilt one in the *Boost Graph Library* so we have better control. We will implement this as our own iterator that can start from any given airport and then begin to traverse possible paths starting from the airport, and then beyond in a breadth first fashion. We believe this will be the most useful traversal since we are analyzing all the flights that leave a given airport

**Input**: The function should only require the graph itself and a start node to iterate
**Outputs**: Returns an iterator that can be used to print out a pair of start and destination airports for the airport used to initialize the iterator.
**Function Efficiency**: This function should have $O(V + E)$ time complexity since it traverses each accessible vertex via all the accessible edges from the source node. Space complexity will be the number of pairs of nodes, which should be bounded by $|E|$ in our implementation (though it will be much less since the BFS is not meant to traverse the entire graph).

### Algorithm: Djikstra (Covered)

We will be implement Djikstra as an algorithm in our graph to find the shortest paths for two destinations (our graph is weighted by the physical location between two airports). This is a reasonable effective algorithm for us to implement since ouyr graph will contiains only positive weighted edges and is feasible for us to implement given our skillset.

**Input**: Requires the graph, the start node, and the end node.
**Outputs**: Returns the calculated shortest path once found by the Djikstra algorithm. 
**Function Efficiency**: This function should have $O(E + VlogV)$ time complexity based on how Djikstra works. It will also have a space complexity of $O(V^2)$ as it stores shortest paths for nodes.

### Algorithm: PageRank (Not Covered)

We will be implementing PageRank as an algorithm not covered in CS225 for this project. We will use it to find common destination airports from a given start airport. This will leverage the frequency of flights from one airport to another to create a markov model and that will be used to create a graph where edges are weighted by probability that a flight takes that path (this can be calculated from the existing graph based on the frequency of the neighbors, so a new graph is not needed in implementation).

This will be usefull in our search feature where a person can enter in a start airport and we can return common destination from that airport, to a certain amount of levels (i.e create a smaller graph that shows the airports that could be visited within a given amount of steps with corresponding probabilities).

**Input**: The function should require the graph itself and a start node to create the probability vector.  The user should also list the number of "steps" from the original.
**Output**: The function will return a smaller graph that shows the markov chain for the source node where all nodes are within a certain amount of steps away.
**Function Efficiency**: The PageRank algorithm should have a $O(V + E)$ on the specific subsection of the graph where the function is taking place (i.e the number of nodes and corresponding edges within the given amount of steps from the source node). The space complexity shouldn't exceed $O(V^2)$ for the number of nodes in our graph subsection. 

## Timeline

> General timeline for project progress

November 11th: Parse Airline Data + Finish project setup

November 15th-ish: Create Graph + Djikstra Shortest Path (needs to be done before mid-point check in 🙃)

December 2: Implement BFS + PageRank.

December 9: Create user inputs to make the project interactive.

`woof 🦮`
