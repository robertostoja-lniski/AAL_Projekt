#include "Solver.hpp"
void Solver::decryptResults(DataStorage data_storage) {
    
    for( auto result : algorithmResults ) {

        int workerId = result.getWorker() - data_storage.getSectorsNum() - 1;
        int projectId = result.getProject() - data_storage.getSectorsNum() - data_storage.getWorkersNum() - 1;

        auto worker_name = data_storage.getWorkerAt( workerId ).getName();
        auto project_name = data_storage.getProjectAt( projectId );

        std::cout << worker_name << " " << project_name << "\n";
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
int Solver::fordFulkerson(std::vector< Connection >* graphRepresentation, size_t graphSize) 
{ 
    int u, v; 
    std::vector< Connection >* residual_graph;  
    residual_graph = new std::vector< Connection >[graphSize];

    for (u = 0; u < graphSize; u++) {

        for (v = 0; v < graphRepresentation[u].size(); v++) {
            
            Connection residual_connection(graphRepresentation[u][v].getVertexId(), graphRepresentation[u][v].getEdgeLen());
            Connection residual_reverse_connection(u, 0);
            
            int reverse_vertexId = graphRepresentation[u][v].getVertexId();

            residual_graph[u].push_back(residual_connection);
            residual_graph[reverse_vertexId].push_back(residual_reverse_connection);
            
        } 
    }
    VertexParent parents[graphSize];
  
    int max_flow = 0;

    while (bfs(residual_graph, 0, graphSize - 1, parents, graphSize)) 
    { 
        int path_flow = INT_MAX; 

        v = graphSize - 1;
        while(parents[v].getParentId() != -1) {

            u = parents[v].getParentId();
            int index = parents[v].getIndexInCollection();
           
            path_flow = std::min(path_flow, residual_graph[u][index].getEdgeLen());
            
            v = u;
        }
     
        v = graphSize - 1;
        while(parents[v].getParentId() != -1) { 

            u = parents[v].getParentId(); 
            int index = parents[v].getIndexInCollection();

            // for better performance index in parent collection is saved
            residual_graph[u][index].addToEdgeLen( -path_flow );
            
            for(int i = 0; i < residual_graph[v].size(); i++) {

                if(residual_graph[v][i].getVertexId() == u) {
                    residual_graph[v][i].addToEdgeLen( path_flow );
                }
            }

            v = u;
        }

        max_flow += path_flow;
    }
    return max_flow; 
}
  
