#include "Graph.hpp"
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

void Graph::generateGraph(DataStorage data_storage) {
    // 2 is added because graph has to have starting and ending vertexes
    graphSize = data_storage.getWorkersNum() +  data_storage.getSectorsNum() + data_storage.getProjectsNum() + 2;
    // [begin][sectors][workers][projects][end]
    graphRepresentation = new std::vector< int >[graphSize];
    this->limit = data_storage.getLimit();

    //from starting point, there will be connection to every project
    int sectorId = 0;
    while(sectorId < data_storage.getProjectsNum()) {
        makeOneDirectionalConnectionBetween( 0, sectorId + 1);
        sectorId++;
    }

    //every worker will be connected to his sector
    //and to projects that he takes part in
    int workerId = 0;
    while(workerId < data_storage.getWorkersNum()) {

        //get worker with given id and found id of sector he is in    
        auto worker = data_storage.getWorkerAt( workerId );
        auto sector_name = worker.getSector();
        int sectorId = data_storage.getSectorId( sector_name );

        //[begin][sector][workerId]...
        int worker_offset = workerId + 1 + data_storage.getSectorsNum();
        makeOneDirectionalConnectionBetween(sectorId + 1, worker_offset);

        //now for a worker, there will be a connection 
        //with every of his projects
        auto project_collection = worker.getProjects();
        for( auto project : project_collection) {
            
            int projectId = data_storage.getProjectId( project );
            //[begin][sector][worker][projectId]...
            int project_offset = projectId + 1 + data_storage.getSectorsNum() + data_storage.getWorkersNum();
            
            makeOneDirectionalConnectionBetween(worker_offset, project_offset);

        }
        workerId++;
    }

    int projectId = 0;
    //every project will be connected with end
    while(projectId < data_storage.getProjectsNum()) {
        int project_offset = projectId + 1 + data_storage.getSectorsNum() + data_storage.getWorkersNum();
        makeOneDirectionalConnectionBetween( project_offset, graphSize - 1);
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

