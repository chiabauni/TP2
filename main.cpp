#include <map>
#include <string>
#include <cstdlib>
#include <iostream>
#include "Reader.h"
#include "Thread.h"
//------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
	std::vector<std::string> filesToProcess;
	for (int i = 2; i <argc ; i++) {
		filesToProcess.push_back(argv[i]);
	}
	int N = std::atoi(argv[1]);
	FilesToProcessProtected files(filesToProcess);
	ProcessedFilesProtected results;
	std::vector<Thread*> threads;

	for (int i = 0; i < N; ++i) {
        threads.push_back(new Reader(files, results));
    }
    
    for (int i = 0; i < N; ++i) {
        threads[i]->start();
    }

    for (int i = 0; i < N; ++i) {
        threads[i]->join();
        delete threads[i];
    }
    
    std::vector<std::string> result = results.getResult();
    std::sort(result.begin(), result.end());
    std::vector<std::string>::iterator it;
    for (it = result.begin(); it != result.end(); it++) {
    	std::cout << *it;
    }
    return 0;
}
