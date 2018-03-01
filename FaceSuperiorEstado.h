#ifndef FACESUPERIORESTADO_H
#define FACESUPERIORESTADO_H

#include "EstadoAlgoritmo.h"
#include <vector>

using namespace std;

class FaceSuperiorEstado: public EstadoAlgoritmo
{
        public:
                FaceSuperiorEstado(AAlgoritmo*);
                virtual ~FaceSuperiorEstado();
                virtual void atualiza();
        protected:
        private:
                void numCubiculosNaoPosicionados();
                void escolherEntreEstados345();
                void escolherEntreEstados12();
                void escolherEntreEstados67();
                void sentidoHorarioAlgoritmo();
                void sentidoAntihorarioAlgoritmo();
                vector<const Cubiculo*> cubiculos;
                vector<const Cubiculo*> cubiculosErrados;
};

#endif // FACESUPERIORESTADO_H
