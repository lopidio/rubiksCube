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


#include "F2L.h"
#include "CorParaBaixoEstado.h"

F2L::F2L()
{
        //Instancia o primeiro estado (pode ser aqui ou no primeiro passo)
        estadoAtual = new CorParaBaixoEstado(Color::Branco(), this);
}

F2L::~F2L()
{
        //dtor
}


/** @brief atualiza
  *
  * @todo: document this function
  */
void F2L::atualizaFilho()
{
        if (estadoAtual)
                estadoAtual->atualiza();
}


/** @brief onCuboCompleto
  *
  * @todo: document this function
  */
void F2L::onCuboCompleto()
{
        delete estadoAtual;
        estadoAtual = NULL;
        printf("Fim do algoritmo. Num passos: %d\n", this->getNumPassos());
}







