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
    int** possible_matches_copy;
    int* chosen_workers;

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
        possible_matches_copy = new int*[row_num];
        chosen_workers = new int[row_num];

        for(int i = 0; i < row_num; i++) {
            chosen_workers[i] = -1;
        }

        for(int i = 0; i < row_num; i++) {
            possible_matches[i] = new int[column_num];
            possible_matches_copy[i] = new int[column_num];
        }

        int x = 0;
        int y = 0;

        for( auto project : projects ) {

            y = 0;
            for( auto worker : workers ) {

                std::cout << x << " " << y << "\n";
                possible_matches[x][y] = worker.isInProject(project);
                possible_matches_copy[x][y] = worker.isInProject(project);
                y++;
            }
            x++;
        }
    }
    void solve() {

        // 1. jesli przypisano kazdemu projektowi, wyjdz

        // 2. dla kazdego rzedu
        //    jesli jest 1 w tablicy matching, sprawdz czy po dodaniu osiagnie limit
        //    
        /*
            1. jesli przypisano reprezentanta kazdego projektowi, wyjdz

            2. dla kazdego rzedu
                2.1 dla kazdej komorki - jesli jest 1 w tablicy matching, sprawdz czy po dodaniu osiagnie sie limit
                    2.1.1 jesli tak, iteruj dalej
                    2.1.2 jesli nie dodaj
                
                2.2 jesli przejdzie sie za ostatnia komorke i nie znajdzie sie dopasowania, to usun szukajac 
                    od poczatku, pracownika, ktory jest z wadliwego dzialu i przejdz do dopasowania innego zamiast niego
        */
        std::map< std::string, int > count_map;
        std::string problematic_sector;

        bool swapped = false;
        bool finished = false;

        int problematic_x;
        int problematic_y;
        int help_tab[projects.size()][workers.size()];
        int count = 0;

        for(int x = 0; x < projects.size(); x++) {

            for(int y = 0; y < workers.size(); y++) {
                help_tab[x][y] = 0;
            }
        }

        for( auto sector : sectors ) {
            count_map[sector] = 0;
        }

        int limit = projects.size() / 2;

        for(int x = 0; x < projects.size() && !finished; x++) {

            for(int y = 0; y < workers.size() && !finished ; y++) {

                // sleep(2);    
                std::cout << "analising " << x << " " << y << "\n"; 
                if(count == projects.size()) {
                    finished = true;
                }

                if( x == -1) {

                    std::cout << "matching impossible\n";    
                    return;
                }
                std::cout << x << " " << y << "\n";    
                if( possible_matches[x][y] != 0 ) {

                    std::string sector_name = workers[y].getSector();
                    if(count_map[sector_name] < limit) {

                        help_tab[x][y] = 1;
                        count_map[sector_name]++;
                        count++;
                        std::cout << sector_name << " " << count_map[sector_name] << "\n";

                        break;
                    } else {

                        std::cout << "Problem occured " << sector_name << " " << x << " " << y << "\n";
                        problematic_sector = sector_name;
                        problematic_x = x;
                        problematic_y = y;
                    }

                }

                // if not found
                if(y == workers.size() - 1) {

                    swapped = false;
                    std::cout << "not found\n";
                    for(int k = 0; k < projects.size() && !swapped ; k++) {

                        for(int l = 0; l < workers.size() && !swapped; l++) {

                            if(help_tab[k][l] == 1) {

                                std::cout << "analising " << k << " " << l << "\n";    
                                std::string sector_chosen = workers[l].getSector();

                                if(sector_chosen == problematic_sector) {

                                    help_tab[k][l] = 0;
                                    help_tab[problematic_x][problematic_y] = 1;

                                    x = k;  
                                    y = -1;

                                    swapped = true;
                                }
                            }
                        }
                    }

                    std::cout << "exited swap loop\n";
                }

                std::cout << x << " " << y << "\n";
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

    void show_results() {

        for(int i = 0; i < projects.size(); i++) {

            std::cout << "projekt nr " << i + 1 << " => " << chosen_workers[i] << "\n";
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
            std::cout <<"#" << i;
        }
        std::cout << "\n";

        // not using for each, because x is printed
        for(int x = 0; x < row_num; x++) {
            
            //TODO fit to number of digits
            std::cout << x  << "# ";
            for(int y = 0; y < column_num; y++) {

                std::cout << possible_matches[x][y] << " ";
            }
            std::cout << "\n";
        }

    }
};
#endif