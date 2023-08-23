# Project Results

What follows in an overview of our results after coding and executing our project

## Our Algorithms

### BFS
> Implemented by David
#### Output

#### Testing Functionality


### Dijkstra
> Implemented by Kaitlyn
#### Output

#### Testing Functionality


### PageRank
> Implemented by Dhiraj
#### Output

Our pagerank algorithm successfull returned an unordered map with all the possible end locations form the specified source airport in the specified number of levels with the specified $\alpha$ dampening factor (i.e. the dampening that occured after each level to reflect the reduced chance of increasingly longer paths).

This output can then be mapped to the node id's in the loaded metadata for each airport and can also be sorted in a vector by the most probable end destinations quite easily by the user (see `entry/main.cpp` for an example of this).

For example, when running PageRank on airport node #65 (Champaign's Willard Airport) we get the following results for the 10 most probable end destinations
```
PageRank for Champaign, IL
ID: Chicago, IL Probability: 0.0313984
ID: Cincinnati, OH Probability: 0.0270182
ID: Detroit, MI Probability: 0.0149926
ID: Dallas/Fort Worth, TX Probability: 0.0119747
ID: Green Bay, WI Probability: 0.0105294
ID: Dubuque, IA Probability: 0.0104331
ID: Dayton, OH Probability: 0.00906475
ID: Columbus, OH Probability: 0.00904327
ID: Madison, WI Probability: 0.00904257
ID: Toledo, OH Probability: 0.00904182
```

#### Testing Functionality
Since verifying pagerank is quite difficult without manually calcualting all conditional probabilities between any pairwise match of start and end airports, we used several "sanity" checks in our test cases to ensure that PageRank was behaving correctly under function calls with our dataset.

The first step was in verification was making the probability graph needed for PageRank as populated correctly. This was done by verifying that the correct number of nodes were loaded, and that the sum of probabilities to each connected node in the adjacency list as 1 (i.e. proper normalization of edges was done)

After this we testing the traversal method of PageRank. we made sure the following criteria were met:
1. The traversal return probabilities should all sum up to one (since it has to map over every possibility given our dataset)
2. The top probabilities in the traversal should make conceptual sense
	1. For example, the top 3 end airports in terms of destination form Champaign are Chicago, Cincinatti, and Detroit in that order. This makes sense geographically given the positions of these airports and the fact people would use Champaign airport to get to large metropoliation airports that server more destinations
2. Airports probability weights should be lopsdided. 
	1. Since our dataset includes all the paths (even those not as common) the second half should have probability extremely low

## Answering Our Leading Question
> **Q:**  Our primary objective is to analyze what "typical flights" look like

We answers this question by creating a graph data structure out of the dataset. Using this graph structure we could leverage the graph algorithms of PageRank and Dijkstra to analyze the probability of certain paths and the shortest paths between two destination. This led the following infomration that helped us answer our question.
1. Using the Dijkstra shortest paths algorithm we saw that **[KAITLYN PLEASE WRITE SOMETHING IDK]**
2. The PageRank illuminated that most of the airtravel from any given airport was usually very concentrated in a handul of airports. In general we saw that the bottom half of the least probable airports contributed virtually nothing to the overall paths in and out of the airport. This indicated that these destination are exist more for coverage of an airport than to accomadate the majority of people (most likely because airline paths are setup to provide reasonable transoportation options beyond just optimizing for profits by only having flights to and form popular destinations). We also saw through the PageRank that the majority of probably desintations fall into one of two categories: geographically close desinations and major metropoliation areas. For smaller airports, the most probably destination were the airports closest in geographical distance that were markedly larger, indicating that flights from these airports were either used for short trips to the nearest city or to connect to a larger airport that offered a wider variety of flights. For larger airports, we saw that probable destinations included other large airports, indicating that these airports were often leveraged by travelers to travel larger distances and/or to get the nearest major city as their destination or to take a smaller flight to a smaller airport from there. 
