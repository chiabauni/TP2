#ifndef PROCESSEDFILES_H
#define PROCESSEDFILES_H
#include <mutex>
#include <vector>
#include <string>
#include "Lock.h"
#define CYCLIC 1
#define INSTR 2
#define GOOD 3
//------------------------------------------------------------------------------
class ProcessedFilesProtected {
    private:
        std::mutex m;
        /* Vector con los resultados de cada ejecuccion de los hilos. */        
        std::vector<std::string> results;

    public: 
    	/* Constructor */
        ProcessedFilesProtected();

        /* Destructor */
        ~ProcessedFilesProtected();

        /* Recibe un numero segun cual fue el resultado(constantes CYCLIC,
        INSTR, GOOD) y el nombre del archivo que obtuvo ese resultado. 
        Guarda en el vector de resultados un string con el nombre del archivo 
        y la frase que se deba imprimir segun cual sea el resultado.*/
        void addResult(int threadResult, std::string& fileName);
        
        /* Devuelve el vector con los resultados. */
        std::vector<std::string> getResult();
};
#endif
