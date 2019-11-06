#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <pthread.h> 
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>  
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream> 
#include <limits.h> 
#include <string.h> 
#include <queue> 

#include "GraphHelpClasses.hpp"
#include "DataStorage.hpp"

class Solver{

    private:
        std::vector< Path > algorithmResults;

    public:
         /*
            A simple bfs function using queue
        */
        bool bfs(std::vector< Connection >* graph, int s, int t, VertexParent parents[], size_t graphSize);

        /*  
            simple algorithm that checks maximum flow in graph.
            The aim is to have the flow of projects num.

            It is modified to work on optimised data structures
        */
        int fordFulkerson(std::vector< int >* graphRepresentation, size_t graphSize, size_t limit);

        /*
            structure algorithm_results stores the information
            about vertexes that create path starting in s and ending in t.

            To generate results, it has to be decrypted.
        */
        void decryptResults(DataStorage dataStorage);
};
#endif