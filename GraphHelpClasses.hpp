#ifndef GRAPHHELPCLASSES_HPP
#define GRAPHHELPCLASSES_HPP
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
class VertexParent{

private:

    /*  
        Index in collection is the index in a vector 
        assigned to given vertex. 

        For example:

        if parend_id[B] = A ( parent id was assigned when moving from A to B )
        graph[A][index_in_collection].getValue() = B

        Aim:

        It increases the effectiveness of algorithm when reading path after BFS round.

        Assume that, there is int parent[] instead of VertexParent parent[]

        After running BFS, when we want to check what was the algorithm path knowing
        parent[] array.

        Stepping backwards starting from parent[graph_size - 1] we know only vertexes ids.
        We need to find min flow in the path.
        To check what was the flow between a vertex and its parent we have to:
        
        a) iterate through parent neighbours list
        b) find a child that was chosen by the algorithm
        c) read a flow of edge parent => child

        Using VertexParent speeds up this process.
        Step a) in unnecessary, since we know the exact position in neighbours list
        It gives us O(1) instead of O(n)
    */
    int parent_id = 0;
    int index_in_collection = 0;

public:

    VertexParent() {}

    int getParentId() {
        return parent_id;
    }

    int getIndexInCollection() {
        return index_in_collection;
    }

    void setParentId( int parent_id ) {
        this->parent_id = parent_id;
    }

    void setIndexInCollection(int index_in_collection ) {
        this->index_in_collection = index_in_collection;
    }
};

class Connection{

private:

    
    /*  
        To avoid using N x N matrix that wastes memory graph
        representation of vector tab[] was chosen.

        Since edge value can be ( 1 : m / 2 ), class Connection
        was added to solve the issue of storing egde value.
        
        graph_representation[Connection_A][Connection_B].edge_len
        is equal to length of edge A => B
    */
    int vertex_id;
    int edge_len;

public:
    Connection(int vertex_id, int edge_len) : vertex_id(vertex_id), edge_len(edge_len) {}

    int getVertexId() {
        return vertex_id;
    }
    
    int getEdgeLen(){
        return edge_len;
    }

    int addToEdgeLen(int val) {
        edge_len += val;
    }
};
#endif