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


int main() {

    std::string filename = "test_data.txt";
    DataStorage dataStorage;

    dataStorage.readData(filename);
    dataStorage.printData();
    
    Graph graph;
    graph.generateGraph(dataStorage);
    graph.print();

    Solver solver;
    unsigned int maxFlow = solver.fordFulkerson(graph.getRepresentation(), graph.getSize(), graph.getLimit());
    unsigned int requiredFlow = dataStorage.getProjectsNum();

    if(maxFlow < requiredFlow) {
        std::cout << "Cannot assign workers.\n";
    } else {
        solver.decryptResults(dataStorage);
    }
}