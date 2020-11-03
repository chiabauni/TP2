#include "FilesToProcess.h"
//------------------------------------------------------------------------------
FilesToProcessProtected::FilesToProcessProtected(std::vector<std::string>& 
						filesToProcess) : filesToProcess(filesToProcess) {}

FilesToProcessProtected::~FilesToProcessProtected() {}

bool FilesToProcessProtected::getFileNameIfEmpty(std::string& fileName){
	Lock l(m);
	if (filesToProcess.empty()){
		return false;
	}
	std::vector<std::string>::iterator it = filesToProcess.begin();
	fileName = *it;
	filesToProcess.erase(filesToProcess.begin());
	return true;
}

