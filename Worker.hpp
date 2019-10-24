#ifndef WORKER_HPP
#define WORKER_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

/*  
    Simple class representing a worker
    It contains his name, sector, list of projects 
*/
class Worker{

    private:

        std::vector< std::string > projects;
        std::string name;
        std::string sector;

        bool assigned = false;
        bool problematic = false;

        int id;

    public:

        Worker() {}

        Worker(std::string name, std::string sector, unsigned int id) :
            name(name), sector(sector), id(id) {}

        void add_project(std::string project) {
            projects.push_back(project);
        }

        std::vector< std::string > getProjects() {
            return projects;
        }

        void sort_project_list() {
            std::sort(projects.begin(), projects.end());
        }

        std::string getSector() {
            return sector;
        }

        int getId() {
            return id;
        }    
        
        void assign() {
            assigned = true;
        }

        std::string getName() {
            return name;
        }

        int isInProject(std::string project) {
            return std::find(projects.begin(), projects.end(), project) != projects.end();
        }
};

#endif