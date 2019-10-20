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

    std::string filename = "test_data_2.txt";
    Solver solver;
    solver.read_data(filename);
    solver.print_data();
    solver.generate_possible_matches();
    solver.print_possible_matches();
    solver.solve();
    // solver.preSolve();
    solver.print_possible_matches();
}