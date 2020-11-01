#include <map>
#include "Graph.h"
#include "Reader.h"



int main(int argc, char *argv[]) {
	//File f("all_addr_modes.bpf","rt");
	//std::fstream file;
	//std::vector<std::string> filenames (argc);
	//for (int i = 1; i <argc ; i++) {
		//vector[i] = argv[i];
	//}
	Reader reader;
	int current_node = 0;
	current_node = reader.findLabels(argv[1], current_node);
	int V= current_node;
	Graph G(V);
	int result = reader.parseText(G, argv[1]);
	if(result == CYCLIC) {
		std::cout << "FAIL: cycle detected"<< '\n'; 
	} else if (result == INSTR) {
		std::cout << "FAIL: unused instruction detected"<< '\n';
	} else if (result == GOOD) {
		std::cout << "GOOD"<< '\n';
	}
	return 0;
}
