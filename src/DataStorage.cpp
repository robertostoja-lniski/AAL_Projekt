#include "../include/DataStorage.hpp"
void DataStorage::makeUnique(std::vector< std::string > &vec) {

    std::sort(vec.begin(), vec.end());
    auto last = std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
}

int DataStorage::readData(std::string filename){

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
            worker.addProject(project);
            projects.push_back(project);
        }

        workers.push_back(worker);
        count++;
    }

    makeUnique(sectors);
    makeUnique(projects);

    return 0;
}

void DataStorage::printData() {

    std::cout << "Pracownicy:" << std::endl;
    for( auto worker : workers ) {
        std::cout << worker.getName() << " ma projekty ";

        for( auto project : worker.getProjects() ) {
            std::cout << project << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\n";
}
