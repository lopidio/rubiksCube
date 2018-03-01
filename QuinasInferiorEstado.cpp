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


#include "QuinasInferiorEstado.h"
#include "SegundaCamadaEstado.h"


QuinasInferiorEstado::QuinasInferiorEstado(const Color& cor_, AAlgoritmo* algoritmo):
                                                EstadoAlgoritmo(algoritmo),// Construtor do pai
                                                cor(cor_) //Cor da face virada para baixo
{
        //ctor
        //algoritmo->getCubo()->getCubiculoQuinaDeCor() --> Tu vai usar mto essa função aqui!!
        //Se liga que o cubo é constante!
        //A cruz vai tá virada para baixo!
        construirLista();
//        faciculaCorCorretaJaEstaDeLado = false;
        marcadoParaIteracao = false;
}

QuinasInferiorEstado::~QuinasInferiorEstado()
{
        //dtor
}



/** @brief construirLista
  *
  * @todo: document this function
  */
void QuinasInferiorEstado::construirLista()
{
        for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                        for (int k = 0; k < 3; k++)
                        {
                                //Pego todos os cubículos de quina que tenha minha cor
                                const Cubiculo* cubiculo = algoritmo->getCubo()->getCubiculo(i,j,k);
                                if (cubiculo->getNumFaciculas() == 3 && //Se for uma quina E
                                    cubiculo->temCor(cor) ) //Tiver minha cor
                                        cubiculos.push_back(cubiculo);
                        }
        iterator = cubiculos.begin();
}

/** @brief atualiza
  *
  * @todo: document this function
  */
void QuinasInferiorEstado::atualiza()
{
        if (marcadoParaIteracao)
                return iterar();
        const Cubiculo* cub = *iterator;

        eFaceNome faceCorreta = (*iterator)->getFaceAtravesDaCor(cor);
        if (faceCorreta == eFACENOME_BAIXO || faceCorreta == eFACENOME_CIMA)
        {
                //Rotaciono até o cubiculo ficar com o Z = 1
                if (cub->getPosicaoNoCubo().getZ() != 1)
                        return algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);

                if (faceCorreta == eFACENOME_BAIXO)
                {
                        if (algoritmo->getCubo()->estaCubiculoNaPosicaoCorreta(*iterator))
                                return iterar();
                        return moverBaixoParaLado();
                }
                if (faceCorreta == eFACENOME_CIMA)
                        return moverCimaParaLado();
        }
        if ((*iterator)->getPosicaoNoCubo().getY() == -1) //Se tiver lá embaixo
        {
                if (faceCorreta != eFACENOME_FRENTE)//Faço isso até dar certo
                        return algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
                return moverLadoInferiorParaLadoSuperior();
        }

        //Se a cor de cima tiver diferente da cor da frente (rotaciono até a projeção ficar correta)
        if (!(cub->getCorAtravesDaFace(eFACENOME_CIMA) ==
              algoritmo->getCubo()->getFace(faceCorreta)->getColorDoCubiculoCentral()))
                return algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);

        if (faceCorreta != eFACENOME_FRENTE)//Faço isso até dar certo
                return algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
        botarNaPosicaoCorreta(); //Movo até a posição correta
}

/** @brief iterar
  *
  * @todo: document this function
  */
void QuinasInferiorEstado::iterar()
{
        if (algoritmo->getCubo()->estaCubiculoNaPosicaoCorreta(*iterator))
        {
                //É um pq eu vou remover um aqui dentro
                if (cubiculos.size() > 1)//Ainda existe coisa pra fazer
                {
                        cubiculos.remove(*iterator);
                        iterator = cubiculos.begin();
                }
                else
                {
                        //muda o estado
                        return algoritmo->setEstadoAtual(new SegundaCamadaEstado(algoritmo));
                }
        }
        marcadoParaIteracao = false;
}

/** @brief moverLadoInferiorParaLadoSuperior
  *
  * @todo: document this function
  */
void QuinasInferiorEstado::moverLadoInferiorParaLadoSuperior()
{
        //Verifico se tá certa no eixoX
        float posX = (*iterator)->getPosicaoNoCubo().getX();
        if (posX == 1)//Se tiver na direita
        {
                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
        }
        else //if (posX == -1)
        {
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_HORARIO);
        }
}

/** @brief botarNaPosicaoCorreta
  *
  * @todo: document this function
  */
void QuinasInferiorEstado::botarNaPosicaoCorreta()
{
        //Verifico se tá certa no eixoX
        float posX = (*iterator)->getPosicaoNoCubo().getX();
        if (posX == 1)//Se tiver na direita
        {
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
        }
        else //if (posX == -1)
        {
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_HORARIO);
        }
        marcadoParaIteracao = true;
}


/** @brief moverBaixoParaLado
  *
  * @todo: document this function
  */
void QuinasInferiorEstado::moverBaixoParaLado()
{
        //Aqui o Z e o Y sempre são 1 e -1, respectivamente
        int x = (*iterator)->getPosicaoNoCubo().getX();

        if (x == 1)
        {
                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
        }
        else //if (x == -1)
        {
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_HORARIO);
        }

}


/** @brief moverCimaParaLado
  *
  * @todo: document this function
  */
void QuinasInferiorEstado::moverCimaParaLado()
{
        int x = (*iterator)->getPosicaoNoCubo().getX();
        const Cubiculo* cubProjetado = algoritmo->getCubo()->getCubiculo(x+1,0,2);
        bool cuboProjetadoCorreto = algoritmo->getCubo()->estaCubiculoNaPosicaoCorreta(cubProjetado);
        if (cuboProjetadoCorreto)
        {
                return algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO); //Tiro a face di cima dessa posição
        }
        if (x == 1)
        {
                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
        }
        else //if x == -1
        {
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_HORARIO);
        }

}

