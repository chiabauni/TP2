#ifndef GRAPH_H
#define GRAPH_H
#include <set>
#include <vector>
//------------------------------------------------------------------------------
class Graph{
    /* Cantidad de vertices. */
    int V;    
    /* Vector de array donde se guarda el grafo. */
    std::vector<int> *adj; 
    /* Container de nodos "con color" blanco. */
    std::set<int> white;    
    /* Container de nodos "con color" gris. */
    std::set<int> grey;   
    /* Container de nodos "con color" negro. */
    std::set<int> black;
    
	public:
		/* Constructor */
		explicit Graph(int V);
        
		/* Destructor */
        ~Graph();

        /* Recibe dos nodos y crea una arista del nodo v
         hacia el nodo w. */
        void addEdge(int v,int w); 
        
        /* Va recibiendo nodos para chequear si el grafo 
        contiene ciclos. Todos los nodos se inicializa en 
        el set blanco, cuando entra a la funcion isCyclic 
        se elimina del set blanco y se inserta en el set gris. 
        Para cada uno de los nodos adjacentes al que se esta procesando 
        se chequea: si esta en el set blanco se corre nuevamenta la 
        funcion isCyclic(), si esta en el set gris devuelve true porque 
        significa que encontro un ciclo. Cuando termina de procesar 
        el nodo lo borra del set gris y lo ubica en el set negro. */
        bool isCyclic(int v);
        
        /* Chequea si quedo algun nodo sin visitar. Si quedo un nodo
        en el set blanco devuelve true, en otro caso devuelve false. */
        bool unusedInstruction();
};
#endif
