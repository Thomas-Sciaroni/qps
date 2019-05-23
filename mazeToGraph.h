#ifndef QPS_MAZETOGRAPH_H
#define QPS_MAZETOGRAPH_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>

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
    uint8_t **binaryWallMat;
    bool imported;
    bool generated;
    int mazeDimSq;
public:
    explicit mazeToGraph(double = 0.180, int = 16, double = 1.0 , double = 4.0, double = 5.0, double = 0.8);
    int getDimensions();
    double adjMatAccess(int, int);
    uint8_t binWallMatAccess(int, int);
    int getDimensionsSq();
    void mouseParamUpdate(double, double, double, double);
    void mazeParamUpdate(double, int);
    bool importMaze(char*);
    bool generateGraph();
    bool ready();
};

// };
#endif //QPS_MAZETOGRAPH_H
