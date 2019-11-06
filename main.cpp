#include <pthread.h> 
#include <unistd.h>
#include "Graph.hpp"
#include "DataStorage.hpp"
#include "Solver.hpp"

#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>  
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>

#define TIME_RAPORT 1
#define VERBOSE 0
#define TIME_RAPORT_FILE "time_raport.csv"

int main(int argc, char *argv[]) {

    if(argc != 2) {    
        std::cout << "run ./a.out test_file.txt \n";
        return 1;
    }

    std::string filename = argv[1];
    DataStorage dataStorage;

    dataStorage.readData(filename);

#if(VERBOSE)    
    dataStorage.printData();
#endif

    Graph graph;
    graph.generateGraph(dataStorage);

#if(VERBOSE)    
    graph.print();
#endif

    Solver solver;

#if(TIME_RAPORT)
    auto s = std::chrono::high_resolution_clock::now();
#endif

    unsigned int maxFlow = solver.fordFulkerson(graph.getRepresentation(), graph.getSize(), graph.getLimit());
    unsigned int requiredFlow = dataStorage.getProjectsNum();

#if(TIME_RAPORT)
    auto t = std::chrono::high_resolution_clock::now();
    double diff = std::chrono::duration<double, std::milli>(t-s).count();

    std::ofstream timeRaport;
    timeRaport.open(TIME_RAPORT_FILE, std::ios::app );
    timeRaport << diff << "\n";

#endif

#if(VERBOSE)
    if(maxFlow < requiredFlow) {
        std::cout << "Cannot assign workers.\n";
    } else {
        solver.decryptResults(dataStorage);
    }
#endif

}