#include "graphToPath.h"
#include <cstdio>

//Macro for making dijkstra() simpler to write.
#define VERTICES         maze.getDimensionsSq()


//import adjmat using maze.adjMatAccess()
//remember to check if the return result is 100*getDimensions()
// void graphToPath::dijkstra(int target, mazeToGraph &maze) {
 void graphToPath::dijkstra(mazeToGraph &maze) {
    int source = 0;
    distance = new double [VERTICES];
    quickestPathTree = new bool [VERTICES];
    parent = new int [VERTICES];

    for (int i = 0; i < VERTICES; i++) {
        distance[i] = HUGE_VAL;
        quickestPathTree[i] = false;
        parent[source] = -1;
    }

    distance[source] = 0;

    for (int counter = 0; counter < VERTICES-1; counter++) {
        int current = minDistance();
        quickestPathTree[current] = true;

        for (int i = 0; i < VERTICES; i++) {
            if (!quickestPathTree[i] && (maze.adjMatAccess(current, i) != (100*maze.getDimensions())) && ((distance[current]+maze.adjMatAccess(current, i)) < distance[i]))
            {
                parent[i] = current;
                distance[i] = distance[current] + maze.adjMatAccess(current, i);
            }
        }
    }
}

//finds the next index for dijkstra() with minimum distance.
int graphToPath::minDistance() {
    double min_val = HUGE_VAL;
    int min_index = 0;
    for (int i = 0; i < VERTICES; i++) {
        if (quickestPathTree[i] == false && distance[i] <= min_val) {
            min_val = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

//prints the vertices on the quickest path for a selected target. 
void graphToPath::printDirections(int target) {
    if (parent[target] == -1) return;

    printDirections(parent[target]);

    printf("%d  ", target);
    return; 
}

void graphToPath::findPath(mazeToGraph &maze) {
    int dimension = maze.getDimensions();
    int target1 = ((dimension*dimension)/2)+(dimension-1);
    int target2 = ((dimension*dimension)/2)+(dimension);
    int target3 = ((dimension*dimension)/2)-(dimension);
    int target4 = ((dimension*dimension)/2)-(dimension+1);
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

    printf("The quickest path for the given parameters is...\n");
    printDirections(min_path_target);

    // dijkstra(target1, maze, verticesOnPath1);
    // dijkstra(target2, maze, verticesOnPath2);
    // dijkstra(target3, maze, verticesOnPath3);
    // dijkstra(target4, maze, verticesOnPath4);    
}