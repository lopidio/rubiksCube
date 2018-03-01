#ifndef ESTADOALGORITMO_H
#define ESTADOALGORITMO_H

#include "AAlgoritmo.h"

class AAlgoritmo;

class EstadoAlgoritmo
{
        public:
                EstadoAlgoritmo(AAlgoritmo* algoritmo_);
                virtual ~EstadoAlgoritmo();
                virtual void atualiza() = 0;
        protected:
                AAlgoritmo* algoritmo;
        private:
};

#endif // ESTADOALGORITMO_H
