#include "ProcessedFiles.h"
//------------------------------------------------------------------------------
ProcessedFilesProtected::ProcessedFilesProtected(){}

ProcessedFilesProtected::~ProcessedFilesProtected() {}

void ProcessedFilesProtected::addResult(int threadResult, 
										std::string& fileName) {
	Lock l(m);
	if(threadResult == CYCLIC) {
		std::string s0(" FAIL: cycle detected\n"); 
		fileName += s0;
	} else if (threadResult == INSTR) {
		std::string s1(" FAIL: unused instructions detected\n");
		fileName += s1;
	} else if (threadResult == GOOD) {
		std::string s2(" GOOD\n");
		fileName += s2;
	}
	std::vector<std::string>::iterator it;
	it = this->results.end();
	it = this->results.insert(it, fileName);
}

std::vector<std::string> ProcessedFilesProtected::getResult() {
	Lock l(m);
	return this->results;
}
