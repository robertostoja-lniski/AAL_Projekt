#ifndef GRAPH_HPP
#define GRAPH_HPP

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
#include "DataStorage.hpp"
#include <iostream> 
#include <limits.h> 
#include <string.h> 
#include <queue> 

#define SIZE 12
class Path{

private:

    int project;
    int worker;
    int sector;

public:
    Path(int project, int worker, int sector) :
        project(project), worker(worker), sector(sector) {}

    int getProject() {
        return project;
    }

    int getWorker() {
        return worker;
    }

    int getSector() {
        return sector;
    }

};
class Graph{

private:
    

    unsigned int** graph_representation;
    size_t graph_size = 0;
    std::vector< Path > algorithm_results;

public:
    
    Graph() {}

    void decryptResults(DataStorage data_storage) {
        
        for( auto result : algorithm_results ) {

            int worker_id = result.getWorker() - data_storage.getSectorsNum() - 1;
            int project_id = result.getProject() - data_storage.getSectorsNum() - data_storage.getWorkersNum() - 1;

            auto worker_name = data_storage.getWorkerAt( worker_id ).getName();
            auto project_name = data_storage.getProjectAt( project_id );

            std::cout << worker_name << " " << project_name << "\n";
        }
    }
    void generate_graph(DataStorage data_storage) {
        // 2 is added because graph has to have starting and ending vertexes
        graph_size = data_storage.getWorkersNum() +  data_storage.getSectorsNum() + data_storage.getProjectsNum() + 2;
        // [begin][sectors][workers][projects][end]
        graph_representation = new unsigned int*[graph_size];
        for(int i = 0; i < graph_size; i++) {
            graph_representation[i] = new unsigned int[graph_size];
            memset(graph_representation[i], 0x00, graph_size);
        }
        
        int limit = data_storage.getLimit();
        int project_id = 0;
        while(project_id < data_storage.getProjectsNum()) {

            graph_representation[0][project_id + 1] = limit;
            graph_representation[project_id + 1][0] = limit;
            
            project_id++;
        }

        int worker_id = 0;
        while(worker_id < data_storage.getWorkersNum()) {

            auto worker = data_storage.getWorkerAt( worker_id );
            auto sector_name = worker.getSector();
            int sector_id = data_storage.getSectorId( sector_name );
            int worker_offset = worker_id + 1 + data_storage.getSectorsNum();

            // std::cout << " joining " << sector_name << " " << sector_id + 1 << " with " << worker_id + 1 + data_storage.getSectorsNum() << "\n";
            graph_representation[sector_id + 1][worker_offset] = limit;
            graph_representation[worker_offset][sector_id + 1] = limit;

            auto project_collection = worker.getProjects();
            for( auto project : project_collection) {
                
                int project_id = data_storage.getProjectId( project );
                std::cout << project_id << "\n";
                int project_offset = project_id + 1 + data_storage.getSectorsNum() + data_storage.getWorkersNum();

                graph_representation[worker_offset][project_offset] = 1;
                graph_representation[project_offset][worker_offset] = 1;

                graph_representation[project_offset][graph_size - 1] = 1;
                graph_representation[graph_size - 1][project_offset] = 1;

            }
            worker_id++;
        }
    }

    void print() {
        
        std::cout << "# ";
        for(int i = 0; i < graph_size; i++) {
            
            std::cout << "#" << i;
            if( i < 10 ) {
                std::cout << " ";
            }
        }
        std::cout << "\n";

        for(int i = 0; i < graph_size; i++) {

            std::cout << i << " ";  
            if( i < 10 ) {
                std::cout << " ";
            }

            for (int j = 0; j < graph_size; j++) {

                std::cout << graph_representation[i][j] << "  ";
            }
            std::cout << "\n";
        }
    }


}; 
#endif 