#include <pthread.h> 
#include <unistd.h>
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

    std::string filename = "test_loop.txt";
    Solver solver;
    solver.read_data(filename);
    solver.print_data();
    solver.generate_possible_matches();
    solver.print_possible_matches();
    int result = solver.solve();

    if(result == EXIT_SUCCESS) {

        solver.print_possible_matches();
        solver.print_results();
    } 
    
}