#ifndef AALGORITMO_H
#define AALGORITMO_H

#include "ICuboObserver.h"
#include "EstadoAlgoritmo.h"
#include <queue>

class Cubo;
class EstadoAlgoritmo;

enum eAlgoritmoID
{
        eALGORITMOID_F2L
};

class AAlgoritmo : public ICuboObserver
{
        public:
                virtual ~AAlgoritmo();
                static AAlgoritmo* Fabrica(eAlgoritmoID id, Cubo* cubo); //Fala por si só
                void atualiza(); //Todo mundo sabe o que é

                void  executa(); //Inicia a contagem de tempo, chama o primeiro update
                virtual void primeiroPasso(); //Hook ;)
                static void Embaralhar(Cubo* cubo, bool animado = true);

                //Movimenta o cubo
                void addMovimentoFace(eFaceNome face, eSentidoRotacao sentido);
                void addMovimentoTodo(eEixoRotacao eixo, eSentidoRotacao);

                int getNumPassos() const;
                void setAnimado(bool);
                const Cubo* getCubo() const;

                //Herdadas de ICuboObserver
                virtual void onCuboCompleto();
                virtual void onFimCuboRotacoes(const Cubo*);// (Se sobrecaregadas, chamar o método do pai)

                //Padrão State
                void setEstadoAtual(EstadoAlgoritmo* novoEstado);
        private: //Atributos privados
                Cubo* cubo;
                int numPassos;
        protected:
                AAlgoritmo(); //Default

                virtual void atualizaFilho() = 0;
                EstadoAlgoritmo* estadoAtual;
                bool animado;
};

#endif // AALGORITMO_H
