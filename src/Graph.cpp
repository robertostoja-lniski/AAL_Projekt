#include "../include/Graph.hpp"
void Graph::makeOneDirectionalConnectionBetween(int a, int b){

        graphRepresentation[a].push_back(b); 
}

std::vector< int >* Graph::getRepresentation()  {
        return graphRepresentation;
}

size_t Graph::getSize() {
    return graphSize;
}

size_t Graph::getLimit() {
    return limit;
}

void Graph::generateGraph(DataStorage dataStorage) {
    // 2 is added because graph has to have starting and ending vertexes
    graphSize = dataStorage.getWorkersNum() +  dataStorage.getSectorsNum() + dataStorage.getProjectsNum() + 2;
    // [begin][sectors][workers][projects][end]
    graphRepresentation = new std::vector< int >[graphSize];
    this->limit = dataStorage.getLimit();

    //from starting point, there will be connection to every project
    int sectorId = 0;
    while(sectorId < dataStorage.getSectorsNum()) {
        makeOneDirectionalConnectionBetween( 0, sectorId + 1);
        sectorId++;
    }

    //every worker will be connected to his sector
    //and to projects that he takes part in
    int workerId = 0;
    while(workerId < dataStorage.getWorkersNum()) {

        //get worker with given id and found id of sector he is in    
        auto worker = dataStorage.getWorkerAt( workerId );
        auto sectorName = worker.getSector();
        int sectorId = dataStorage.getSectorId( sectorName );

        //[begin][sector][workerId]...
        int workerName = workerId + 1 + dataStorage.getSectorsNum();
        makeOneDirectionalConnectionBetween(sectorId + 1, workerName);

        //now for a worker, there will be a connection 
        //with every of his projects
        auto projectCollection = worker.getProjects();
        for( auto project : projectCollection) {
            
            int projectId = dataStorage.getProjectId( project );
            //[begin][sector][worker][projectId]...
            int projectOffset = projectId + 1 + dataStorage.getSectorsNum() + dataStorage.getWorkersNum();
            
            makeOneDirectionalConnectionBetween(workerName, projectOffset);

        }
        workerId++;
    }

    int projectId = 0;
    //every project will be connected with end
    while(projectId < dataStorage.getProjectsNum()) {
        int projectOffset = projectId + 1 + dataStorage.getSectorsNum() + dataStorage.getWorkersNum();
        makeOneDirectionalConnectionBetween( projectOffset, graphSize - 1);
        projectId++;
    }

}

void Graph::print() {
    
    std::cout << "\n";
    for(int i = 0; i < graphSize; i++) {

        std::cout << i << " ";  
        if( i < 10 ) {
            std::cout << " ";
        }
    
        for (int j = 0; j < graphRepresentation[i].size(); j++) {
            
            int edgeLen = ( i == 0 ? limit : 1 );
            std::cout << graphRepresentation[i][j] << "( " << edgeLen << " ) ";
        }
        std::cout << "\n";
    }
}

