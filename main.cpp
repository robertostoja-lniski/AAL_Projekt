#include <pthread.h> 
#include <unistd.h>
#include "Graph.hpp"
#include "DataStorage.hpp"

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
    DataStorage data_storage;

    data_storage.read_data(filename);
    data_storage.print_data();

    Graph graph;
    graph.generate_graph(data_storage);
    graph.print();
    std::cout << graph.fordFulkerson() << "\n";
    graph.decryptResults(data_storage);
}