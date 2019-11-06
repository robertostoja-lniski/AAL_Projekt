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
        graph[A][indexInCollection].getValue() = B

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
    int parentId = 0;
    int indexInCollection = 0;

public:

    VertexParent() {}

    int getParentId() {
        return parentId;
    }

    int getIndexInCollection() {
        return indexInCollection;
    }

    void setParentId( int parentId ) {
        this->parentId = parentId;
    }

    void setIndexInCollection(int indexInCollection ) {
        this->indexInCollection = indexInCollection;
    }
};

class Connection{

private:

    
    /*  
        To avoid using N x N matrix that wastes memory graph
        representation of vector tab[] was chosen.

        Since edge value can be ( 1 : m / 2 ), class Connection
        was added to solve the issue of storing egde value.
        
        graph_representation[Connection_A][Connection_B].edgeLen
        is equal to length of edge A => B
    */
    int vertexLen;
    int edgeLen;

public:
    Connection(int vertexLen, int edgeLen) : vertexLen(vertexLen), edgeLen(edgeLen) {}

    int getVertexId() {
        return vertexLen;
    }
    
    int getEdgeLen(){
        return edgeLen;
    }

    int addToEdgeLen(int val) {
        edgeLen += val;
    }
};
#endif