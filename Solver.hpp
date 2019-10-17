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
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Worker.hpp"

class Solver{

private:

    void print_single_1D_vector(std::vector< std::string> vec_to_print) {

        for(std::string element : vec_to_print) {
            std::cout << element << "\n";
        }
        std::cout << "\n";
    }

    std::set< std::string > sectors;
    std::vector< Worker > workers;
    int** possible_matches;

public:

    //TODO
    //Add delete in destructor

    Solver() {}

    int read_data(std::string filename){

        std::string name;
        std::string sector;
        std::string line;
        std::string project;
        unsigned int count = 0;

        std::ifstream infile(filename);
        
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            if (!(iss >> name >> sector)) { 

                return 1; 
            }

            Worker worker(name, sector);
            sectors.insert(sector);

            while(iss >> project) {
                worker.add_project(project);
            }

            workers.push_back(worker);
        }
        return 0;
    }

    void generate_possible_matches() {

        int row_num = sectors.size();
        int column_num = workers.size();

        possible_matches = new int*[row_num];

        for(int i = 0; i < row_num; ++i) {
            possible_matches[i] = new int[column_num];
        }

        int x = 0;
        int y = 0;

        for( auto sector : sectors ) {

            y = 0;
            for( auto worker : workers ) {

                possible_matches[x][y] =  ( worker.getSector() == sector );
                y++;
            }
            x++;
        }
    }    
    void print_data() {

        for( auto worker : workers ) {
            std::cout << worker << "\n";
        }

        std::cout << "\n";

        for( auto sector : sectors ) {

            std::cout << sector << "\n";
        }
        
        std::cout << "\n";
    }

    void print_possible_matches() {

        int row_num = sectors.size();
        int column_num = workers.size();

        std::cout << "##";
        for(int i = 0 ; i < column_num; i++) {

            std::cout <<"#" << i;
        }
        std::cout << "\n";

        // not using for each, because x is printed
        for(int x = 0; x < row_num; x++) {
            
            //TODO fit to number of digits
            std::cout << x << "# ";
            for(int y = 0; y < column_num; y++) {

                std::cout << possible_matches[x][y] << " ";
            }
            std::cout << "\n";
        }

    }
};

#endif 