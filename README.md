# qps
Quickest Path Search - Finds the quickest path through a micromouse maze.

## mazeToGraph Class
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
