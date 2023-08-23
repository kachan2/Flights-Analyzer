##Leading Question 
We want to see and study the different networks within airports in the United States. We want to learn three things, what is the shortest path (distance, and/or least connections) between two locations in airports. In addition to that, we want to see how many connected components there are between all the airports and whether or not going from point A to B requires someone transitioning to a different airport. Maybe, we want to see if we can figure out the most popular and busy airports, and see which ones have the most connected flights. In this case, can we observe the largest airport hubs. Finally, we want to create some sort of searching that given a airport, and however many flights max you want to take, give you possible travel locations. This can be done potentially using the weights as a max radius of travel. We may also try to integrate pricing data to create additional insights on how different connecting routes may vary in pricing. 

## Dataset Acquisition and Format
We will be using the SNAP airport accessibility dataset found on the SNAP standford site. The format of the data set is 2 files, a .txt file with three columns saying the origin, destination, and a weight that indicates how similar the destinations are to one another. The lesser the value, the closer they are to each other. In addition to that, we have a .csv file that gives us the metadata of the dataset. In this file, it associates each airport ID with the actual name and city it is from. The dataset itself is in total, less than 1 MB. We plan to use all of the dataset to observe patterns of airports.

## Data Correction
For us to parse the input data, we will most likely be using libraries within C++ that allow us to read the file and serialize it into the data structure needed to store the graph. In addition to that, we will do preprocessing on it as well. Instead of the airprot IDs, we will be matching them to the actual names. This is done for user input purposes as well as making it user-friendly. We will probably be making everything in lowercase and numeric format as well to account for user input too. 


## Data Storage
Our datastorage will be in a graph format, with a node for each airport, and probably a vector storing all the paths to other airports (with information on the path). This should result is a space complexity of O(V+E), using an adjacency list, since each edge for each vertice has to be stored w/ all the assecory data needed (realistically the number will . We will aim to make our graph contain as all the data, so even though it might be heavy, it will make traversals and processing easier for us. 

## Algorithm 
Right now, we think that finding connected components in airports, we would use Depth First search to find the number of connected airport networks. To find the shortest path between two points, we can use an algorithm like Dijkstras. This is an example of a minimum spanning tree problem. Finally, to find the radius of flights within an n amount of flights, we can use Breadth First search and then prune the values that exceed our limits. 

#### Function Inputs
Our function input would be something simmilar to a menu where you can pick options of what data you want to explore. So we would first use a numeric menu and then based on what option they choose, compute what data they want to see. Two things that need input are the path between A and B, and choosing a location A to start at and radius to go out of. For the former, we can have people input city names and then we explain the route with other data. For the latter, we can have them iput a city name and a value (such as 3) that indicates the maximum amount of flights they want to take. 

#### Function Outputs
The outputs will be printed out in the terminal in a neatly formatted manner. We may also build a small web-based app that takes the processed data and displays it in an interactive dashboard or atop a map to visualize the flight paths and insights. 

#### Function Efficiency
For both DFS and BFS, we expect it to run in worst case O(V + E) where V are airports (verticies) and E are Routes (edges). In addition to that, we will probably have a worst space complexity of O(E) since we will be storing every path between the airports. Finally, Djikstra's Algorithm to find the shortest path will be O(V^2) (V calculations which take O(V) time) using an adjacency matrix. However, if we use an adjacency list, we learned in class that the time can be shortened down. We anticipate the space complexity to be at most O(V^2) since we will have V possible airports matching to V-1 other airports. Maybe we can shorten that down by using an adjacency list implementation. 


## Timeline

November 12: Finish parsing and processing data and making its graph representation 

November 18: Implement BFS and DFS

December 2: Finish rest of algorithms, possibly Djikstra, A*, PageRank(to find commonly connected airports)

December 9: Have everything turned in (and develop a UI to visualize) 
