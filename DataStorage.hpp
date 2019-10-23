#ifndef DATASTORAGE_HPP
#define DATASTORAGE_HPP

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

class DataStorage{

private:

    void make_unique(std::vector< std::string > &vec) {

        std::sort(vec.begin(), vec.end());
        auto last = std::unique(vec.begin(), vec.end());
        vec.erase(last, vec.end());
    }

    size_t projects_num = 0;
    size_t workers_num = 0;
    size_t sectors_num = 0;
    size_t limit = 0;

    std::vector< std::string > projects;
    std::vector< std::string > sectors;
    std::vector< Worker > workers;

    int** possible_matches;
    int** result_tab;

public:

    DataStorage() {}

    size_t getProjectsNum(){
        return projects_num;
    }

    size_t getWorkersNum() {
        return workers_num;
    }

    size_t getSectorsNum() {
        return sectors_num;
    }

    size_t getLimit() {
        return limit;
    }
    
    int getSectorId(std::string sector) {

        auto it = std::find(sectors.begin(), sectors.end(), sector);
        if( it == sectors.end() ) {
            return -1;
        }

        return std::distance(sectors.begin(), it);
    }

    std::string getSectorAt(size_t index) {

        if(index > sectors_num) {
            throw std::out_of_range("There is no such worker");
        }
        return sectors[index];
    }

    int getProjectId(std::string project) {

        auto it = std::find(projects.begin(), projects.end(), project);
        if( it == projects.end() ) {
            return -1;
        }

        return std::distance(projects.begin(), it);
    }

    Worker getWorkerAt(size_t index) {

        if(index > workers_num) {
            throw std::out_of_range("There is no such worker");
        }
        return workers[index];
    }

    std::string getProjectAt(size_t index) {
        
        if(index > projects_num) {
            throw std::out_of_range("There is no such project");
        }
        return projects[index];
    }
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

            Worker worker(name, sector, count);
            sectors.push_back(sector);

            while(iss >> project) {
                worker.add_project(project);
                projects.push_back(project);
            }

            workers.push_back(worker);
            count++;
        }

        make_unique(sectors);
        make_unique(projects);

        workers_num = workers.size();
        projects_num = projects.size();
        sectors_num = sectors.size();
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