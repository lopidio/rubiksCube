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


#include "Vector3.h"
#include <math.h>

#include "Definicoes.h"

Vector3::Vector3():Matriz(3,1)
{
        setX(0);
        setY(0);
        setZ(0);
}

Vector3::Vector3(float x, float y, float z):Matriz(3,1)
{
        setX(x);
        setY(y);
        setZ(z);
}

/** @brief Vector3
  *
  * @todo: document this function
  */
Vector3::Vector3(const Vector3& from, const Vector3& to):Matriz(3,1)
{
        setX(to.getX() - from.getX());
        setY(to.getY() - from.getY());
        setZ(to.getZ() - from.getZ());
}

/** @brief Vector3
  *
  * @todo: document this function
  */
 Vector3::Vector3(eFaceNome face):Matriz(3,1, false)
{
        switch (face)
        {
                case eFACENOME_BAIXO:
                                setY(-1);
                        break;
                case eFACENOME_CIMA:
                                setY(1);
                        break;
                case eFACENOME_ESQUERDA:
                                setX(-1);
                        break;
                case eFACENOME_DIREITA:
                                setX(1);
                        break;
                case eFACENOME_FRENTE:
                                setZ(1);
                        break;
                case eFACENOME_TRAS:
                                setZ(-1);
                        break;
        }
}


Vector3::~Vector3()
{
        //dtor
}


/** @brief norma
  *
  * @todo: document this function
  */
float Vector3::norma() const
{
        float somatorio = 0.000000000000001;//Evitar divisão por 0
        for (unsigned int i = 0; i < linha; ++i)
        {
                float coordenada = getValor(i,0);
                coordenada *= coordenada;
                somatorio += coordenada;
        }
        return sqrt(somatorio);
}

/** @brief normalizar
  *
  * @todo: document this function
  */
void Vector3::normalizar()
{
        float modulo = norma();
        if (modulo==0)
                modulo = 0.000000000000001;
        for (unsigned int i = 0; i < linha; ++i)
                setValor(i, 0, getValor(i,0)/modulo);
}

/** @brief produtoVetorial
  *
  * @todo: document this function
  */
Vector3* Vector3::produtoVetorial(const Vector3& vec) const
{
        Vector3* retorno = new Vector3();
        retorno->setX(      (getY()*vec.getZ())  -     (getZ()*vec.getY())      );
        retorno->setY(      ((getZ()*vec.getX()) -    (getX()*vec.getZ()))     );
        retorno->setZ(      (getX()*vec.getY())  -    (getY()*vec.getX())     );
        return retorno;
}

/** @brief produtoInterno
  *
  * @todo: document this function
  */
float Vector3::produtoInterno(const Vector3& vetor) const
{
        float resultado = 0;
        for (unsigned int i = 0; i < linha; ++i)
                resultado += getValor(i,0)*vetor.getValor(i,0);
        return resultado;
}

/** @brief toGLFloat
  *
  * @todo: document this function
  */
GLfloat* Vector3::toGLfloat() const
{
        GLfloat* retorno = new GLfloat[3];
        for (unsigned int i = 0; i < linha; ++i)
                retorno[i] = getValor(i,0);
        return retorno;
}

float Vector3::getX() const
{
        return  Matriz::getValor(0, 0);
}

void Vector3::setX(float x)
{
        Matriz::setValor(0, 0, x);
}

float Vector3::getY() const
{
        return  Matriz::getValor(1, 0);
}

void Vector3::setY(float y)
{
        Matriz::setValor(1, 0, y);
}

float Vector3::getZ() const
{
        return  Matriz::getValor(2, 0);
}

void Vector3::setZ(float z)
{
        Matriz::setValor(2, 0, z);
}


/** @brief multiplicaPor
  *  (3x1)t x (3x3) = 3x1
  */
void Vector3::multiplicaPor(const Matriz& matriz)
{
        if (linha == matriz.getLinha())
        {
                Vector3* nova = new Vector3(*this);
                for (unsigned int j = 0; j < 3; ++j) //coluna da matriz
                {
                        float somatorio = 0;
                        for (unsigned int i = 0; i < 3; ++i) //linha da matriz
                        {
                                somatorio+= nova->getValor(i,0)* matriz.getValor(i,j);
                        }
                        setValor(j,0, somatorio);
                }
                delete nova;
        }
}


/** @brief eIgual
  *
  * @todo: document this function
  */
bool Vector3::eIgual(const Vector3& outro) const
{
        return (getX() == outro.getX() && getY() == outro.getY() && getZ() == outro.getZ());
}



/** @brief arredondar
  *
  * @todo: document this function
  */
void Vector3::arredondar()
{
        float x = getX();
        if (x > 0.5)
               setX(1);
        else if (x < -0.5)
                setX(-1);
        else
                setX(0);

        float y = getY();
        if (y > 0.5)
               setY(1);
        else if (y < -0.5)
                setY(-1);
        else
                setY(0);

        float z = getZ();
        if (z > 0.5)
               setZ(1);
        else if (z < -0.5)
                setZ(-1);
        else
                setZ(0);
}

/** @brief projetar
  *
  * @todo: document this function
  */
Vector3* Vector3::projetar(const Vector3& b) const
{
        float moduloB = b.norma();
        moduloB *= moduloB;
        float produto = this->produtoInterno(b);
        produto /= moduloB;
        Vector3* retorno = new Vector3();
        retorno->setX(b.getX()*produto);
        retorno->setY(b.getY()*produto);
        retorno->setZ(b.getZ()*produto);
        return retorno;
}

/** @brief toFacicula
  *
  * @todo: document this function
  */
eFaceNome Vector3::toFacicula() const
{
        if (eIgual(Vector3(1,0,0)))
                return eFACENOME_DIREITA;
        if (eIgual(Vector3(-1,0,0)))
                return eFACENOME_ESQUERDA;
        if (eIgual(Vector3(0,1,0)))
                return eFACENOME_CIMA;
        if (eIgual(Vector3(0,-1,0)))
                return eFACENOME_BAIXO;
        if (eIgual(Vector3(0,0,1)))
                return eFACENOME_FRENTE;
        if (eIgual(Vector3(0,0,-1)))
                return eFACENOME_TRAS;
        return eFACENOME_INEXISTENTE;
}

