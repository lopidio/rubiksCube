/** ********************/
//***************
//  - Lopidio
#include "CentraisSuperioresEstado.h"
#include "UltimoMovimentoEstado.h"

CentraisSuperioresEstado::CentraisSuperioresEstado(AAlgoritmo* algoritmo_):EstadoAlgoritmo(algoritmo_)
{
        //ctor
}

CentraisSuperioresEstado::~CentraisSuperioresEstado()
{
        //dtor
}

/** @brief atualiza
  *
  * @todo: document this function
  */
void CentraisSuperioresEstado::atualiza()
{
        eFaceNome ondeApontaAFaceMinerva = eFACENOME_INEXISTENTE;
        Color corMinerva = Color::Indefinido();
        int numFacesMinerva = 0;
        for(int i = 0; i < 6; ++i)
        {
                eFaceNome fa = (eFaceNome)i;
                if (fa == eFACENOME_CIMA || fa == eFACENOME_BAIXO)
                        continue;
                const Color &cor = verificaFaceMinerva(algoritmo->getCubo()->getFace(fa));
                if (!(cor == Color::Indefinido()))
                {
                        corMinerva = cor;
                        numFacesMinerva++;
                        ondeApontaAFaceMinerva = fa;
                }
        }

        //Nenhuma minerva, então embaralha um pouco
        if (numFacesMinerva == 0)
                return executa();

        //Encaixa na face correta
        if (!(algoritmo->getCubo()->getFace(ondeApontaAFaceMinerva)->getColorDoCubiculoCentral() == corMinerva))
                return algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);

        //Vira o cubo para trás
        if (ondeApontaAFaceMinerva != eFACENOME_TRAS)
                return algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_ANTIHORARIO);

        if (numFacesMinerva == 1)
                return executa();
        else
                return algoritmo->setEstadoAtual(new UltimoMovimentoEstado(algoritmo));

}

/** @brief verificaFaceMinerva
  *
  * @todo: document this function
  */
const Color& CentraisSuperioresEstado::verificaFaceMinerva(const Face* face) const
{
        // 20 -- 22
        // -- XX --
        // -- -- --
        const Color& corDo00 = face->getCubiculo(2,0)->getCorAtravesDaFace(face->getLadoDaFace());
        const Color& corDo22 = face->getCubiculo(2,2)->getCorAtravesDaFace(face->getLadoDaFace());
        if (corDo00 == corDo22)
                return corDo00;
        return Color::Indefinido();
}

/** @brief executa
  *
  * @todo: document this function
  */
void CentraisSuperioresEstado::executa()
{
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
        algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
}

