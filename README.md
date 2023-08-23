# CS225 Final Project
*By David An, Dhiraj Kuttichirayil, Kaitlyn Chan* 

> Our project is to use a flights/airports dataset to gain insight into the flow or airtravel out of any given destination airport. We will go this by representing the data as a graph and applying various graph algorithms in C++

Here's a link a a video presentation by us detailing our work on this project : **INSERT LINK HERE :(**

You can view a written report of our results in the `results.md` file here on the GitHub.

## Code
All the code functionality for this project can be found in the `src/` directory. Test cases used to verify accuracy can be seen in the `tests/` directory.

You can compile our project in the CS225 Docker environment as follows (identical to 225 mp/lab instructions)

```bash
mkdir build
cd build
cmake ..
```

After this your can run our project using `./main` for example function usage, the the `./test` file to run our testcases
- `./main` will run an interactive CLI that you can interact with to use each of the features we have built to your specifications
## Data
Our test data was obtained from Stanford SNAP's collection of graph data, namely the "Airports in the United States" dataset which was be found [here](http://snap.stanford.edu/class/cs224w-2018/data.html)

The `.csv` versions of these files used by our program are located in the `data/` directory.

There are 2 main datasets
1. *reachability-meta.csv* which contains metadata for each airport in the dataset
2. *reachability.txt* which contains the similarity between 2 connected airports.

There remaining data files are subsets of the data aforementioned, used for testing/verification purposes.


## Propsal Documents
You can find our proposal and contract documents in the `documents/` folder
