#ifndef CUBO_H
#define CUBO_H

#include "Cubiculo.h"
#include "Desenhavel.h"
#include "Face.h"
#include "ICuboObserver.h"
#include "AAlgoritmo.h"

#include <list>

using namespace std;

class ICuboObserver; //Forward declaration
class AAlgoritmo;

class Cubo: public Desenhavel
{
        public: //Rotações
                struct Rotacao
                {
                        void criarAleatoriamente();
                        bool animado;
                        bool rotacaoFace; //Pode ser do cubo todo!
                        union
                        {
                                eFaceNome face;
                                eEixoRotacao eixo;
                        };
                        eSentidoRotacao sentido;
                };
                bool filaRotacoesVazia() const;
                bool estaRotacionando() const;
                void addRotacaoTodo(const Rotacao&, double alfa = M_PI_2);
                void addRotacaoFace(const Rotacao&, double alfa = M_PI_2);
                void reordenarCubiculos(); //Rearranja os ponteiros das faces e dos cubículos
        private:
                void verificaNotificacoes(); //Informa aos observers
                void verificaNecessidadeDeRotacao(); //Verifica se ainda há rotação na fila
                void executarRotacaoTodo(const Rotacao&);
                void executarRotacaoFace(const Rotacao&);
                list<Rotacao> filaRotacoes;

        public:
                Cubo();
                virtual ~Cubo();
                virtual void atualiza(float msecs);

                const Cubiculo* getCubiculoQuinaDeCor(const Color&,const Color&,const Color& ) const;
                const Cubiculo* getCubiculoLadoDeCor(const Color&,const Color&) const;
                const Cubiculo* getCubiculoCentroDeCor(const Color&) const;
                const Cubiculo* getCubiculo(int x, int y, int z) const;
                bool estaCubiculoNaPosicaoCorreta(const Cubiculo*) const;
                const Face* getFace(eFaceNome face) const;
                bool estaResolvido() const;

                //Observer
                void addObserver(ICuboObserver* observer);
                void removeObserver(ICuboObserver* observer);
        protected:
        private: //Estrutura interior
                list<ICuboObserver*> observers;
                Face** faces; //Ponteiro pra ponteiro pq é um vetor, e vamos fazer uma brincadeira pra trocar as posições...

                Cubiculo *cubiculos[3][3][3];
};

#endif // CUBO_H
