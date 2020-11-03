#include "Reader.h"
//------------------------------------------------------------------------------
Reader::Reader(FilesToProcessProtected &files, 
	ProcessedFilesProtected &results) : 
	files(files), results(results) {}

Reader::~Reader(){}

void Reader::run() {
	std::string fileName;
	while (this->files.getFileNameIfEmpty(fileName)) {
		int V = findLabels(fileName);
		Graph G(V);
		int result = parseText(G, fileName);
		results.addResult(result, fileName);
	}
}

int Reader::findLabels(std::string& fileName) {
	std::fstream file;
	int current_node = 0;
	file.open(fileName);
	if (file.is_open()){
		while (!file.eof()){
			current_node = fillDictionnary(file);
		}
	}
	file.close();
	return current_node;
}

int Reader::fillDictionnary(std::fstream& file) {
	std::string line;
	int current_node = 0;
	while (std::getline(file, line)) {
		std::string delimiter = ":";
		std::size_t label_found = line.find(delimiter);
		if (line == "") {
			continue;
		} else if (label_found != std::string::npos) {
			std::string label = line.substr(0, label_found);
			this->dic.insert(std::pair<std::string,int>(label, current_node));
		}
		current_node++;
	}
	return current_node;
}

int Reader::parseText(Graph& G, std::string& file_name) {
	std::fstream file;
	file.open(file_name);
	if (file.is_open()){
		while (!file.eof()){
			findRetAndJumpLabels(G, file);
		}
	}
	file.close();
	this->dic.clear();
	if(G.isCyclic(0) || (G.isCyclic(0) && G.unusedInstruction())) {
		return CYCLIC;
	} else if (G.unusedInstruction()) {
		return INSTR;
	}
	return GOOD;
}

void Reader::findRetAndJumpLabels(Graph& G, std::fstream& file) {
	std::string line;
	int current_node = 0;
	while (std::getline(file, line)) {
		std::size_t ret_found = line.find("ret");
		int array_element_found = 0;
		std::array<std::string,10> array = {"jmp","ja","jeq","jneq","jne",
									"jlt","jle","jgt","jge","jset"};
		std::size_t jump_found = 0;
		for (int i = 0; i<10 && array_element_found == 0; i++) {
				jump_found = line.find(array[i]);
			if (jump_found != std::string::npos) {
				array_element_found = 1;
			}
		}
		if (line == "") {
			continue;
		} else if (ret_found != std::string::npos) {
		} else if (jump_found != std::string::npos) {
			findJumpLabels(G, line, current_node);
		} else {
			G.addEdge(current_node, (current_node + 1));
		}
		current_node++;
	}
}

void Reader::findJumpLabels(Graph& G, std::string line, int current_node) {
	std::string::iterator begin = line.begin();
	std::string::iterator end = line.end();
	int n = std::count(begin, end, ',');
	if (n == 1) {
		std::map<std::string,int>::iterator it;
		std::string jmp_arg = line.substr(line.find_last_of(" ")+1);
		it = this->dic.find(jmp_arg);
		G.addEdge(current_node, it->second);
		G.addEdge(current_node, (current_node + 1));
	} else if (n == 2) {
		std::map<std::string,int>::iterator it1;
		std::map<std::string,int>::iterator it2;
		std::string jmp_label0 = line.substr(line.find(",")+2);
		std::string jmp_label1 = jmp_label0.substr(0, jmp_label0.find(","));
		std::string jmp_label2 = line.substr(line.find_last_of(",")+2);
		it1 = this->dic.find(jmp_label1);
		it2 = this->dic.find(jmp_label2);
		G.addEdge(current_node, it1->second);
		G.addEdge(current_node, it2->second);
	} else {
		std::map<std::string,int>::iterator it;
		std::string jmp_label = line.substr(line.find_last_of(" ")+1); 
		it = this->dic.find(jmp_label);
		G.addEdge(current_node, it->second);
	}
}
