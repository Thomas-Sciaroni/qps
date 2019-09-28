#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>
#include "graphToPath.h"
#include "mazeToGraph.h"
#include "floodFill.h"

int main(int argc, char **argv) {
    FILE *inputMaze;
    size_t linesize = 0;
    ssize_t linelen;
    mazeToGraph graph;
    char *filename = ((char*)(malloc(sizeof(char) * 100)));
    if(argc > 1){
        strcpy(filename, argv[1]);
        //std::cout << "Name of maze file: " << filename << std::endl;
    }
    //input file and maze and mouse parameters
    if(argc == 8){
        char *mazeUnitWidth = ((char*)(malloc(sizeof(char) * 100)));
        char *mazeDimension = ((char*)(malloc(sizeof(char) * 100)));
        char *mouseMaxSpeed = ((char*)(malloc(sizeof(char) * 100)));
        char *mousePosAccel = ((char*)(malloc(sizeof(char) * 100)));
        char *mouseNegAccel = ((char*)(malloc(sizeof(char) * 100)));
        char *mouseLatAccel = ((char*)(malloc(sizeof(char) * 100)));
        strcpy(mazeUnitWidth,argv[2]);
        strcpy(mazeDimension,argv[3]);
        strcpy(mouseMaxSpeed,argv[4]);
        strcpy(mousePosAccel,argv[5]);
        strcpy(mouseNegAccel,argv[6]);
        strcpy(mouseLatAccel,argv[7]);

        graph.mazeParamUpdate(strtod(mazeUnitWidth, nullptr), atoi(mazeDimension));
        graph.mouseParamUpdate(strtod(mouseMaxSpeed, nullptr), strtod(mousePosAccel, nullptr),
                               strtod(mouseNegAccel, nullptr),strtod(mouseLatAccel, nullptr));
    }
    else if (argc != 2){
        char errmsg[30] = "Invalid CLI Arguments \n";
        write(STDERR_FILENO, errmsg, strlen(errmsg));
        exit(0);
    }

    bool import = graph.importMaze(filename);
    if(import){
        graph.generateGraph();
    }
    else{
        char error_message[30] = "File Import Failure\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
    }
    if(graph.ready()){
        graphToPath path;
        floodFill flood;
        path.findPath(graph);
        flood.findPath(graph);
    }
    else{
        char error_message[30] = "Graph Generation Failure\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
    }

}

