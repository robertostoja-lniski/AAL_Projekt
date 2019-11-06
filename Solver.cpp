#include "Solver.hpp"
void Solver::decryptResults(DataStorage dataStorage) {
    
    for( auto result : algorithmResults ) {

        int workerId = result.getWorker() - dataStorage.getSectorsNum() - 1;
        int projectId = result.getProject() - dataStorage.getSectorsNum() - dataStorage.getWorkersNum() - 1;

        auto workerName = dataStorage.getWorkerAt( workerId ).getName();
        auto project_name = dataStorage.getProjectAt( projectId );

        std::cout << workerName << " " << project_name << "\n";
    }
}

bool Solver::bfs(std::vector< Connection >* graph, int s, int t, VertexParent parents[], size_t graphSize) 
{ 

    bool visited[graphSize]; 
    memset(visited, 0, sizeof(visited)); 

    std::queue <int> q; 
    q.push(s); 
    visited[s] = true; 
    parents[s].setParentId( -1 ); 


    while (!q.empty()) 
    { 
        int u = q.front(); 
        q.pop(); 

        for (int v=0; v<graph[u].size(); v++) 
        { 
            int vertex = graph[u][v].getVertexId();
            if (visited[vertex]==false && graph[u][v].getEdgeLen() > 0) 
            { 
                q.push(vertex); 
                parents[vertex].setParentId( u );
                parents[vertex].setIndexInCollection( v ); 
                visited[vertex] = true; 
            } 
        } 
    } 

    int projectId = parents[t].getParentId();
    int workerId = parents[projectId].getParentId();
    int sectorId = parents[workerId].getParentId();

    if(visited[t]) {

        Path result(projectId, workerId, sectorId);
        algorithmResults.push_back(result);
    }

    return visited[t]; 
} 
/*  
    simple algorithm that checks maximum flow in graph.
    The aim is to have the flow of projects num.

    It is modified to work on optimised data structures
*/
int Solver::fordFulkerson(std::vector< int >* graphRepresentation, size_t graphSize, size_t limit) 
{ 
    int u, v; 
    std::vector< Connection >* residualGraph;  
    residualGraph = new std::vector< Connection >[graphSize];

    for (u = 0; u < graphSize; u++) {

        for (v = 0; v < graphRepresentation[u].size(); v++) {
            
            int edgeLen = ( u == 0 ? limit : 1 );
            Connection residual_connection(graphRepresentation[u][v], edgeLen);
            Connection residual_reverse_connection(u, 0);
            
            int reverse_vertexId = graphRepresentation[u][v];

            residualGraph[u].push_back(residual_connection);
            residualGraph[reverse_vertexId].push_back(residual_reverse_connection);
            
        } 
    }
    VertexParent parents[graphSize];
  
    int maxFlow = 0;

    while (bfs(residualGraph, 0, graphSize - 1, parents, graphSize)) 
    { 
        int pathFLow = INT_MAX; 

        v = graphSize - 1;
        while(parents[v].getParentId() != -1) {

            u = parents[v].getParentId();
            int index = parents[v].getIndexInCollection();
           
            pathFLow = std::min(pathFLow, residualGraph[u][index].getEdgeLen());
            
            v = u;
        }
     
        v = graphSize - 1;
        while(parents[v].getParentId() != -1) { 

            u = parents[v].getParentId(); 
            int index = parents[v].getIndexInCollection();

            // for better performance index in parent collection is saved
            residualGraph[u][index].addToEdgeLen( -pathFLow );
            
            for(int i = 0; i < residualGraph[v].size(); i++) {

                if(residualGraph[v][i].getVertexId() == u) {
                    residualGraph[v][i].addToEdgeLen( pathFLow );
                }
            }

            v = u;
        }

        maxFlow += pathFLow;
    }
    return maxFlow; 
}
  
