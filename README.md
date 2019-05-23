# qps
Quickest Path Search - Finds the quickest path through a micromouse maze.


The main program takes in either one or seven command line arguments.  In the case of one command line argument, the argument is simply the maze file to be processed, using the default values for mouse and maze parameters.  In the case of seven command line arguments, the first argument is the maze file and the next six are the mouse and maze parameters.  The output is the time of traversal for the mouse along the quickest path, and the time of traversal for the mouse along the shortest path, delimited with \n.

testAllFiles.sh is a bash script that passes each maze file in the binary folder as an argument to the executable generated by compiling the project.  If your compiled binary is called something other than "qps" or your binary folder is in a different place in the file system with respect to the executable, this script needs to be modified before it will work.


## mazeToGraph Class
mazeToGraph takes a binary maze file from the binary folder and creates a weighted adjacency matrix based on the maze and mouse parameters
### Construction of a graph expects:
#### 4 Mouse Variables: (m/s or m/s^2)
* Maximum Speed
* Maximum Positive Acceleration
* Maximum Negative Acceleration
* Maximum Lateral Acceleration
#### 2 Maze Variables:
* Maze Unit Square Width (meters)
* Maze Dimension (Mazes are n x n Unit Squares)

The default constructor contains default values for each variable.

### Graph Creation:
The graph is created in two steps.  The first involves importing the binary file that encodes the walls of the maze (this is a standard format, see https://github.com/micromouseonline/micromouse_maze_tool#binary). The second involves using the parameters to populate a vector table, which holds the cost of traveling each possible distance, and then traversing the maze and iteratively adding weights for every pair of vertices that can "see" each other using the distance between them and the vector table.

### Graph Access
When the graph is ready to be accessed, the function ready() will return true

Accessing the weights stored in the adjacency matrix from outside the class is only possible with the public function accessAdjMat(int, int), where the two integer arguments are used to select a row and column, respectively.  This is bounds checked, and in the case that the adjacency matrix has not been generated or has an out of bounds exception, the value of 100 * Maze Dimension is returned.  Checking against this value can be used to look for errors in the calling program.  Algorithms should be written with this access pattern in mind.

## graphToPath
graphToPath takes a weighted adjacency matrix and runs dijkstra's algorithm on the matrix to find the quickest (time) path using our weighted edges

## floodFill
floodFill creates a weighted adjacency matrix and sets the edge weights exactly equal to path length, then runs dijkstra's algorithm to find the shortest path (distance) using the weighted edges.  It then recomputes the true cost of the shortest path based on the vector table from mazeToGraph.
