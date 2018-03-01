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


#include "CruzInferiorEstado.h"
#include "QuinasInferiorEstado.h"

CruzInferiorEstado::CruzInferiorEstado(const Color& cor_, AAlgoritmo* algoritmo): EstadoAlgoritmo(algoritmo), //Construtor do pai
                                                                                                    cor(cor_)
{
        //ctor
        for (int i = 0; i < 6; ++i)
                parteCruzResolvida[i] = false;

        //Essas duas não precisa resolver (não existe interseção)
        parteCruzResolvida[eFACENOME_CIMA] = true;
        parteCruzResolvida[eFACENOME_BAIXO] = true;

        iterarFace();
}

CruzInferiorEstado::~CruzInferiorEstado()
{
        //dtor
}

/** @brief atualiza
  *
  * @todo: document this function
  */
void CruzInferiorEstado::atualiza()
{
        //Primeira coisa a fazer é saber qual a outra cor do cubículo
        const Color& outraCor = algoritmo->getCubo()->getFace(faceDaCorDoProximoCubiculo)->getColorDoCubiculoCentral();

        //Localizar o cubículo que tenha a minha cor e a cor da face que tou procurando
        const Cubiculo* cubiculo = algoritmo->getCubo()->getCubiculoLadoDeCor(cor, outraCor);

        //Preciso saber em qual face tá da minha cor da cruz que eu tou montando (geralmente branco)
        eFaceNome faceDaMinhaCorDoCubiculo = cubiculo->getFaceAtravesDaCor(cor);

        //A face que o cubículo tá que não é a minha cor.. Em qual Face ela tá?
        eFaceNome outraFace = cubiculo->getFaceAtravesDaCor(outraCor);

        switch (faceDaMinhaCorDoCubiculo)
        {
                case eFACENOME_CIMA: //Ok!
                                minhaCorEmCima(outraFace);
                        break;
                case eFACENOME_BAIXO: //OK!
                                minhaCorEmbaixo(outraFace);
                        break;
                case eFACENOME_TRAS: //Bota a face em cima
                                minhaCorAtras(outraFace);
                        break;
                case eFACENOME_FRENTE: //Bota a face em cima
                                minhaCorNaFrente(outraFace);
                        break;
                case eFACENOME_DIREITA: //Bota a face em cima
                                minhaCorNaDireita(outraFace);
                        break;
                case eFACENOME_ESQUERDA: //Bota a face em cima
                                minhaCorNaEsquerda(outraFace);
                        break;
        }
}

void CruzInferiorEstado::iterarFace()
{
        for (int iteradorFace = 0;iteradorFace < 6; ++iteradorFace)
                if (!parteCruzResolvida[iteradorFace])
                {
                        faceDaCorDoProximoCubiculo = eFaceNome(iteradorFace);
                        return;
                }
        algoritmo->setEstadoAtual(new QuinasInferiorEstado(cor, algoritmo));
}

void CruzInferiorEstado::minhaCorNaDireita(eFaceNome outraFace)
{
//        printf("CruzInferiorEstado::minhaCorNaDireita \n");
        switch (outraFace)
        {
                case eFACENOME_FRENTE:
                                algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_ANTIHORARIO); //Boto a face que eu quero resolver pra cima
                                if (parteCruzResolvida[eFACENOME_FRENTE]) //Se a parte da direita já tava resolvida
                                {
                                        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO); //Mexo a face de cima pra qualquer canto (liberar a descida)
                                        algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_HORARIO); //Ajeito a parte que eu tinha desajeitado
                                }
                        break;
                case eFACENOME_TRAS: //Frente e trás são praticamente iguais
                                algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_HORARIO); //Boto a face que eu quero resolver pra cima
                                if (parteCruzResolvida[eFACENOME_TRAS]) //Se a parte da direita já tava resolvida
                                {
                                        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO); //Mexo a face de cima pra qualquer canto (liberar a descida)
                                        algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_ANTIHORARIO); //Ajeito a parte que eu tinha desajeitado
                                }
                        break;
                case eFACENOME_CIMA: //Movo para ficar atrás
                                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
                        break;
                case eFACENOME_BAIXO: //Movo para a outra face ficar atrás e eu, a minha à direita
                                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO);
                        break;
        }
}


void CruzInferiorEstado::minhaCorNaEsquerda(eFaceNome outraFace)
{
//        printf("CruzInferiorEstado::minhaCorNaEsquerda \n");
        switch (outraFace)
        {
                case eFACENOME_FRENTE:
                                algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_HORARIO); //Boto a face que eu quero resolver pra cima
                                if (parteCruzResolvida[eFACENOME_FRENTE]) //Se a parte da esquerda já tava resolvida
                                {
                                        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO); //Mexo a face de cima pra qualquer canto (liberar a descida)
                                        algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_ANTIHORARIO); //Ajeito a parte que eu tinha desajeitado
                                }
                        break;
                case eFACENOME_TRAS: //Frente e trás são praticamente iguais
                                algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_ANTIHORARIO); //Boto a face que eu quero resolver pra cima
                                if (parteCruzResolvida[eFACENOME_TRAS]) //Se a parte da direita já tava resolvida
                                {
                                        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO); //Mexo a face de cima pra qualquer canto (liberar a descida)
                                        algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_HORARIO); //Ajeito a parte que eu tinha desajeitado
                                }
                        break;
                case eFACENOME_CIMA: //Movo para ficar atrás
                                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                        break;
                case eFACENOME_BAIXO: //Movo para a outra face ficar atrás e eu, a minha à esquerda
                                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_HORARIO);
                        break;
        }
}


