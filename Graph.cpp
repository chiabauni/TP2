#include "Graph.h"

Graph::Graph(int V){
    this->V = V;
    this->adj = new std::vector<int>[V];
    this->visit = new bool[V];
    for(int i=0;i<this->V;i++) {
        this->visit[i] = false;
        this->white.insert(i);
    }
}

Graph::~Graph(){
    delete [] adj;
    delete [] visit;
}

void Graph::addEdge(int v,int w){
    adj[v].push_back(w); //agrega w a la posicion v
}

bool Graph::isCyclic(int v) {
    white.erase(v);
    grey.insert(v); 
    for(int i = 0; i < adj[v].size(); ++i) {
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

bool Graph::DFS(int v){
    if (white.empty()){
        return false;
    }
    for (std::set<int>::iterator it = white.begin(); it!=white.end();++it){
        std::cout << "Contenido white" << *it << '\n';
    }
    return true;
}