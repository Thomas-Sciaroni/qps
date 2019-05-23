#include "floodFill.h"
#include <cstdio>
#include <limits>

#define NORTH         (uint8_t)0x01
#define EAST          (uint8_t)0x02
#define SOUTH         (uint8_t)0x04
#define WEST          (uint8_t)0x08

void floodFill::flood(mazeToGraph &maze) {
    int errval = dim*100;
    int source = 0;
    int dist;
    distance = new int [VERTICES];
    visited = new bool [VERTICES];
    parent = new int [VERTICES];

    for (int i = 0; i < VERTICES; i++) {
        distance[i] = std::numeric_limits<int>::max();
        visited[i] = false;
    }

    distance[source] = 0;
    visited[source] = true;


    for(int i = 0; i != VERTICES; ++i){
        if(adjMat[source][i] != 0){
            distance[i] = adjMat[source][i];
        }
    }

    for (int counter = 0; counter != VERTICES; counter++) {
        int current = nextMin();
        visited[current] = true;

        //update neighbours, if applicable
        for (int i = 0; i != VERTICES; i++) {

            if (!visited[i] ){//worth checking
                dist = adjMat[current][i];
                if(dist != 0 && dist < errval){ //valid distance between two vertices
                    if(distance[current]+dist < distance[i]){
                        parent[i] = current;
                        distance[i] = distance[current] + adjMat[current][i];
                    }
                }
            }
        }
    }

    //create end marker on the array.
    parent[source] = -1;
}

//finds the next index for dijkstra() with minimum weighted distance.
int floodFill::nextMin() {
    double min_val = std::numeric_limits<int>::max();
    int min_index = 0;
    for (int i = 0; i < VERTICES; i++) {
        if (!visited[i] && distance[i] <= min_val) {
            min_val = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

void floodFill::rebuildTrueCost(mazeToGraph &maze, int target) {
    if (target >= VERTICES) {
        std::cout << "err: illegal target. cannot print path. " << std::endl;
        return;
    }
    else if (parent[target] == -1) {
        return;
    }
    else {
        //std::cout << target << "\t\t" << trueDistance << std::endl;
        trueDistance += maze.adjMatAccess(target, parent[target]);
        this->rebuildTrueCost(maze, parent[target]);
    }
}

void floodFill::generateGraph(mazeToGraph& maze) {
    int offset, v1, v2, distance;

    adjMat = new int *[VERTICES];
    for(int i = 0; i != VERTICES; ++i){
        adjMat[i] = new int [VERTICES];
        for(int j = 0; j != VERTICES; ++j){
            adjMat[i][j] = 0;
        }
    }

    //North-South sight-lines
    for(int i = 0; i != dim; ++i){
        for(int j = 0; j != dim; ++j){
            if((maze.binWallMatAccess(i,j) & SOUTH) == SOUTH){
                if((maze.binWallMatAccess(i,j) & NORTH) != NORTH){
                    offset = 1;
                    while((maze.binWallMatAccess(i,j+offset) & NORTH) != NORTH){
                        offset++;
                    }
                    for(int k = 0; k < offset; ++k){
                        for(int m = k + 1; m <= offset; ++m){
                            v1 = ((i * 16) + (j + k));
                            v2 = ((i * 16) + (j + m));
                            distance = m - k;
                            adjMat[v1][v2] = distance;
                            adjMat[v2][v1] = distance;
                        }
                    }
                }
            }
        }
    }

    //East-West sight-lines
    for(int i = 0; i != dim; ++i){
        for(int j = 0; j != dim; ++j){
            if((maze.binWallMatAccess(i,j) & WEST) == WEST){
                if((maze.binWallMatAccess(i,j) & EAST) != EAST){
                    offset = 1;
                    while((maze.binWallMatAccess(i+offset,j) & EAST) != EAST){
                        offset++;
                    }
                    for(int k = 0; k < offset; ++k){
                        for(int m = k + 1; m <= offset; ++m){
                            v1 = (((i + k) * 16) + j);
                            v2 = (((i + m) * 16) + j);
                            distance = m - k;
                            adjMat[v1][v2] = distance;
                            adjMat[v2][v1] = distance;
                        }
                    }
                }
            }
        }
    }
}

//finds the quickest path for a given mazeToGraph object.
void floodFill::findPath(mazeToGraph &maze) {
    dim = maze.getDimensions();
    VERTICES = maze.getDimensionsSq();
    trueDistance = 0;
    generateGraph(maze);
    int target1 = ((dim*dim)/2)+((dim/2)-1);
    int target2 = ((dim*dim)/2)+(dim/2);
    int target3 = ((dim*dim)/2)-(dim/2);
    int target4 = ((dim*dim)/2)-((dim/2)+1);
    flood(maze);
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
    rebuildTrueCost(maze, min_path_target);
    std::cout << trueDistance << std::endl;
}