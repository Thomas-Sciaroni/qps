#ifndef QPS_MAZETOGRAPH_H
#define QPS_MAZETOGRAPH_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>

class mazeToGraph{
private:
    double maxSpeed;
    double maxPosAccel;
    double maxNegAccel;
    double maxLatAccel;
    double mazeUnitWidth;
    int mazeDim;
    double *vectorTable;
    double **adjMat;
    char **binaryWallMat;
    bool imported;
    bool generated;
    int mazeDimSq;
public:
   // mazeToGraph();
    mazeToGraph(double, int, double, double, double, double);
    double adjMatAccess(int, int);
    int getDimensions();
    int getDimensionsSq();
    void mouseParamUpdate(double, double, double, double);
    void mazeParamUpdate(double, int);
    bool importMaze(char*);
    bool generateGraph();
    bool ready();
};

// };
#endif //QPS_MAZETOGRAPH_H