void CruzInferiorEstado::minhaCorNaFrente(eFaceNome outraFace)
{
//        printf("CruzInferiorEstado::minhaCorNaFrente \n");
        switch (outraFace)
        {
                case eFACENOME_ESQUERDA:
                                algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_ANTIHORARIO); //Boto a face que eu quero resolver pra cima
                                if (parteCruzResolvida[eFACENOME_ESQUERDA]) //Se a parte da esquerda já tava resolvida
                                {
                                        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO); //Mexo a face de cima pra qualquer canto (liberar a descida)
                                        algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_HORARIO); //Ajeito a parte que eu tinha desajeitado
                                }
                        break;
                case eFACENOME_DIREITA: //Frente e trás são praticamente iguais
                                algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO); //Boto a face que eu quero resolver pra cima
                                if (parteCruzResolvida[eFACENOME_DIREITA]) //Se a parte da direita já tava resolvida
                                {
                                        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO); //Mexo a face de cima pra qualquer canto (liberar a descida)
                                        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO); //Ajeito a parte que eu tinha desajeitado
                                }
                        break;
                case eFACENOME_CIMA: //Movo para ficar atrás
                                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);
                        break;
                case eFACENOME_BAIXO: //Movo para a outra face ficar na direita,  e eu, a minha frente
                                algoritmo->addMovimentoFace(eFACENOME_FRENTE, eSENTIDOROTACAO_HORARIO);
                        break;
        }
}



void CruzInferiorEstado::minhaCorAtras(eFaceNome outraFace)
{
//        printf("CruzInferiorEstado::minhaCorAtras \n");
        //Verifica se só uma rotação já é suficiente
        bool faceCorreta = (outraFace == faceDaCorDoProximoCubiculo);

        //Bota a face em cima
        switch (outraFace)
        {
                case eFACENOME_ESQUERDA:
                                if (faceCorreta)
                                        algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_HORARIO); //Só faço descer
                                else
                                {
                                        algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_HORARIO); //Subo
                                        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO); //Mexo pra qualqer lado, pra livrar a volta
                                        algoritmo->addMovimentoFace(eFACENOME_ESQUERDA, eSENTIDOROTACAO_ANTIHORARIO); //Desço pra arrumar o que talvez eu tenha desarrumado
                                }
                        break;
                case eFACENOME_DIREITA:
                                if (faceCorreta)
                                        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO); //Só faço descer
                                else
                                {
                                        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_ANTIHORARIO); //Subo
                                        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO); //Mexo pra qualqer lado, pra livrar a volta
                                        algoritmo->addMovimentoFace(eFACENOME_DIREITA, eSENTIDOROTACAO_HORARIO); //Desço pra arrumar o que talvez eu tenha desarrumado
                                }
                        break;
                case eFACENOME_CIMA://Deixo na esquerda!
                                algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_HORARIO); //Com esse movimento, fica na esquerda
                                return minhaCorAtras(utils::rotacionarFaceNome(eFACENOME_CIMA, eEIXOROTACAO_Z, eSENTIDOROTACAO_ANTIHORARIO)); //É invertido pq tá atrás (vide nome da função)
                case eFACENOME_BAIXO://Deixo na direita
                                algoritmo->addMovimentoFace(eFACENOME_TRAS, eSENTIDOROTACAO_HORARIO); //Com esse movimento, fica na direita
                                return minhaCorAtras(utils::rotacionarFaceNome(eFACENOME_BAIXO, eEIXOROTACAO_Z, eSENTIDOROTACAO_ANTIHORARIO)); //É invertido pq tá atrás (vide nome da função)
                        break;
        }
}


//Quando a branca tá embaixo
void CruzInferiorEstado::minhaCorEmbaixo(eFaceNome outraFace)
{
//        printf("CruzInferiorEstado::minhaCorEmbaixo \n");
        bool faceCorreta = (outraFace == faceDaCorDoProximoCubiculo);
        if (!faceCorreta)
        {
                //Bota a cor em cima
                algoritmo->addMovimentoFace(outraFace, eSENTIDOROTACAO_HORARIO);
                algoritmo->addMovimentoFace(outraFace, eSENTIDOROTACAO_HORARIO);
                minhaCorEmCima(outraFace);
                //Como tava embaixo, não desarrumou nenhuma
        }
        else
        {
                parteCruzResolvida[outraFace] = true; //Já tava resolvida
                //Como tá resolvido, vou fazer outra coisa
                iterarFace();
        }
}

//Quando a "branca" tá em cima
void CruzInferiorEstado::minhaCorEmCima(eFaceNome outraFace)
{
//        printf("CruzInferiorEstado::minhaCorEmCima \n");
        //Acessar a função que rotaciona
        using namespace utils;

        //Pode ser todas menos: Cima e baixo
        //Posiciono em cima da face correta
        int numRotacoes = 0;
        while (outraFace != faceDaCorDoProximoCubiculo)
        {
                outraFace = rotacionarFaceNome(outraFace, eEIXOROTACAO_Y, eSENTIDOROTACAO_HORARIO);
                ++numRotacoes;
        }
        //Verifico qual o menor caminho
        if (numRotacoes  > 2)
                algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_ANTIHORARIO);
        else
                while (--numRotacoes >= 0)
                        algoritmo->addMovimentoFace(eFACENOME_CIMA, eSENTIDOROTACAO_HORARIO);

        //Desço até formar a cruz
        algoritmo->addMovimentoFace(outraFace, eSENTIDOROTACAO_HORARIO);
        algoritmo->addMovimentoFace(outraFace, eSENTIDOROTACAO_HORARIO);

        //Como eu resolvi essa face
        parteCruzResolvida[faceDaCorDoProximoCubiculo] = true;

        //Como tá resolvido, vou fazer outra coisa
        iterarFace();
}









