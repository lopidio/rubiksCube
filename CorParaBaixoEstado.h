#ifndef CORPARABAIXOESTADO_H
#define CORPARABAIXOESTADO_H

#include "EstadoAlgoritmo.h"

//Movo a face inicial do algoritmo para baixo
class CorParaBaixoEstado: public EstadoAlgoritmo
{
        public:
                CorParaBaixoEstado(const Color& cor, AAlgoritmo*);
                virtual ~CorParaBaixoEstado();
                virtual void atualiza();
        protected:
        private:
                const Color& cor;
};

#endif // CORPARABAIXOESTADO_H
