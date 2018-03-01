#ifndef QUINASINFERIORESTADO_H
#define QUINASINFERIORESTADO_H

#include "EstadoAlgoritmo.h"
#include <list>

using namespace std;

class QuinasInferiorEstado: public EstadoAlgoritmo
{
        public:
                QuinasInferiorEstado(const Color& cor_, AAlgoritmo* algoritmo);
                virtual ~QuinasInferiorEstado();
                virtual void atualiza();
        protected:
        private:
                void moverBaixoParaLado();
                void moverCimaParaLado();
                void moverLadoInferiorParaLadoSuperior();
                void construirLista();
                void botarNaPosicaoCorreta();
                void iterar();

                list<const Cubiculo*> cubiculos;
                list<const Cubiculo*>::const_iterator iterator;
                const Color& cor;
                bool marcadoParaIteracao;
//                bool faciculaCorCorretaJaEstaDeLado;
};

#endif // QUINASINFERIORESTADO_H
