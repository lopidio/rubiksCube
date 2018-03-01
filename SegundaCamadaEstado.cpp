/** ********************/
//***************
//  - Lopidio
#include "SegundaCamadaEstado.h"

#include "CruzSuperiorEstado.h"

SegundaCamadaEstado::SegundaCamadaEstado(AAlgoritmo* algoritmo):EstadoAlgoritmo(algoritmo)
{
        numCubiculosAjeitados = 0;
        construirLista();
//        bool b = algoritmo->getCubo()->getFace(eFACENOME_BAIXO)->estaCompleta();
//        printf("Num passos: %d. Tamanho da pilha: %d\n", algoritmo->getNumPassos(), !algoritmo->getCubo()->filaRotacoesVazia());
//        while (!b)
//        {
//                printf("%s, instancia incompleta!!\n", __PRETTY_FUNCTION__);
//                exit(-4);
//        }
}

SegundaCamadaEstado::~SegundaCamadaEstado()
{
        //dtor
}

/** @brief construirLista
  *
  * @todo: document this function
  */
void SegundaCamadaEstado::construirLista()
{
        Color corBaixo = algoritmo->getCubo()->getFace(eFACENOME_BAIXO)->getColorDoCubiculoCentral();
        Color corCima = algoritmo->getCubo()->getFace(eFACENOME_CIMA)->getColorDoCubiculoCentral();
        for (int x = 0; x <= 2; ++x)
                for (int y = 0; y <= 2; ++y)
                        for (int z = 0; z <= 2; ++z)
                        {
                                const Cubiculo* cub = algoritmo->getCubo()->getCubiculo(x,y,z);
                                if (!cub->temCor(corBaixo) && !cub->temCor(corCima) && cub->getNumFaciculas() == 2)
                                        cubiculos.push_back(cub);
                        }
        cubiculo = cubiculos.begin();
}

/** @brief atualiza
  *
  * @todo: document this function
  */
void SegundaCamadaEstado::atualiza()
{
        //Mudar oe stado
        if (numCubiculosAjeitados == 4)
        {
              //Mudo o estado
              return algoritmo->setEstadoAtual(new CruzSuperiorEstado(algoritmo));
        }
        //Bota o cubículo na parte da frente
        if ((*cubiculo)->getPosicaoNoCubo().getZ() != 1)
                return algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
        //Se o cubículo tiver no meio, sobe
        if ((*cubiculo)->getPosicaoNoCubo().getY() == 0)
                return subirCubiculo();

        //A cor da frente do cubo deve ser a mesma cor da frente do cubiculo
        Color corFrenteCubo = algoritmo->getCubo()->getFace(eFACENOME_FRENTE)->getColorDoCubiculoCentral();
        Color corFrenteCubiculo = (*cubiculo)->getCorAtravesDaFace(eFACENOME_FRENTE);
        if (!(corFrenteCubiculo == corFrenteCubo))
        {
                //roda até ficar alinhada as cores
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                return;
        }

        //Bota na posição correta
        descerCubiculo();
        iterarOuMudarEstado();
}

/** @brief descerCubiculo
  *
  * @todo: document this function
  */
void SegundaCamadaEstado::descerCubiculo()
{
        Color corDeCimaCubiculo = (*cubiculo)->getCorAtravesDaFace(eFACENOME_CIMA);
        Color corDaDireitaCubo = algoritmo->getCubo()->getFace(eFACENOME_DIREITA)->getColorDoCubiculoCentral();
        if (corDeCimaCubiculo == corDaDireitaCubo)
        {
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
                //
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_HORARIO);
        }
        else
        {
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_HORARIO);
                //
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_ANTIHORARIO);
        }

}

/** @brief subirCubiculo
  *
  * @todo: document this function
  */
void SegundaCamadaEstado::subirCubiculo()
{
        int posX = (*cubiculo)->getPosicaoNoCubo().getX();
        //Vou botar a de cima no meu lugar
        if (posX == 1)
        {
                //Boto na poição que é fácil subir
                algoritmo->addMovimentoTodo(eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
        }

        //A substituo pela peça do meio da frente de cima
        {
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_HORARIO);
                //
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_ANTIHORARIO);
        }
}

/** @brief iterarOuMudarEstado
  *
  * @todo: document this function
  */
void SegundaCamadaEstado::iterarOuMudarEstado()
{
        ++numCubiculosAjeitados;
        //Melhor mudar o estado no atualizar
        if (numCubiculosAjeitados < 4) //Ainda existe coisa pra fazer
        {
                cubiculo++;
        }
}

