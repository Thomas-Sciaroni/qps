#include "graphToPath.h"


graphToPath::graphToPath() {
    VERTICES = 0;
}

//Input: takes a mazeToGraph object as input.
//Func: Steps through the adjacency matrix and creates the quickest path.
//Output: It updates distance[], quickestPathTree[], and parent[].
//		The parent[] and quickestPathTree[] contain the "minimum tree" of the vertices used in the quickest path.
void graphToPath::dijkstra(mazeToGraph &maze) {
    VERTICES = maze.getDimensionsSq();
    int errval = dim*100;
    int source = 0;
    double dist;
    distance = new double [VERTICES];
    quickestPathTree = new bool [VERTICES];
    parent = new int [VERTICES];

    for (int i = 0; i < VERTICES; i++) {
        distance[i] = HUGE_VAL;
        quickestPathTree[i] = false;
    }

    distance[source] = 0;
    quickestPathTree[source] = true;


    for(int i = 0; i != VERTICES; ++i){
        if(maze.adjMatAccess(source, i) != 0){
            distance[i] = maze.adjMatAccess(source,i);
        }
    }

    for (int counter = 0; counter < VERTICES-1; counter++) {
        int current = nextMin();
        quickestPathTree[current] = true;

        //update neighbours, if applicable
        for (int i = 0; i < VERTICES; i++) {

            if (!quickestPathTree[i] ){//worth checking
                dist = maze.adjMatAccess(current, i);
                if(dist != 0 && dist < errval){ //valid distance between two vertices
                    if(distance[current]+dist < distance[i]){
                        parent[i] = current;
                        distance[i] = distance[current] + maze.adjMatAccess(current, i);
                    }
                }
            }
        }
    }

    //create end marker on the array.
    parent[source] = -1;
}

//finds the next index for dijkstra() with minimum weighted distance.
int graphToPath::nextMin() {
    double min_val = HUGE_VAL;
    int min_index = 0;
    for (int i = 0; i < VERTICES; i++) {
        if (!quickestPathTree[i] && distance[i] <= min_val) {
            min_val = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

//prints the vertices on the quickest path for a selected target.
//The source is initialized in dijkstra().
void graphToPath::printDirections(int target) {
    //ensure that target is w/in bounds.
    if (target >= VERTICES) {
        std::cout << "err: illegal target. cannot print path. " << std::endl;
        return;
    }
    else if (parent[target] == -1) {
        std::cout << target << std::endl;
        return;
    }
    else {
        this->printDirections(parent[target]);
        std::cout << target << std::endl;
    }
}

//finds the quickest path for a given mazeToGraph object.
void graphToPath::findPath(mazeToGraph &maze) {
    dim = maze.getDimensions();
    int target1 = ((dim*dim)/2)+((dim/2)-1);
    int target2 = ((dim*dim)/2)+(dim/2);
    int target3 = ((dim*dim)/2)-(dim/2);
    int target4 = ((dim*dim)/2)-((dim/2)+1);
    dijkstra(maze);
    //pick the shortest one now
    int min_path_target = target1;
    if (distance[target2] < distance[min_path_target]) {
        min_path_target = target2;
    }
    else if (distance[target3] < distance[min_path_target]) {
        min_path_target = target3;
    }
    else if (distance[target4] < distance[min_path_target]) {
        min_path_target = target4;
    }
    std::cout << distance[min_path_target] << std::endl;
}