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
#include "Worker.hpp"

class Solver{

private:

    void print_single_1D_vector(std::vector< std::string> vec_to_print) {

        for(std::string element : vec_to_print) {
            std::cout << element << "\n";
        }
        std::cout << "\n";
    }

    std::set< std::string > projects;
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
                projects.insert(project);
            }

            workers.push_back(worker);
        }
        return 0;
    }

    void generate_possible_matches() {

        int row_num = projects.size();
        int column_num = workers.size();

        possible_matches = new int*[row_num];

        for(int i = 0; i < row_num; ++i) {
            possible_matches[i] = new int[column_num];
        }

        int x = 0;
        int y = 0;

        for( auto project : projects ) {

            y = 0;
            for( auto worker : workers ) {

                possible_matches[x][y] = worker.isInProject(project);
                y++;
            }
            x++;
        }
    }
    void solve() {
        
        // maybe hide check inside my_map
        // that iherits from std map ?
        std::map< std::string, int > count_map;
        int help_tab[projects.size()][workers.size()];

        for(int x = 0; x < projects.size(); x++) {

            for(int y = 0; y < workers.size(); y++) {
                help_tab[x][y] = 0;
            }
        }

        for( auto sector : sectors ) {
            count_map[sector] = 0;
        }

        int limit = projects.size() / 2;

        for(int x = 0; x < projects.size(); x++) {

            for(int y = 0; y < workers.size(); y++) {

                std::cout << x << " " << y << "\n";    
                if( possible_matches[x][y] != 0 ) {

                    std::string sector_name = workers[y].getSector();

                    if(count_map[sector_name] < limit) {

                        help_tab[x][y] = 1;
                        count_map[sector_name]++;
                        break;
                    }

                }
            }
        }

       for (std::map<std::string,int>::iterator it=count_map.begin(); it!=count_map.end(); ++it) {
            std::cout << it->first << " => " << it->second << '\n';
       }

        for(int x = 0; x < projects.size(); x++) {

            for(int y = 0; y < workers.size(); y++) {

                possible_matches[x][y] = help_tab[x][y];
            }
        }
        
    }    
    void print_data() {

        for( auto worker : workers ) {
            std::cout << worker << "\n";
        }

        std::cout << "\n";

        for( auto project : projects ) {

            std::cout << project << "\n";
        }
        
        std::cout << "\n";
    }

    void print_possible_matches() {

        int row_num = projects.size();
        int column_num = workers.size();

        std::cout << "pw";
        for(int i = 0 ; i < column_num; i++) {
            std::cout <<"#" << i + 1;
        }
        std::cout << "\n";

        // not using for each, because x is printed
        for(int x = 0; x < row_num; x++) {
            
            //TODO fit to number of digits
            std::cout << x + 1 << "# ";
            for(int y = 0; y < column_num; y++) {

                std::cout << possible_matches[x][y] << " ";
            }
            std::cout << "\n";
        }

    }
};
#endif