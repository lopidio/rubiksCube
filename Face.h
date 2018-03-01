#ifndef FACE_H
#define FACE_H

#include "Cubiculo.h"

class Face
{
        public:
                Face();
                Face(eFaceNome, Cubiculo*[3][3][3]);
                virtual ~Face();

                void rotaciona(eSentidoRotacao,bool animado = true, double = M_PI_2);
                void capturarRespectivosCubiculos(Cubiculo*[3][3][3]);
                bool estaCompleta() const;
                const Color& getColorDoCubiculoCentral() const;
                bool contemCubiculo(const Cubiculo*) const;
                const Cubiculo* getCubiculo(int a, int b) const;
                eFaceNome getLadoDaFace() const;
        protected:
        private:
                const eFaceNome ladoDaFace;
                Cubiculo* cubiculo[3][3]; //Matriz 2d de ponteiros para ponteiros
        private:
                void capturarCubiculosCima(Cubiculo*[3][3][3]);
                void capturarCubiculosBaixo(Cubiculo*[3][3][3]);
                void capturarCubiculosFrente(Cubiculo*[3][3][3]);
                void capturarCubiculosTras(Cubiculo*[3][3][3]);
                void capturarCubiculosEsquerda(Cubiculo*[3][3][3]);
                void capturarCubiculosDireita(Cubiculo*[3][3][3]);
};

#endif // FACE_H
