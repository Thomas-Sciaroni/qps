#include "graphToPath.h"

void graphToPath::dijkstra(int target, mazeToGraph &maze) {
    int source = 0;

}

void graphToPath::printDirections() {

}

void graphToPath::findPath(mazeToGraph &maze) {
    int dimension = maze.getDimensions();
    int target1 = ((dimension*dimension)/2)+(dimension-1);
    int target2 = ((dimension*dimension)/2)+(dimension);
    int target3 = ((dimension*dimension)/2)-(dimension);
    int target4 = ((dimension*dimension)/2)-(dimension+1);
    dijkstra(target1, maze);
    dijkstra(target2, maze);
    dijkstra(target3, maze);
    dijkstra(target4, maze);
    //pick the shortest one now
}