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


#include "Cubiculo.h"
#include "Definicoes.h"
#include "Principal.h"


//Aproxima "var" de "target", somando "step" e retorna o quanto foi aproximado
float transformaEm(float& var, float target, float step)
{
        float retorno = step;
        if (target > var)
        {
                if (var + step > target)
                {
                        retorno = target - var;
                        var = target;
                }
                else
                        var += step;
        }
        else if (target < var)
        {
                retorno *= -1;
                if (var - step < target)
                {
                        retorno = target - var;
                        var = target;
                }
                else
                        var -= step;
        }
        else // target == var
        {
                retorno = 0;
        }
        return retorno;
}

Cubiculo::Cubiculo()
{
        //Default
}

/** @brief Cubiculo
  *
  * @todo: document this function
  */
 Cubiculo::Cubiculo(const Vector3& centro)
{
        posicaoReal = centro;
        //Crio todos os vértices
        for (int x = - 1; x < 2; x+=2)
                for (int y = - 1; y < 2; y+=2)
                        for (int z = - 1; z < 2; z+=2)
                                vertices.push_back(Vector3(x*LADO/2 +(LADO * centro.getX()),
                                                                              y*LADO/2 +(LADO * centro.getY()),
                                                                              z*LADO/2 +(LADO * centro.getZ())));
        rotacionando = false;
}

Cubiculo::~Cubiculo()
{
        //dtor
}


/** @brief ativarFacicula
  *
  * @todo: document this function
  */
void Cubiculo::ativarFacicula(eFaceNome face)
{
        //Crio a facícula que vai ser ativada
        switch (face)
        {
                case eFACENOME_CIMA:
                                faces.push_back(Quadrado(&vertices[2],&vertices[3],&vertices[7],&vertices[6], Color::enumToColor(face))); //Cima
                        break;
                case eFACENOME_FRENTE:
                                faces.push_back(Quadrado(&vertices[1],&vertices[5],&vertices[7],&vertices[3], Color::enumToColor(face))); //Frente
                        break;
                case eFACENOME_ESQUERDA:
                                faces.push_back(Quadrado(&vertices[0],&vertices[1],&vertices[3],&vertices[2], Color::enumToColor(face))); //Esquerda
                        break;
                case eFACENOME_DIREITA:
                                faces.push_back(Quadrado(&vertices[4],&vertices[6],&vertices[7],&vertices[5], Color::enumToColor(face))); //Direita
                        break;
                case eFACENOME_TRAS:
                                faces.push_back(Quadrado(&vertices[0],&vertices[2],&vertices[6],&vertices[4], Color::enumToColor(face))); //Trás
                        break;
                case eFACENOME_BAIXO:
                                faces.push_back(Quadrado(&vertices[0],&vertices[4],&vertices[5],&vertices[1], Color::enumToColor(face))); //Baixo
                        break;
        }
}

/** @brief construir
  *
  * @todo: document this function
  */
void Cubiculo::construir()
{
        //
        for (list<Quadrado>::iterator it = faces.begin(); it != faces.end(); it++)
        {
                addDesenhavel( &*it); //Adiciona todas as facículas como desenhável
        }
}

/** @brief rotacionar
  *
  * @todo: document this function
  */
void Cubiculo::rotacionar(eEixoRotacao eixo, eSentidoRotacao sentido, bool animado, double alfa)
{
        if (!rotacionando)
        {
                rotacionando = true;
                //Adapta alfa ao sentido de rotação
                alfa =  (sentido != eSENTIDOROTACAO_ANTIHORARIO)? alfa: -alfa;
                switch (eixo)
                {
                        case eEIXOROTACAO_X:
                                        angulo.setX(angulo.getX() + alfa);
                                break;
                        case eEIXOROTACAO_Y:
                                        angulo.setY(angulo.getY() + alfa);
                                break;
                        case eEIXOROTACAO_Z:
                                        angulo.setZ(angulo.getZ() + alfa);
                                break;
                }

                if (!animado)
                {
                        //Eu sei que é um código nojento... Mas funciona
                        //Efetivamente, só faz acelerar
                        atualiza(100000);
                }
        }
}

/** @brief atualiza
  *
  * @todo: document this function
  */
void Cubiculo::atualiza(float msecs)
{
        if (rotacionando && !angulo.eIgual(anguloAnimacao))//Verifica necessidade de rotação
        {
                //Aproxima anguloDeAnimação ao angulo normal
                float step = PRINCIPAL->getVelocidadeAngular()*msecs;
                if (angulo.getX() != anguloAnimacao.getX())
                        aproximaAngulosX(step);
                else if (angulo.getY() != anguloAnimacao.getY())
                        aproximaAngulosY(step);
                else if (angulo.getZ() != anguloAnimacao.getZ())
                        aproximaAngulosZ(step);
        }
        else
        {
                if (rotacionando)
                        fimRotacao();
        }
}


