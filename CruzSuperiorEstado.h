#ifndef CRUZSUPERIORESTADO_H
#define CRUZSUPERIORESTADO_H

#include "EstadoAlgoritmo.h"

class CruzSuperiorEstado: public EstadoAlgoritmo
{
        public:
                CruzSuperiorEstado(AAlgoritmo*);
                virtual ~CruzSuperiorEstado();
                virtual void atualiza();
        protected:
        private:
        // --  f3 --
        // f1  X  f2
        // --  f0 --
                void doAlgoritmo(); //T E C E' C' T'
                void verificaLOuLinha();
                void LAlgoritmo();

                int numFaciculasCruzParaCima();
                bool faciculasCorretasParaCima[4];
                const Color corCruz;
};

#endif // CRUZSUPERIORESTADO_H
