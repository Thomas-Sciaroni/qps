#include "mazeToGraph.h"

//Macros for interacting with binary mazefiles
#define NORTH         (uint8_t)0x01
#define EAST          (uint8_t)0x02
#define SOUTH         (uint8_t)0x04
#define WEST          (uint8_t)0x08


//constructor with default maze parameters
mazeToGraph::mazeToGraph(double mUW, int mD, double mS, double mPA, double mNA, double mLA) {
    mazeParamUpdate(mUW, mD);
    mouseParamUpdate(mS, mPA, mNA, mLA);
    generated = false;
    imported = false;
}


//The else return functions as a predictable error code
//a mouse that has a chance of completing the maze in 10 minutes
//will never take 1600 seconds to travel the length of the maze
double mazeToGraph::adjMatAccess(int row, int col) {
    if(ready() && row < mazeDimSq && col < mazeDimSq){
        return adjMat[row][col];
    }
    else{
        return 100*mazeDim;
    }
}

uint8_t mazeToGraph::binWallMatAccess(int row, int col) {
    if(imported && row < mazeDimSq && col < mazeDimSq){
        return binaryWallMat[row][col];
    }
    else{
        return 0xFF;
    }
}

void mazeToGraph::mouseParamUpdate(double mS, double mPA, double mNA, double mLA) {
    maxSpeed = mS;          //meters per second
    maxPosAccel = mPA;      //meters per second squared
    maxNegAccel = mNA;      //meters per second squared
    maxLatAccel = mLA;      //meters per second squared
}

void mazeToGraph::mazeParamUpdate(double mUW, int mD) {
    mazeUnitWidth = mUW;    //meters
    mazeDim = mD;           //16x16 square units
    mazeDimSq = mazeDim * mazeDim;
}


//imports a binary file (standard format, see documentation)
//takes filename as an argument
bool mazeToGraph::importMaze(char *fname) {
    FILE *mazeFile;
    mazeFile = fopen(fname, "r+");
    //std::cout << "Location of maze file: " << mazeFile << std::endl;
    if (mazeFile == nullptr)
    {
        imported = false;
        return imported;
    }

    binaryWallMat = new uint8_t *[16];
    for (int i = 0; i != 16; ++i) {
        binaryWallMat[i] = new uint8_t[16];
    }
    for(int i = 0; i != mazeDim; ++i){
        for(int j = 0; j != mazeDim; ++j){
            binaryWallMat[i][j] = 0;
        }
    }

    uint8_t value;
    for(int i = 0; i != mazeDim; ++i){
        for(int j = 0; j != mazeDim; ++j){
            fread(&value, 1, 1, mazeFile);
            binaryWallMat[i][j] = value;
        }
    }

    fclose(mazeFile);

    imported = true;
    return imported;
}


//See Documentation for how the vector table is generated
//Each possible distance between two vertices is covered
//in the vectorTable, where the index is the distance
//and the value stored is the cost of traversal (edge weight)
bool mazeToGraph::generateGraph() {
    int offset, v1, v2, distance;
    double  intermediateDistance, intermediateTime, targetDistance, accelRatio,
            posAccelDistance, vMaxLocal, timeToLocalMaxSpeed,
            timeToLocalBrake;
    double vMaxCorner = sqrt(maxLatAccel * mazeUnitWidth * 0.5);
    double timeToMaxSpeed = (maxSpeed - vMaxCorner) / maxPosAccel;
    double timeToBrake = (maxSpeed - vMaxCorner)/ maxNegAccel;
    double distanceToMaxSpeed = ((maxSpeed + vMaxCorner) / 2) * timeToMaxSpeed;
    double distanceToBrake = ((maxSpeed * vMaxCorner) / 2) * timeToBrake;

    vectorTable = new double [mazeDim];
    for(int i = 1; i != mazeDim; ++i){
        targetDistance = mazeUnitWidth * i;
        if((targetDistance) > (distanceToMaxSpeed + distanceToBrake)){
            intermediateDistance = (targetDistance) - distanceToMaxSpeed + distanceToBrake;
            intermediateTime = intermediateDistance / maxSpeed;
            vectorTable[i] = timeToMaxSpeed + intermediateTime + timeToBrake;
        }
        else{
            accelRatio = maxNegAccel / maxPosAccel;
            posAccelDistance = (((targetDistance) * accelRatio) / (accelRatio + 1));
            vMaxLocal = sqrt(vMaxCorner + 2 * maxPosAccel * posAccelDistance);
            timeToLocalMaxSpeed = (vMaxLocal - vMaxCorner) / maxPosAccel;
            timeToLocalBrake = (vMaxLocal - vMaxCorner)/ maxNegAccel;
            vectorTable[i] = timeToLocalMaxSpeed + timeToLocalBrake;
        }
    }


    adjMat = new double *[mazeDimSq];
    for(int i = 0; i != mazeDimSq; ++i){
        adjMat[i] = new double [mazeDimSq];
        for(int j = 0; j != mazeDimSq; ++j){
            adjMat[i][j] = 0;
        }
    }

    //North-South sight-lines
    for(int i = 0; i != mazeDim; ++i){
        for(int j = 0; j != mazeDim; ++j){
            if((binaryWallMat[i][j] & SOUTH) == SOUTH){
                if((binaryWallMat[i][j] & NORTH) != NORTH){
                    offset = 1;
                    while((binaryWallMat[i][j+offset] & NORTH) != NORTH){
                        offset++;
                    }
                    for(int k = 0; k < offset; ++k){
                        for(int m = k + 1; m <= offset; ++m){
                            v1 = ((i * 16) + (j + k));
                            v2 = ((i * 16) + (j + m));
                            distance = m - k;
                            adjMat[v1][v2] = vectorTable[distance];
                            adjMat[v2][v1] = vectorTable[distance];
                        }
                    }
                }
            }
        }
    }

    //East-West sight-lines
    for(int i = 0; i != mazeDim; ++i){
        for(int j = 0; j != mazeDim; ++j){
            if((binaryWallMat[i][j] & WEST) == WEST){
                if((binaryWallMat[i][j] & EAST) != EAST){
                    offset = 1;
                    while((binaryWallMat[i+offset][j] & EAST) != EAST){
                        offset++;
                    }
                    for(int k = 0; k < offset; ++k){
                        for(int m = k + 1; m <= offset; ++m){
                            v1 = (((i + k) * 16) + j);
                            v2 = (((i + m) * 16) + j);
                            distance = m - k;
                            adjMat[v1][v2] = vectorTable[distance];
                            adjMat[v2][v1] = vectorTable[distance];
                        }
                    }
                }
            }
        }
    }

    generated = true;
    return generated;
}

bool mazeToGraph::ready() {
    return (imported && generated);
}

int mazeToGraph::getDimensions() {
    return mazeDim;
}

int mazeToGraph::getDimensionsSq() {
    return mazeDimSq;
}