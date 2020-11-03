#include "Graph.h"
//------------------------------------------------------------------------------
Graph::Graph(int V){
    this->V = V;
    this->adj = new std::vector<int>[V];
    for (int i = 0; i < this->V; i++) {
        this->white.insert(i);
    }
}

Graph::~Graph(){
    delete [] adj;
}

void Graph::addEdge(int v,int w){
    adj[v].push_back(w);
}

bool Graph::isCyclic(int v) {
    white.erase(v);
    grey.insert(v); 
    int size = (int) adj[v].size();
    for (int i = 0; i < size; ++i) {
        if (white.find(adj[v][i]) != white.end()) {
            isCyclic(adj[v][i]);
        }
        if (grey.find(adj[v][i]) != grey.end()) {
            return true;
        }
    } 
    black.insert(v);
    grey.erase(v);
    return false;
}

bool Graph::unusedInstruction(){
    if (white.empty()){
        return false;
    }
    return true;
}
