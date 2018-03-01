/** ********************/
//***************
//  - Lopidio
#include "UltimoMovimentoEstado.h"

UltimoMovimentoEstado::UltimoMovimentoEstado(AAlgoritmo* algoritmo_):EstadoAlgoritmo(algoritmo_)
{
        //ctor
}

UltimoMovimentoEstado::~UltimoMovimentoEstado()
{
        //dtor
}

/** @brief atualiza
  *
  * @todo: document this function
  */
void UltimoMovimentoEstado::atualiza()
{
        const Face* face = NULL;
        int numFacesLateraisCompletas = 0;
        for (int i = 0; i < 6; ++i)
        {
                eFaceNome fa = (eFaceNome)i;
                if (fa == eFACENOME_CIMA || fa == eFACENOME_BAIXO)
                        continue;
                bool faceCompleta = algoritmo->getCubo()->getFace(fa)->estaCompleta();
                if (faceCompleta)
                {
                        numFacesLateraisCompletas++;
                        face = algoritmo->getCubo()->getFace(fa);
                }
        }

        if (face && face->getLadoDaFace() != eFACENOME_ESQUERDA && numFacesLateraisCompletas == 1)
                return algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);

        if (numFacesLateraisCompletas == 0)
                return executa();
        if (numFacesLateraisCompletas == 1)
                return executa();
        if (numFacesLateraisCompletas > 1)
                printf("Cubo montado\n\n\n\n\n\n\n\n\n");
}


/** @brief executa
  *
  * @todo: document this function
  */
void UltimoMovimentoEstado::executa()
{
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
}