/** @brief aproximaAngulosX
  *
  *Aproxima o valor dos ângulos X de animação e o original
  */
void Cubiculo::aproximaAngulosX(float step)
{
        float var = anguloAnimacao.getX();
        if (var != angulo.getX())
        {
                float anguloDeRotacao = transformaEm(var, angulo.getX(), step);
                anguloAnimacao.setX(var);
                Matriz* rotacao = Matriz::RotacaoX(anguloDeRotacao);
                atualizaVertices(rotacao);
        }
}

/** @brief aproximaAngulosZ
  *
  * @todo: document this function
  */
void Cubiculo::aproximaAngulosZ(float step)
{
        float var = anguloAnimacao.getZ();
        if (var != angulo.getZ())
        {
                float anguloDeRotacao = transformaEm(var, angulo.getZ(), step);
                anguloAnimacao.setZ(var);
                Matriz* rotacao = Matriz::RotacaoZ(anguloDeRotacao);
                atualizaVertices(rotacao);
        }
}

/** @brief aproximaAngulosY
  *
  * @todo: document this function
  */
void Cubiculo::aproximaAngulosY(float step)
{
        float var = anguloAnimacao.getY();
        if (var != angulo.getY())
        {
                float anguloDeRotacao = transformaEm(var, angulo.getY(), step);
                anguloAnimacao.setY(var);
                Matriz* rotacao = Matriz::RotacaoY(anguloDeRotacao);
                atualizaVertices(rotacao);
        }
}

/** @brief atualizaVertices
  * Multiplica todos os vértices do cubículo pela matriz (e deleta depois)
  */
void Cubiculo::atualizaVertices(Matriz* matriz)
{
        posicaoReal.multiplicaPor(*matriz);
        for (unsigned int i = 0; i < vertices.size(); ++i)
        {
                vertices[i].multiplicaPor(*matriz);
        }
        delete matriz;
}

/** @brief isRotacionando
  *
  * @todo: document this function
  */
bool Cubiculo::isRotacionando() const
{
        return rotacionando;
}

/** @brief getCentroValorOrdenacao
  *
  * @todo: document this function
  */
float Cubiculo::getCentroValorOrdenacao() const
{
        float retorno = 0;
        retorno += posicaoReal.getX()*100*LADO + posicaoReal.getY()*10*LADO + posicaoReal.getZ()*LADO;
        return retorno;
}

/** @brief fimRotacao
  *
  * @todo: document this function
  */
void Cubiculo::fimRotacao()
{
        //Esse arredondamento é pra utilizar essa posição como índice dos vetores
       posicaoReal.arredondar();
        rotacionando = false;
        //Informo ao Cubo que eu acabei
        PRINCIPAL->getCubo()->reordenarCubiculos();
}

/** @brief getCorAtravesDaFace
  *
  * @todo: document this function
  */
const Color & Cubiculo::getCorAtravesDaFace(eFaceNome facicula) const
{
        //retorno a cor do quadrado da facícula, ou indefinido
        Vector3 normalFaciculaDesejada(facicula);
        for (list<Quadrado>::const_iterator it = faces.begin(); it != faces.end(); it++)
        {
                Vector3* normalFaciculaAtual  = it->getNormal();
                normalFaciculaAtual->arredondar();
                if (normalFaciculaAtual->eIgual(normalFaciculaDesejada))
                {
                        delete normalFaciculaAtual;
                        return it->getColor();
                }
                delete normalFaciculaAtual;
        }
        return Color::Indefinido();
}

/** @brief getFaceAtravesDaCor
  *
  * @todo: document this function
  */
eFaceNome Cubiculo::getFaceAtravesDaCor(const Color& cor) const
{
        for (list<Quadrado>::const_iterator it = faces.begin(); it != faces.end(); it++)
                if (it->getColor() == cor)
                {
                        Vector3* normal = it->getNormal();
                        normal->arredondar();
                        eFaceNome retorno = normal->toFacicula();
                        delete normal;
                        return retorno;
                }
        return eFACENOME_INEXISTENTE;
}


/** @brief getPosicaoNoCubo
  *
  * @todo: document this function
  */
const Vector3& Cubiculo::getPosicaoNoCubo() const
{
        return posicaoReal;
}

/** @brief temCor
  *
  * @todo: document this function
  */
bool Cubiculo::temCor(const Color& c) const
{
        for (list<Quadrado>::const_iterator it = faces.begin(); it != faces.end(); it++)
                if (it->getColor() == c)
                        return true;
        return false;
}

/** @brief getNumFaciculas
  *
  * @todo: document this function
  */
int Cubiculo::getNumFaciculas() const
{
        return faces.size();
}

