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

    std::pair< int, int > swap_assignmets(std::string sector, int x_to_swap, int y_to_swap) {

        std::cout << "not found\n";
        for(int x = 0; x < projects_num; x++) {

            for(int y = 0; y < workers_num; y++) {

                if(result_tab[x][y] == 1) {

                    std::cout << "analising " << x << " " << y << "\n";    
                    std::string sector_chosen = workers[y].getSector();

                    if(sector_chosen == sector) {

                        result_tab[x][y] = 0;
                        result_tab[x_to_swap][y_to_swap] = 1;

                        return std::make_pair( x, -1 );
                    }
                }
            }
        }

        std::cout << "exited swap loop\n";
    }
    
    void print_single_1D_vector(std::vector< std::string> vec_to_print) {

        for(std::string element : vec_to_print) {
            std::cout << element << "\n";
        }
        std::cout << "\n";
    }
    
    void make_unique(std::vector< std::string > &vec) {

        std::sort(vec.begin(), vec.end());
        auto last = std::unique(vec.begin(), vec.end());
        vec.erase(last, vec.end());
    }

    size_t projects_num = 0;
    size_t workers_num = 0;
    size_t limit = 0;

    std::vector< std::string > projects;
    std::vector< std::string > sectors;
    std::vector< Worker > workers;

    int** possible_matches;
    int** result_tab;

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
            sectors.push_back(sector);

            while(iss >> project) {
                worker.add_project(project);
                projects.push_back(project);
            }

            workers.push_back(worker);
        }

        make_unique(sectors);
        make_unique(projects);

        workers_num = workers.size();
        projects_num = projects.size();
        limit = projects_num / 2;

        return 0;
    }

    void generate_possible_matches() {

        possible_matches = new int*[projects_num];

        for(int i = 0; i < projects_num; i++) {
            possible_matches[i] = new int[workers_num];
        }

        int x = 0;
        int y = 0;

        for( auto project : projects ) {

            y = 0;
            for( auto worker : workers ) {

                std::cout << x << " " << y << "\n";
                possible_matches[x][y] = worker.isInProject(project);
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
        int count = 0;

        result_tab = new int*[projects_num];

        for(int i = 0; i < projects_num; i++) {
            result_tab[i] = new int[workers_num];
        }

        for(int x = 0; x < projects_num; x++) {

            for(int y = 0; y < workers_num; y++) {
                result_tab[x][y] = 0;
            }
        }

        for( auto sector : sectors ) {
            count_map[sector] = 0;
        }

        for(int x = 0; x < projects_num && !finished; x++) {

            for(int y = 0; y < workers_num && !finished ; y++) {
    
                std::cout << "analising " << x << " " << y << "\n"; 
                if(count == projects_num) {
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

                        result_tab[x][y] = 1;
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
                if(y == workers_num - 1) {

                    auto point = swap_assignmets(problematic_sector, problematic_x, problematic_y);
                    x = point.first;
                    y = point.second;
                }

                std::cout << x << " " << y << "\n";
            }
            
        }

       for (std::map<std::string,int>::iterator it=count_map.begin(); it!=count_map.end(); ++it) {
            std::cout << it->first << " => " << it->second << '\n';
       }

        for(int x = 0; x < projects.size(); x++) {

            for(int y = 0; y < workers.size(); y++) {

                possible_matches[x][y] = result_tab[x][y];
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

        std::cout << "pw";
        for(int i = 0 ; i < workers_num; i++) {
            std::cout <<"#" << i;
        }
        std::cout << "\n";

        // not using for each, because x is printed
        for(int x = 0; x < projects_num; x++) {
            
            //TODO fit to number of digits
            std::cout << x  << "# ";
            for(int y = 0; y < workers_num; y++) {

                std::cout << possible_matches[x][y] << " ";
            }
            std::cout << "\n";
        }

    }
};
#endif