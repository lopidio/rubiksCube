/** ********************/
//***************
//  - Lopidio
#include "FaceSuperiorEstado.h"

#include "CentraisSuperioresEstado.h"

FaceSuperiorEstado::FaceSuperiorEstado(AAlgoritmo* algoritmo_):EstadoAlgoritmo(algoritmo_)
{
        //ctor
        cubiculos.reserve(4);
        cubiculosErrados.reserve(4);
}

FaceSuperiorEstado::~FaceSuperiorEstado()
{
        //dtor
}

/** @brief atualiza
  *
  * @todo: document this function
  */
void FaceSuperiorEstado::atualiza()
{
        numCubiculosNaoPosicionados();
        if (cubiculosErrados.size() == 2)
                return escolherEntreEstados345();
        else if (cubiculosErrados.size() == 3)
                return escolherEntreEstados12();
        else if (cubiculosErrados.size() == 4)
                return escolherEntreEstados67();
        else if (cubiculosErrados.size() == 0)
                return algoritmo->setEstadoAtual( new CentraisSuperioresEstado(algoritmo));
}

/** @brief sentidoAntihorarioAlgoritmo
  *
  * @todo: document this function
  */
void FaceSuperiorEstado::sentidoAntihorarioAlgoritmo()
{
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
}

/** @brief sentidoHorarioAlgoritmo
  *
  * @todo: document this function
  */
void FaceSuperiorEstado::sentidoHorarioAlgoritmo()
{
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
}

/** @brief numCubiculosNaoPosicionados
  *
  * @todo: document this function
  */
void FaceSuperiorEstado::numCubiculosNaoPosicionados()
{
        cubiculosErrados.clear();
        cubiculos.clear();

        const Face* face = algoritmo->getCubo()->getFace(eFACENOME_CIMA);
        Color faceCor = face->getColorDoCubiculoCentral();
        for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                        const Cubiculo* cubiculo = face->getCubiculo(i,j);
                        if (cubiculo->getNumFaciculas() == 3)
                        {
                                cubiculos.push_back(cubiculo);
                                Color cubColor = cubiculo->getCorAtravesDaFace(eFACENOME_CIMA);
                                if (!(cubColor == faceCor))
                                {
                                        cubiculosErrados.push_back(cubiculo);
                                }
                        }
                }
}

/** @brief escolherEntreEstados67
  *
  * @todo: document this function
  */
void FaceSuperiorEstado::escolherEntreEstados67()
{       //        ^
        // 00 --  20
        // --  X --
        // -- -- 22
        //       v
        const Cubiculo* cubiculo20 = algoritmo->getCubo()->getCubiculo(2,2,0);
        const Cubiculo* cubiculo22 = algoritmo->getCubo()->getCubiculo(2,2,2);

        eFaceNome praOndeApontaO20 = cubiculo20->getFaceAtravesDaCor(algoritmo->getCubo()->getFace(eFACENOME_CIMA)->getColorDoCubiculoCentral());
        eFaceNome praOndeApontaO22 = cubiculo22->getFaceAtravesDaCor(algoritmo->getCubo()->getFace(eFACENOME_CIMA)->getColorDoCubiculoCentral());
        //rodo até ficar numa posição legal
        if (praOndeApontaO20 != eFACENOME_TRAS || praOndeApontaO22 != eFACENOME_FRENTE)
                return algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_ANTIHORARIO);

        const Cubiculo* cubiculo00 = algoritmo->getCubo()->getCubiculo(0,2,0);
        eFaceNome praOndeApontaO00 = cubiculo00->getFaceAtravesDaCor(algoritmo->getCubo()->getFace(eFACENOME_CIMA)->getColorDoCubiculoCentral());
        //Estado 6
        if (praOndeApontaO00 == eFACENOME_ESQUERDA)
        {
                return sentidoAntihorarioAlgoritmo();
        }
        //Estado 7
        else if (praOndeApontaO00 == eFACENOME_TRAS)
        {
                return sentidoHorarioAlgoritmo();
        }
}

bool find(const vector<const Cubiculo*>& a, const Cubiculo* b)
{
        for (int i = 0; i < a.size(); ++i)
                if (b == a[i])
                        return true;
        return false;
}

/** @brief escolherEntreEstados12
  *
  * @todo: document this function
  */
void FaceSuperiorEstado::escolherEntreEstados12()
{
        const Cubiculo* cuboCerto = NULL;
        for (int i = 0; i < cubiculos.size(); ++i)
                if (!find(cubiculosErrados, cubiculos[i]))
                        cuboCerto = cubiculos[i];

        int posX = cuboCerto->getPosicaoNoCubo().getX();
        int posZ = cuboCerto->getPosicaoNoCubo().getZ();
        if (posX != -1 | posZ == 1)
                return algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_ANTIHORARIO);

        //Se chegou até aqui é
        const Cubiculo* cuboErrado = algoritmo->getCubo()->getCubiculo(2,2,2);
        eFaceNome faceDaCorDeCima = cuboErrado->getFaceAtravesDaCor(algoritmo->getCubo()->getFace(eFACENOME_CIMA)->getColorDoCubiculoCentral());
        if (faceDaCorDeCima == eFACENOME_DIREITA)
        {
                sentidoAntihorarioAlgoritmo();
                return;
        }
        if (faceDaCorDeCima == eFACENOME_FRENTE)
                return sentidoHorarioAlgoritmo();
}

/** @brief escolherEntreEstados345
  *
  * @todo: document this function
  */
void FaceSuperiorEstado::escolherEntreEstados345()
{
        // 00 -- 20
        // --  X --
        // 02 -- 22
        bool cubiculo00Errado = find(cubiculosErrados, algoritmo->getCubo()->getCubiculo(0,2,0));
        bool cubiculo20Errado = find(cubiculosErrados, algoritmo->getCubo()->getCubiculo(2,2,0));
        bool cubiculo02Errado = find(cubiculosErrados, algoritmo->getCubo()->getCubiculo(0,2,2));
        bool cubiculo22Errado = find(cubiculosErrados, algoritmo->getCubo()->getCubiculo(2,2,2));

        if (cubiculo00Errado || !cubiculo20Errado)
                return algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_ANTIHORARIO);

        eFaceNome praOndeAponta20 = algoritmo->getCubo()->getCubiculo(2,2,0)->getFaceAtravesDaCor(algoritmo->getCubo()->getFace(eFACENOME_CIMA)->getColorDoCubiculoCentral());
        //Verifiquei o estado 5
        if (cubiculo20Errado && cubiculo02Errado)
        {
                if (praOndeAponta20 == eFACENOME_DIREITA)
                        algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_ANTIHORARIO);
                if (praOndeAponta20 == eFACENOME_TRAS)
                        algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
                sentidoAntihorarioAlgoritmo();
                return;
        }

        //verifiquei o estado 3
        if (praOndeAponta20 == eFACENOME_DIREITA)
        {
                algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
                sentidoHorarioAlgoritmo();
                return;
        }
        //verifiquei o estado 3
        if (praOndeAponta20 == eFACENOME_TRAS)
        {
                algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
                sentidoHorarioAlgoritmo();
                return;
        }

}

