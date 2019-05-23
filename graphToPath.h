#ifndef QPS_GRAPHTOPATH_H
#define QPS_GRAPHTOPATH_H

#include "mazeToGraph.h"

class graphToPath {
private:
    int VERTICES;
    int dim;
    bool* quickestPathTree;
    double* distance;
    int* parent;
    void dijkstra(mazeToGraph&);
    int nextMin();
public:
    graphToPath();
    void printDirections(int);
    void findPath(mazeToGraph&);
};

#endif