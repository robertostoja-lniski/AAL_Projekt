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
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

class Solver{

private:

    void print_single_1D_vector(std::vector< std::string> vec_to_print) {

        for(std::string element : vec_to_print) {
            std::cout << element << "\n";
        }
        std::cout << "\n";
    }

    std::vector< std::string > sectors;
    std::vector< std::string > workers;
    std::vector< std::string > projects;

    // dimension 1 - m
    // dimension 2 - worker
    // dimension 3 - sectors for each worker
    std::vector< std::vector< std::vector <unsigned int > > > possible_matches;

public:

    Solver() {}

    int read_data(std::string filename){

        std::string worker;
        std::string sector;
        std::string line;
        std::string project;
        unsigned int id = 0;

        std::ifstream infile(filename);
        
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            if (!(iss >> worker >> sector)) { 

                return 1; 
            }

            workers.push_back(worker);
            sectors.push_back(sector);

    
            while(iss >> project) {

                // Check if element 22 exists in vector
                std::vector<std::string>::iterator it = std::find(projects.begin(), projects.end(), project);

                if (it != vecOfNums.end())
                    std::cout << "Element Found" << std::endl;
                else
                    std::cout << "Element Not Found" << std::endl;    
                                projects.push_back(project);
            }
            // process pair (a,b)
        }

        return 0;
    }

    void print_data() {

        print_single_1D_vector(sectors);
        print_single_1D_vector(workers);
        print_single_1D_vector(projects);
    }
};

#endif 