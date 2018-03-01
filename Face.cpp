/* *********************************************/
/********************************************  /
//
// @date -
//
// Project -
//
//  if (!bug)
//	@author Lopídio (I love America)
//  else
//	@author Unkwonn
//
//
//  Good Luck!
** *********************************/
/* *******************************/


#include "Face.h"

Face::Face():ladoDaFace(eFACENOME_INEXISTENTE)
{
        //ctor
}

/** @brief Face
  *
  * @todo: document this function
  */
 Face::Face(const eFaceNome ladoDaFace_, Cubiculo* cubiculo_[3][3][3]):ladoDaFace(ladoDaFace_)
{
        //Pego os cubículos que são meus
        capturarRespectivosCubiculos(cubiculo_);

        //Informo aos meus cubículos que ele deverá exibir a face
        for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                        cubiculo[i][j]->ativarFacicula(ladoDaFace);
}

Face::~Face()
{
        //dtor
}

/** @brief capturarRespectivosCubiculos
  *
  * @todo: document this function
  */
void Face::capturarRespectivosCubiculos(Cubiculo* cubiculo_[3][3][3])
{
        //Descubro quais cubiculos pertencem a mim
        switch (ladoDaFace)
        {
                case eFACENOME_CIMA :
                                capturarCubiculosCima(cubiculo_);
                        break;
                case eFACENOME_BAIXO :
                                capturarCubiculosBaixo(cubiculo_);
                        break;
                case eFACENOME_ESQUERDA :
                                capturarCubiculosEsquerda(cubiculo_);
                        break;
                case eFACENOME_DIREITA :
                                capturarCubiculosDireita(cubiculo_);
                        break;
                case eFACENOME_TRAS :
                                capturarCubiculosTras(cubiculo_);
                        break;
                case eFACENOME_FRENTE :
                                capturarCubiculosFrente(cubiculo_);
                        break;
        }
}


/** @brief capturarCubiculosEsquerda
  *
  * @todo: document this function
  */
void Face::capturarCubiculosEsquerda(Cubiculo* cubs[3][3][3])
{
        cubiculo[0][0] = cubs[0][0][0];
        cubiculo[0][1] = cubs[0][0][1];
        cubiculo[0][2] = cubs[0][0][2];
        cubiculo[1][0] = cubs[0][1][0];
        cubiculo[1][1] = cubs[0][1][1];
        cubiculo[1][2] = cubs[0][1][2];
        cubiculo[2][0] = cubs[0][2][0];
        cubiculo[2][1] = cubs[0][2][1];
        cubiculo[2][2] = cubs[0][2][2];
}

/** @brief capturarCubiculosDireita
  *
  * @todo: document this function
  */
void Face::capturarCubiculosDireita(Cubiculo* cubs[3][3][3])
{
        cubiculo[0][0] = cubs[2][0][2];
        cubiculo[0][1] = cubs[2][0][1];
        cubiculo[0][2] = cubs[2][0][0];
        cubiculo[1][0] = cubs[2][1][2];
        cubiculo[1][1] = cubs[2][1][1];
        cubiculo[1][2] = cubs[2][1][0];
        cubiculo[2][0] = cubs[2][2][2];
        cubiculo[2][1] = cubs[2][2][1];
        cubiculo[2][2] = cubs[2][2][0];
}

/** @brief capturarCubiculosFrente
  *
  * @todo: document this function
  */
void Face::capturarCubiculosFrente(Cubiculo* cubs[3][3][3])
{
        cubiculo[0][0] = cubs[0][0][2];
        cubiculo[0][1] = cubs[1][0][2];
        cubiculo[0][2] = cubs[2][0][2];
        cubiculo[1][0] = cubs[0][1][2];
        cubiculo[1][1] = cubs[1][1][2];
        cubiculo[1][2] = cubs[2][1][2];
        cubiculo[2][0] = cubs[0][2][2];
        cubiculo[2][1] = cubs[1][2][2];
        cubiculo[2][2] = cubs[2][2][2];
}

/** @brief capturarCubiculosTras
  *
  * @todo: document this function
  */
