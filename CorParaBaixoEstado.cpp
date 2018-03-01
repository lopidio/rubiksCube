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


#include "CorParaBaixoEstado.h"
#include "CruzInferiorEstado.h"
#include "Principal.h"

CorParaBaixoEstado::CorParaBaixoEstado(const Color& cor_, AAlgoritmo* algoritmo): EstadoAlgoritmo(algoritmo), cor(cor_)
{
        //ctor
}

CorParaBaixoEstado::~CorParaBaixoEstado()
{
        //dtor
}


/** @brief atualiza
  *
  * @todo: document this function
  */
void CorParaBaixoEstado::atualiza()
{
        eFaceNome faceAtual;
        for (int i = 0; i < 6; i++)
        { //Descubro onde tá a cor que eu quero
                eFaceNome face = eFaceNome(i);
                if (algoritmo->getCubo()->getFace(face)->getColorDoCubiculoCentral() == cor)
                        faceAtual = face;
        }

        switch (faceAtual)
        {
                case eFACENOME_CIMA:
                                algoritmo->addMovimentoTodo(eEIXOROTACAO_X, eSENTIDOROTACAO_HORARIO);
                                algoritmo->addMovimentoTodo(eEIXOROTACAO_X, eSENTIDOROTACAO_HORARIO);
                        break;
                case eFACENOME_DIREITA:
                                algoritmo->addMovimentoTodo(eEIXOROTACAO_Z, eSENTIDOROTACAO_HORARIO);
                        break;
                case eFACENOME_ESQUERDA:
                                algoritmo->addMovimentoTodo(eEIXOROTACAO_Z, eSENTIDOROTACAO_ANTIHORARIO);
                        break;
                case eFACENOME_FRENTE:
                                algoritmo->addMovimentoTodo(eEIXOROTACAO_X, eSENTIDOROTACAO_ANTIHORARIO);
                        break;
                case eFACENOME_TRAS:
                                algoritmo->addMovimentoTodo(eEIXOROTACAO_X, eSENTIDOROTACAO_HORARIO);
                        break;
        }

        return algoritmo->setEstadoAtual(new CruzInferiorEstado(cor, algoritmo));
}

