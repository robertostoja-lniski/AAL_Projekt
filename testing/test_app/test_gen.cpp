#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <set>

#define TEST_NUM 250
#define WORKER_NUM 14
#define PROJECT_NUM 10
#define SECTOR_NUM 6 
#define VERBOSE 0

#define RAPORT_FILE "../visualisation/raport.csv"
void generateTestWithRapport(std::string testName, std::string raportName) {

    std::ofstream testFile;
    std::ofstream raportFile;

    testFile.open (testName); 
    raportFile.open (raportName, std::ios::app);
        
    size_t edge_number = 0;
    std::set<std::string> vertexes;
    std::set<std::string> uniqueProjects;

    std::random_device rd{};
    std::mt19937 gen{rd()};

    // number of workers
    std::uniform_int_distribution<> w{1, WORKER_NUM};
    int workers = w(gen);

    // number of projects
    std::uniform_int_distribution<> p{1, PROJECT_NUM};
    int projects = p(gen);

    // number of sectors
    std::uniform_int_distribution<> s{1, SECTOR_NUM};
    int sectors = s(gen);

    for( int worker = 0; worker < workers; worker++) {

        // create a worker
        std::string workerName = "Worker" + std::to_string(worker);
        edge_number++;
        vertexes.insert(workerName);
#if(VERBOSE)        
        std::cout << workerName << " ";
#endif        
        testFile << workerName << " ";
        
        // assign a sector
        std::uniform_int_distribution<> sectorGen{1, sectors};
        int sectorExample = sectorGen(gen);
        std::string sectorName = "Sector" + std::to_string(sectorExample);
        edge_number++;
        vertexes.insert(sectorName);
#if(VERBOSE)        
        std::cout << sectorName << " ";
#endif        
        testFile << sectorName << " ";

        // choose projects for this worker
        std::uniform_int_distribution<> projectsGen{1, projects};
        int projectsNum = projectsGen(gen);

        std::set<int> projectSet;

        for(int projectForWorker = 0; projectForWorker < projectsNum; projectForWorker++) {

            std::uniform_int_distribution<> setFill{1, projectsNum};
            int newProject = setFill(gen);
            projectSet.insert(newProject);
            
        }

        for( auto item : projectSet ) {
            std::string projectName = "P" + std::to_string(item);
#if(VERBOSE)            
            std::cout << projectName  << " ";
#endif            
            testFile << projectName << " ";
            edge_number++;
            vertexes.insert(projectName);
            uniqueProjects.insert(projectName);
        }
#if(VERBOSE)        
        std::cout << "\n";
#endif        
        testFile << "\n";
    }
    // +2 is for adding s and t
    size_t E = edge_number + uniqueProjects.size();
    size_t V = edge_number + vertexes.size() + 2;

#if(VERBOSE)
    std::cout << "Edges: " << E << " Vertexes: " << V << "\n";
    std::cout << "Expected runtime ( in operations count ) is ( in the worst case ): " << V * E * E << "\n";
#endif

    raportFile << V * E * E << "\n";
    //cleanup
    vertexes.clear();
    uniqueProjects.clear();

    testFile.close();
    raportFile.close();
}
int main(int argc, char const *argv[])
{   
    
    std::ofstream ofs;
    ofs.open(RAPORT_FILE, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    
    for(int i = 0; i < TEST_NUM; i++ ) {

        std::string testFileName = "test" + std::to_string( i ) + ".txt";
        generateTestWithRapport(testFileName, RAPORT_FILE);
    }
    return 0;
}
