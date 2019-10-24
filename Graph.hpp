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
    
    // makes a connection a => b ( with value val )
    void make_one_direction_connection_between(int a, int b, int val);

    std::vector< Connection >* graph_representation;
    size_t graph_size = 0;
    std::vector< Path > algorithm_results;

public:
    
    Graph() {}

    /*
        structure algorithm_results stores the information
        about vertexes that create path starting in s and ending in t.

        To generate results, it has to be decrypted.
    */
    void decryptResults(DataStorage data_storage);

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
    void generate_graph(DataStorage data_storage);

    void print();

    /*
        A simple bfs function using queue
    */
    bool bfs(std::vector< Connection >* graph, int s, int t, VertexParent parents[]);

    /*  
        simple algorithm that checks maximum flow in graph.
        The aim is to have the flow of projects num.

        It is modified to work on optimised data structures
    */
    int fordFulkerson();

}; 
#endif 