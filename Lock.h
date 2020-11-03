#ifndef LOCK_H
#define LOCK_H
#include <mutex>
//------------------------------------------------------------------------------
class Lock {
    private:
        std::mutex &m;

    public:
        /* Constructor */
        explicit Lock(std::mutex &m);
        
        /* Destructor */
        ~Lock();

    private:
        /* Deshabilito el contructor por copia y su operador. */
        Lock(const Lock&) = delete;
        Lock& operator=(const Lock&) = delete;
        
        /* Deshabilito el constructor por movimiento y su operador.*/
        Lock(Lock&&) = delete;
        Lock& operator=(Lock&&) = delete;
};
#endif