void Face::capturarCubiculosTras(Cubiculo* cubs[3][3][3])
{
        cubiculo[0][0] = cubs[2][0][0];
        cubiculo[0][1] = cubs[1][0][0];
        cubiculo[0][2] = cubs[0][0][0];
        cubiculo[1][0] = cubs[2][1][0];
        cubiculo[1][1] = cubs[1][1][0];
        cubiculo[1][2] = cubs[0][1][0];
        cubiculo[2][0] = cubs[2][2][0];
        cubiculo[2][1] = cubs[1][2][0];
        cubiculo[2][2] = cubs[0][2][0];
}

/** @brief capturarCubiculosBaixo
  *
  * @todo: document this function
  */
void Face::capturarCubiculosBaixo(Cubiculo* cubs[3][3][3])
{
        cubiculo[0][0] = cubs[0][0][0];
        cubiculo[0][1] = cubs[1][0][0];
        cubiculo[0][2] = cubs[2][0][0];
        cubiculo[1][0] = cubs[0][0][1];
        cubiculo[1][1] = cubs[1][0][1];
        cubiculo[1][2] = cubs[2][0][1];
        cubiculo[2][0] = cubs[0][0][2];
        cubiculo[2][1] = cubs[1][0][2];
        cubiculo[2][2] = cubs[2][0][2];
}

/** @brief capturarCubiculosCima
  *
  * @todo: document this function
  */
void Face::capturarCubiculosCima(Cubiculo* cubs[3][3][3])
{
        cubiculo[0][0] = cubs[0][2][2];
        cubiculo[0][1] = cubs[1][2][2];
        cubiculo[0][2] = cubs[2][2][2];
        cubiculo[1][0] = cubs[0][2][1];
        cubiculo[1][1] = cubs[1][2][1];
        cubiculo[1][2] = cubs[2][2][1];
        cubiculo[2][0] = cubs[0][2][0];
        cubiculo[2][1] = cubs[1][2][0];
        cubiculo[2][2] = cubs[2][2][0];
}


/** @brief rotaciona
  *
  * @todo: document this function
  */
void Face::rotaciona(eSentidoRotacao sentido, bool animado, double alfa)
{
        //Ajusta o sentido da rotação...
        //Tava dando erro na face de trás. (ela era a única que tava rodando pro outro lado)
        if (ladoDaFace == eFACENOME_TRAS ||ladoDaFace == eFACENOME_ESQUERDA || ladoDaFace == eFACENOME_BAIXO)
        {
                int aux = sentido;
                aux *= -1;
                sentido = (eSentidoRotacao)aux;
        }

        eEixoRotacao eixo;
        switch (ladoDaFace)
        {
                case eFACENOME_CIMA:
                case eFACENOME_BAIXO:
                                eixo = eEIXOROTACAO_Y;
                        break;
                case eFACENOME_ESQUERDA:
                case eFACENOME_DIREITA:
                                eixo = eEIXOROTACAO_X;
                        break;
                case eFACENOME_FRENTE:
                case eFACENOME_TRAS:
                                eixo = eEIXOROTACAO_Z;
                        break;
        }

        //Rotaciono os cubículos
        for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                        cubiculo[i][j]->rotacionar(eixo, sentido, animado, alfa);

}

/** @brief estaCompleta
  *
  * @todo: document this function
  */
bool Face::estaCompleta() const
{
        Color corDaFace = getColorDoCubiculoCentral();
        //Confiro a cor de todo cubículo voltado pra minha face
        for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                        if (!(cubiculo[i][j]->getCorAtravesDaFace(ladoDaFace) == corDaFace))
                                return false;
        return true;
}

/** @brief contemCubiculo
  *
  * @todo: document this function
  */
bool Face::contemCubiculo(const Cubiculo* c) const
{
        for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                        if (c == cubiculo[i][j])
                                return true;
        return false;
}

/** @brief getColorDoCubiculoCentral
  *
  * @todo: document this function
  */
const Color & Face::getColorDoCubiculoCentral() const
{
        return cubiculo[1][1]->getCorAtravesDaFace(ladoDaFace);
}

/** @brief getCubiculo
  *
  * @todo: document this function
  */
const Cubiculo* Face::getCubiculo(int a, int b) const
{
        if (a >= 0 && a <= 2 && b >=0 && b <= 2)
                return cubiculo[a][b];
        return NULL;
}

/** @brief getLadoDaFace
  *
  * @todo: document this function
  */
eFaceNome Face::getLadoDaFace() const
{
        return ladoDaFace;
}

