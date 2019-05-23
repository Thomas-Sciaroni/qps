#ifndef QPSPRIVATE_FLOODFILL_H
#define QPSPRIVATE_FLOODFILL_H

#include "mazeToGraph.h"

class floodFill {
private:
    int VERTICES;
    int* parent;
    int dim;
    int* distance;
    int **adjMat;
    bool* visited;
    double trueDistance;
    void flood(mazeToGraph&);
    int nextMin();
    void rebuildTrueCost(mazeToGraph&, int);
    void generateGraph(mazeToGraph&);
public:
    void findPath(mazeToGraph&);
};

#endif