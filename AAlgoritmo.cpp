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


#include "AAlgoritmo.h"
#include "F2L.h"

AAlgoritmo::AAlgoritmo()
{
        animado = true;
        numPassos = 0;
}

AAlgoritmo::~AAlgoritmo()
{
        cubo->removeObserver(this);
}

/** @brief addMovimentoFace
  *
  * @todo: document this function
  */
void AAlgoritmo::addMovimentoFace(eFaceNome face, eSentidoRotacao sentido)
{
//        printf("\tAAlgoritmo::addMovimentoFace  %s, %d, %d\n", utils::faceToString(face), sentido, numPassos);
        ++numPassos; //Incrementa o número de passos, né?

        Cubo::Rotacao rot;
        rot.rotacaoFace = true;
        rot.sentido = sentido;
        rot.animado = animado;
        rot.face = face;
        cubo->addRotacaoFace(rot);
}

/** @brief addMovimentoTodo
  *
  * @todo: document this function
  */
void AAlgoritmo::addMovimentoTodo(eEixoRotacao eixo, eSentidoRotacao sentido)
{
        Cubo::Rotacao rot;
        rot.rotacaoFace = false;
        rot.sentido = sentido;
        rot.animado = animado;
        rot.eixo = eixo;
        cubo->addRotacaoTodo(rot);
}

/** @brief onFimCuboRotacao
  *
  * @todo: document this function
  */
void AAlgoritmo::onFimCuboRotacoes(const Cubo* cubo_)
{
}

/** @brief atualiza
  *
  * @todo: document this function
  */
void AAlgoritmo::atualiza()
{
        if  (cubo->filaRotacoesVazia() && !cubo->estaRotacionando())
                atualizaFilho();
}


/** @brief fabrica
  *
  * @todo: document this function
  */
AAlgoritmo* AAlgoritmo::Fabrica(eAlgoritmoID id, Cubo* cubo)
{
        //Retornarei o algoritmo pedido
        AAlgoritmo* retorno = NULL;
        switch (id)
        {
                default:
                        retorno = new F2L();
        }
        retorno->cubo = cubo;
        //Cadastro o algoritmo como observador do cubo
        cubo->addObserver(retorno);
        return retorno;
}


/** @brief getNumPassos
  *
  * @todo: document this function
  */
int AAlgoritmo::getNumPassos() const
{
        return numPassos;
}

/** @brief primeiroPasso
  *
  * @todo: document this function
  */
void AAlgoritmo::primeiroPasso()
{
        //do nothing... Hook
}

/** @brief setAnimado
  *
  * @todo: document this function
  */
void AAlgoritmo::setAnimado(bool a)
{
        animado = a;
}


/** @brief embaralhar
  *
  * @todo: document this function
  */
void AAlgoritmo::Embaralhar(Cubo* cubo, bool animado)
{
        int numPassosEmbaralhamento = 30;
        Cubo::Rotacao rot;
        int ultimaFaceRotacionada;
        while (numPassosEmbaralhamento--)
        {
                rot.animado = animado;
                //Pra que não exista movimentos repetido em sequencia
                do
                {
                        rot.criarAleatoriamente();
                } while (ultimaFaceRotacionada == rot.face);
                ultimaFaceRotacionada = rot.face;

                //É interessante que só sejam rotações de faces, não?
                rot.rotacaoFace = true;
                cubo->addRotacaoFace(rot);
        }
}


/** @brief getCubo
  *
  * @todo: document this function
  */
const Cubo* AAlgoritmo::getCubo() const
{
        return cubo;
}

/** @brief executa
  *
  * @todo: document this function
  */
void AAlgoritmo::executa()
{
        //Vai iniciar a contagem do tempo
        primeiroPasso();
}

/** @brief setEstadoAtual
  *
  * @todo: document this function
  */
void AAlgoritmo::setEstadoAtual(EstadoAlgoritmo* novoEstado)
{
        if (novoEstado)
        {
                delete estadoAtual;
                estadoAtual = novoEstado;
                atualiza();
        }
}


/** @brief onCuboCompleto
  *
  * @todo: document this function
  */
void AAlgoritmo::onCuboCompleto()
{

}


