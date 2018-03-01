#ifndef CUBICULO_H
#define CUBICULO_H

#include "Quadrado.h"
#include "Desenhavel.h"

#include <vector>
#include <list>

using namespace std;

class Cubiculo: public Desenhavel
{
        public:
                static const float LADO = 1.5f;
                Cubiculo(); //Default
                Cubiculo(const Vector3& centro); //1, 0 ou -1
                virtual ~Cubiculo();
                virtual void atualiza(float msecs);

                void ativarFacicula(eFaceNome);
                void construir();

                const Color& getCorAtravesDaFace(eFaceNome) const;
                eFaceNome getFaceAtravesDaCor(const Color& cor) const;
                bool temCor(const Color&) const;
                const Vector3& getPosicaoNoCubo() const; //O centro dos vértices respondem!
                bool isRotacionando() const;
                void rotacionar(eEixoRotacao, eSentidoRotacao, bool animado, double alfa = M_PI_2);
                float getCentroValorOrdenacao() const;
                int getNumFaciculas() const;
        protected:
        private:
                Vector3 posicaoReal;
                bool rotacionando;
                Vector3 angulo;
                Vector3 anguloAnimacao; //Dá o efeito visual da animação

                list<Quadrado> faces; //Estruturas de conteiners da STL pq haverá remoção
                vector<Vector3> vertices;

                //mapa bidimensional. Aquela cruzinha que vai mostrar todas as faces dos cubículos
        private:
                void fimRotacao();
        private:
                //O atualiza chama esses métodos caso haja necessidade
                void aproximaAngulosX(float);
                void aproximaAngulosY(float);
                void aproximaAngulosZ(float);
                void atualizaVertices(Matriz*);
};

#endif // CUBICULO_H
