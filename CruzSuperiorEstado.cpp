/** ********************/
//***************
//  - Lopidio
#include "CruzSuperiorEstado.h"
#include "FaceSuperiorEstado.h"

CruzSuperiorEstado::CruzSuperiorEstado(AAlgoritmo* algoritmo_):EstadoAlgoritmo(algoritmo_),
                                                        corCruz(algoritmo->getCubo()->getFace(eFACENOME_CIMA)->getColorDoCubiculoCentral())
{
        //ctor
        for (int i = 0; i < 4; ++i)
                faciculasCorretasParaCima[i] = false;
}

CruzSuperiorEstado::~CruzSuperiorEstado()
{
        //dtor
}

/** @brief atualiza
  *
  * @todo: document this function
  */
void CruzSuperiorEstado::atualiza()
{
        int numCruzParaCima = numFaciculasCruzParaCima();
        if (numCruzParaCima == 0 || numCruzParaCima == 1)
                return doAlgoritmo();
        if (numCruzParaCima == 2 || numCruzParaCima == 3)
                return verificaLOuLinha();
        if (numCruzParaCima == 4)//Muda o estado
                return algoritmo->setEstadoAtual(new FaceSuperiorEstado(algoritmo));
}

/** @brief numFaciculasCruzParaCima
  *
  * @todo: document this function
  */
int CruzSuperiorEstado::numFaciculasCruzParaCima()
{
        const Face* faceCima = algoritmo->getCubo()->getFace(eFACENOME_CIMA);
        faciculasCorretasParaCima[0] = faceCima->getCubiculo(0,1)->getCorAtravesDaFace(eFACENOME_CIMA) == corCruz;
        faciculasCorretasParaCima[1] = faceCima->getCubiculo(1,0)->getCorAtravesDaFace(eFACENOME_CIMA) == corCruz;
        faciculasCorretasParaCima[2] = faceCima->getCubiculo(1,2)->getCorAtravesDaFace(eFACENOME_CIMA) == corCruz;
        faciculasCorretasParaCima[3] = faceCima->getCubiculo(2,1)->getCorAtravesDaFace(eFACENOME_CIMA) == corCruz;

//        printf("\n\n");
//        faceCima->getCubiculo(0,0)->getCorAtravesDaFace(eFACENOME_CIMA).print();
//        faceCima->getCubiculo(0,1)->getCorAtravesDaFace(eFACENOME_CIMA).print();

        int retorno = 0;
        for (int i = 0; i < 4; ++i)
                retorno += faciculasCorretasParaCima[i];
        return retorno;
}

/** @brief verificaLOuLinha
  *
  * @todo: document this function
  */
void CruzSuperiorEstado::verificaLOuLinha()
{
        // --  f3 --
        // f1  X  f2
        // --  f0 --
        if (faciculasCorretasParaCima[0] && faciculasCorretasParaCima[3])
        {
                algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
                return doAlgoritmo();
        }
        if (faciculasCorretasParaCima[1] && faciculasCorretasParaCima[2])
        {
                return doAlgoritmo();
        }

        return LAlgoritmo();
}

/** @brief LAlgoritmo
  *
  * @todo: document this function
  */
void CruzSuperiorEstado::LAlgoritmo()
{
        // --  f3 --
        // f1  X  f2
        // --  f0 --
        if (faciculasCorretasParaCima[0] && faciculasCorretasParaCima[2])
        {
                algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
                return doAlgoritmo();
        }
        if (faciculasCorretasParaCima[1] && faciculasCorretasParaCima[0])
        {
                algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
                return doAlgoritmo();
        }
        if (faciculasCorretasParaCima[3] && faciculasCorretasParaCima[1])
        {
                return doAlgoritmo();
        }
        if (faciculasCorretasParaCima[2] && faciculasCorretasParaCima[3])
        {
                algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_ANTIHORARIO);
                return doAlgoritmo();
        }
}



/** @brief doAlgoritmo
  *
  * @todo: document this function
  */
void CruzSuperiorEstado::doAlgoritmo()
{
        algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_ANTIHORARIO);
}

