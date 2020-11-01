#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <set>
#include <iostream>
#include <vector>

class Graph{
    int V; //Numero de vertices
    std::vector<int> *adj; //arreglo de listas de adyacencia
    bool *visit;
    std::set<int> white;
    std::set<int> grey;
    std::set<int> black;
public:
        Graph(int V); //Constructor
        ~Graph();
        void addEdge(int v,int w); //GRAFO Dirigido de v -> w
        bool isCyclic(int v);
        bool DFS(int v);
};
#endif
