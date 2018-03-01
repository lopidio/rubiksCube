#ifndef CRUZINFERIORESTADO_H
#define CRUZINFERIORESTADO_H

#include "EstadoAlgoritmo.h"

//Crio uma cruz na cor que t� embaixo!
class CruzInferiorEstado: public EstadoAlgoritmo
{
        public:
                CruzInferiorEstado(const Color& cor_, AAlgoritmo*);
                virtual ~CruzInferiorEstado();
                virtual void atualiza();
        protected:
        private:
                void minhaCorEmCima(eFaceNome outraFace);
                void minhaCorEmbaixo(eFaceNome outraFace);
                void minhaCorAtras(eFaceNome outraFace);
                void minhaCorNaFrente(eFaceNome outraFace);
                void minhaCorNaEsquerda(eFaceNome outraFace);
                void minhaCorNaDireita(eFaceNome outraFace);

                void iterarFace();
                eFaceNome faceDaCorDoProximoCubiculo; //Pr�xima face que vou montar
                const Color& cor; //Cor que ser� resolvida
                bool parteCruzResolvida[6]; //Quais faces da cruz j� t�o montadas
};

#endif // CRUZINFERIORESTADO_H
