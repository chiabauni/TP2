#ifndef READER_H
#define READER_H
#include <map>
#include <string>
#include <fstream>
//#include <sstream>
#include <algorithm>
#include <iostream>
#include "Graph.h"
#define CYCLIC 1
#define INSTR 2
#define GOOD 3

class Reader{
	std::map<std::string,int> dic;
    int fillDictionnary(std::fstream& file, int current_node);
    void findJumpLabels(Graph& G, std::string line, int current_node);
    void findRetAndJumpLabels(Graph& G, std::fstream& file);

public:
        Reader(); 
        ~Reader();
        int findLabels(std::string file_name, int current_node);
        int parseText(Graph& G, std::string file_name);
};
#endif
