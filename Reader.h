#ifndef READER_H
#define READER_H
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <utility>
#include "Graph.h"
#include "Thread.h"
#include "FilesToProcess.h"
#include "ProcessedFiles.h"
#define CYCLIC 1
#define INSTR 2
#define GOOD 3
//------------------------------------------------------------------------------
class Reader : public Thread {
	/* Diccionario en el que se guardan las etiquetas */
	std::map<std::string,int> dic;
	FilesToProcessProtected &files;
	ProcessedFilesProtected &results;
	
	/* Recibe un nombre de archivo, lo abre y llama a 
	la funcion fillDictionnary. Finalmente cierra el archivo
	y devuelve la cantidad de lineas que tiene el archivo */
	int findLabels(std::string& fileName);
	
	/* Recibe un archivo abierto, lo recorre linea por linea 
	y si encuntra una etiqueta la guarda en el diccionario. 
	Siendo su value para cada etiqueta el numero de linea
	(sin contar la lineas vacias). Devuelve la cantidad de
	lineas del archivo. */
	int fillDictionnary(std::fstream& file);
	
	/* Recibe un grafo y un nombre de archivo. Abre el archivo,
	llama a la funcion findRetAndJumpLabels. Cierra el archivo, 
	vacia el diccionario y llama a las funciones isCyclic() 
	y unusedInstruction() que devuelven segun corresponda los
	valores constantes establecidos(CYCLIC, INSTR o GOOD). */
    int parseText(Graph& G, std::string& file_name);

    /* Recibe un grafo y un archivo abierto. Por cada linea 
    no vacia, si encuentra un jump llama a la funcion findJumpLabels,
    si encuntra un ret no hace nada. Si la linea no contiene
    ni jump ni ret, le agrega al grafo una arista que va del numero
    de linea en que se encuentra al siguiete numero de linea. */
    void findRetAndJumpLabels(Graph& G, std::fstream& file);

	/* Recibe un grafo, una linea, y el numero de linea en que 
	se encuentra. Si encuentra una unica coma, se trata del caso 
	en el que hay un argumento y una etiqueta por lo que que se 
	agrega una arista que va de la linea actual a la linea en 
	la que esta la etiqueta y otra arista que va de la linea 
	actual a la siguiente linea. Si encuentran dos comas, se trata 
	del caso en el que hay un argumento y dos etiquetas por lo que que se 
	agrega una arista que va de la linea actual a la linea en 
	la que esta la primera etiqueta y otra arista que va de la linea 
	actual a la linea en la que esta la segunda etiqueta. 
	En otro caso, no se encontro ninguna coma por lo que hay 
	una unica etiqueta y se agrega una aristaque va de la linea actual
	a la siguiente linea. */
    void findJumpLabels(Graph& G, std::string line, int current_node);
	public:
		/* Constructor */
        Reader(FilesToProcessProtected &files, 
        		ProcessedFilesProtected &results); 
        /* Destructor */
        ~Reader();
        /* Codigo que va a ejecutar cada hilo al correr. */
        virtual void run() override;
};
#endif
