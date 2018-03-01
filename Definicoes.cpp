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

#include "Definicoes.h"
#include "Vector3.h"

namespace utils
{
        eFaceNome rotacionarFaceNome(eFaceNome face, eEixoRotacao eixo, eSentidoRotacao sentido)
        {
                Vector3 vetor(face);
                double angulo = M_PI_2;
                if (eixo == eSENTIDOROTACAO_HORARIO)
                        angulo *= -1;

                Matriz* rotacao;
                if (eixo == eEIXOROTACAO_X)
                        rotacao = Matriz::RotacaoX(angulo);
                else if (eixo == eEIXOROTACAO_Y)
                        rotacao = Matriz::RotacaoY(angulo);
                else if (eixo == eEIXOROTACAO_Z)
                        rotacao = Matriz::RotacaoZ(angulo);

                vetor.multiplicaPor(*rotacao);
                vetor.arredondar();
                return vetor.toFacicula();
        }

        eFaceNome iterar(eFaceNome face)
        {
                int f = face;
                ++f;
                f%=6;
                return eFaceNome(f);
        }

        eSentidoRotacao inverter(eSentidoRotacao sentido)
        {
                if (sentido == eSENTIDOROTACAO_HORARIO)
                        return eSENTIDOROTACAO_ANTIHORARIO;
                else //if (sentido == eSENTIDOROTACAO_ANTIHORARIO)
                        return eSENTIDOROTACAO_HORARIO;
        }

        const char* faceToString(eFaceNome face)
        {
                switch (face)
                {
                        case eFACENOME_CIMA:
                                return "eFACENOME_CIMA";
                        case eFACENOME_FRENTE:
                                return "eFACENOME_FRENTE";
                        case eFACENOME_ESQUERDA:
                                return "eFACENOME_ESQUERDA";
                        case eFACENOME_DIREITA:
                                return "eFACENOME_DIREITA";
                        case eFACENOME_TRAS:
                                return "eFACENOME_TRAS";
                        case eFACENOME_BAIXO:
                                return "eFACENOME_BAIXO";
                        default :
                                return "eFACENOME_INEXISTENTE";
                }
        }

}
