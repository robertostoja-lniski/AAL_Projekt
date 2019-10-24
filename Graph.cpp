#include "Graph.hpp"
void Graph::make_one_direction_connection_between(int a, int b, int val){

        Connection to_b(b, val);
        graph_representation[a].push_back(to_b); 
}
void Graph::decryptResults(DataStorage data_storage) {
    
    for( auto result : algorithm_results ) {

        int worker_id = result.getWorker() - data_storage.getSectorsNum() - 1;
        int project_id = result.getProject() - data_storage.getSectorsNum() - data_storage.getWorkersNum() - 1;

        auto worker_name = data_storage.getWorkerAt( worker_id ).getName();
        auto project_name = data_storage.getProjectAt( project_id );

        std::cout << worker_name << " " << project_name << "\n";
    }
}

void Graph::generate_graph(DataStorage data_storage) {
    // 2 is added because graph has to have starting and ending vertexes
    graph_size = data_storage.getWorkersNum() +  data_storage.getSectorsNum() + data_storage.getProjectsNum() + 2;
    // [begin][sectors][workers][projects][end]
    graph_representation = new std::vector< Connection >[graph_size];
    int limit = data_storage.getLimit();

    //from starting point, there will be connection to every project
    int sector_id = 0;
    while(sector_id < data_storage.getProjectsNum()) {
        make_one_direction_connection_between( 0, sector_id + 1, limit);
        sector_id++;
    }

    //every worker will be connected to his sector
    //and to projects that he takes part in
    int worker_id = 0;
    while(worker_id < data_storage.getWorkersNum()) {

        //get worker with given id and found id of sector he is in    
        auto worker = data_storage.getWorkerAt( worker_id );
        auto sector_name = worker.getSector();
        int sector_id = data_storage.getSectorId( sector_name );

        //[begin][sector][worker_id]...
        int worker_offset = worker_id + 1 + data_storage.getSectorsNum();
        make_one_direction_connection_between(sector_id + 1, worker_offset, 1);

        //now for a worker, there will be a connection 
        //with every of his projects
        auto project_collection = worker.getProjects();
        for( auto project : project_collection) {
            
            int project_id = data_storage.getProjectId( project );
            //[begin][sector][worker][project_id]...
            int project_offset = project_id + 1 + data_storage.getSectorsNum() + data_storage.getWorkersNum();
            
            make_one_direction_connection_between(worker_offset, project_offset, 1);

        }
        worker_id++;
    }

    int project_id = 0;
    //every project will be connected with end
    while(project_id < data_storage.getProjectsNum()) {
        int project_offset = project_id + 1 + data_storage.getSectorsNum() + data_storage.getWorkersNum();
        make_one_direction_connection_between( project_offset, graph_size - 1, 1);
        project_id++;
    }

}

void Graph::print() {
    
    std::cout << "\n";
    for(int i = 0; i < graph_size; i++) {

        std::cout << i << " ";  
        if( i < 10 ) {
            std::cout << " ";
        }
    
        for (int j = 0; j < graph_representation[i].size(); j++) {
        
            std::cout << graph_representation[i][j].getVertexId() << "( " << graph_representation[i][j].getEdgeLen() << " ) ";
        }
        std::cout << "\n";
    }
}

bool Graph::bfs(std::vector< Connection >* graph, int s, int t, VertexParent parents[]) 
{ 

    bool visited[graph_size]; 
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

    int project_id = parents[t].getParentId();
    int worker_id = parents[project_id].getParentId();
    int sector_id = parents[worker_id].getParentId();

    if(visited[t]) {

        Path result(project_id, worker_id, sector_id);
        algorithm_results.push_back(result);
    }

    return visited[t]; 
} 
/*  
    simple algorithm that checks maximum flow in graph.
    The aim is to have the flow of projects num.

    It is modified to work on optimised data structures
*/
int Graph::fordFulkerson() 
{ 
    int u, v; 
    std::vector< Connection >* residual_graph;  
    residual_graph = new std::vector< Connection >[graph_size];

    for (u = 0; u < graph_size; u++) {

        for (v = 0; v < graph_representation[u].size(); v++) {
            
            Connection residual_connection(graph_representation[u][v].getVertexId(), graph_representation[u][v].getEdgeLen());
            Connection residual_reverse_connection(u, 0);
            
            int reverse_vertex_id = graph_representation[u][v].getVertexId();

            residual_graph[u].push_back(residual_connection);
            residual_graph[reverse_vertex_id].push_back(residual_reverse_connection);
            
        } 
    }
    VertexParent parents[graph_size];
  
    int max_flow = 0;

    while (bfs(residual_graph, 0, graph_size - 1, parents)) 
    { 
        int path_flow = INT_MAX; 

        v = graph_size - 1;
        while(parents[v].getParentId() != -1) {

            u = parents[v].getParentId();
            int index = parents[v].getIndexInCollection();
           
            path_flow = std::min(path_flow, residual_graph[u][index].getEdgeLen());
            
            v = u;
        }
     
        v = graph_size - 1;
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
  