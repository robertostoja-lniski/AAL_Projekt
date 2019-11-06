#ifndef GRAPH_HPP
#define GRAPH_HPP

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

#include "DataStorage.hpp"
#include "GraphHelpClasses.hpp"

/*  
    A class that represents a graph with methods dedicated
    to solve graph algorithms
*/
class Graph{

private:
    
    // makes a connection a => b
    void makeOneDirectionalConnectionBetween(int a, int b);

    std::vector< int >* graphRepresentation;
    size_t graphSize = 0;
    size_t limit = 0;

public:
    
    Graph() {}

    /*
        Function generating graph:

        From s egdes go to every of sectors. Value on these edges is m / 2.
        It means that at first we try to take a worker from a sector
        and we are sure that there will not be more workers from any sector than m / 2.

        Then from every sector goes an edge to worker that belongs to this sector.

        From workers there is edge to every project that he belongs to 
        ( he can represent every projected that he is working in ).

        From projects flow goes to t.

        Edges from s to sectors have flow m / 2. Every other edge has 1.
    */
    void generateGraph(DataStorage data_storage);

    void print();

    std::vector< int >* getRepresentation();

    size_t getSize();

    size_t getLimit();

}; 
#endif