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

    void makeUnique(std::vector< std::string > &vec);

    std::vector< std::string > projects;
    std::vector< std::string > sectors;
    std::vector< Worker > workers;

public:

    DataStorage() {}

    void addProject(std::string project){
        projects.push_back(project);
    }

    void addSector(std::string sector){
        sectors.push_back(sector);
    }

    void addWorker(Worker worker){
        workers.push_back(worker);
    }

    size_t getProjectsNum(){
        return projects.size();
    }

    size_t getWorkersNum() {
        return workers.size();
    }

    size_t getSectorsNum() {
        return sectors.size();
    }

    size_t getLimit() {
        return projects.size() / 2;
    }
    
    bool isEmpty() {
        return (projects.size() + sectors.size() + workers.size()) == 0;
    }

    int getSectorId(std::string sector) {

        auto it = std::find(sectors.begin(), sectors.end(), sector);
        if( it == sectors.end() ) {
            return -1;
        }

        return std::distance(sectors.begin(), it);
    }

    std::string getSectorAt(size_t index) {

        if(index > sectors.size()) {
            throw std::out_of_range("There is no such sector");
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

        if(index > workers.size()) {
            throw std::out_of_range("There is no such worker");
        }
        return workers[index];
    }

    std::string getProjectAt(size_t index) {
        
        if(index > projects.size()) {
            throw std::out_of_range("There is no such project");
        }
        return projects[index];
    }
    /*  
        A function that reads data into helping structures
        Creates collection of workers, unique projects and sectors
    */
    int readData(std::string filename);

    void printData();
};

#endif