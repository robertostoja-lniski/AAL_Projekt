#ifndef WORKER_HPP
#define WORKER_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Worker{

    private:

        std::vector< std::string > projects;
        std::string name;
        std::string sector;
        bool assigned = false;
        bool problematic = false;

    public:

        Worker(std::string name, std::string sector) :
            name(name), sector(sector) {}

        void add_project(std::string project) {
            projects.push_back(project);
        }

        void sort_project_list() {
            std::sort(projects.begin(), projects.end());
        }

        std::string getSector() {
            return sector;
        }

        void assign() {
            assigned = true;
        }

        void unassign() {
            assigned = false;
        }
        
        void becomeProblematic() {
            problematic = true; 
        }

        bool isProblematic() {
            return problematic;
        }

        bool isAssigned() {
            return assigned;
        }

        std::string getName() {
            return name;
        }

        int isInProject(std::string project) {
            return std::find(projects.begin(), projects.end(), project) != projects.end();
        }

        friend std::ostream& operator<<(std::ostream& os, const Worker& dt);
};

std::ostream& operator<<(std::ostream& os, const Worker& worker)
{
    os << worker.name << " " << worker.sector << " ";

    for(auto project : worker.projects) {
        os << project << " ";
    }
    
    return os;
}
#endif