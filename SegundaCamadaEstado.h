#ifndef SEGUNDACAMADAESTADO_H
#define SEGUNDACAMADAESTADO_H

#include "EstadoAlgoritmo.h"
#include <list>

using namespace std;

class SegundaCamadaEstado:  public EstadoAlgoritmo
{
        public:
                SegundaCamadaEstado(AAlgoritmo* algoritmo);
                virtual ~SegundaCamadaEstado();
                virtual void atualiza();
        protected:
        private:
                void construirLista();
                void iterarOuMudarEstado();
                void subirCubiculo();
                void descerCubiculo();

                int numCubiculosAjeitados;
                list<const Cubiculo*> cubiculos;
                list<const Cubiculo*>::iterator cubiculo;
};

#endif // SEGUNDACAMADAESTADO_H
