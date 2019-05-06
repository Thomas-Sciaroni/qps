#ifndef QPS_GRAPHTOPATH_H
#define QPS_GRAPHTOPATH_H

#include "mazeToGraph.h"

class graphToPath{
private:
    // int *verticesOnPath1;
    // int *verticesOnPath2;
    // int *verticesOnPath3;
    // int *verticesOnPath4;
    // int lenPath1;
    // int lenPath2;
    // int lenPath3;
    // int lenPath4;
    // int chosenPath;
    bool* quickestPathTree;
    double* distance;
    int* parent;
    void dijkstra(mazeToGraph&);
    int minDistance();
public:
    // void printDirections();
    void printDirections(int);
    void findPath(mazeToGraph&); //calls printDirections() before returning
};

#endif