#ifndef FILESTOPROCESS_H
#define FILESTOPROCESS_H
#include <mutex>
#include <vector>
#include <string>
#include "Lock.h"
//------------------------------------------------------------------------------
class FilesToProcessProtected {
    private:
        std::mutex m;
        /* Vector con los nombres de los archivos. */        
        std::vector<std::string> filesToProcess;
    public:
    	/* Constructor */
        explicit FilesToProcessProtected(std::vector<std::string>& 
        									filesToProcess);

        /* Destructor */
        ~FilesToProcessProtected();
        
        /* Obtiene el nombre de un archivo del vector, lo borra 
        de la lista y devuelve false si la lista esta vacia y true
        si no lo esta. */
        bool getFileNameIfEmpty(std::string& fileName); 
};
#endif
