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


#include "Matriz.h"
#include <math.h>

#include "Definicoes.h"

Matriz::Matriz(unsigned int lin,unsigned int col, bool identidade):linha(lin), coluna(col)
{
        valores = new float*[linha];
        for (unsigned int i = 0; i < linha; ++i)
                valores[i] = new float[coluna];

//Zerando todos os valores
        for (unsigned int i = 0; i < linha; ++i)
                for (unsigned int j = 0; j < coluna; ++j)
                         valores[i][j] = identidade  && (i==j);
}

/** @brief Matriz
  * Construtor de cópia
  */
 Matriz::Matriz(const Matriz& matriz):linha(matriz.linha), coluna(matriz.coluna)
{
        valores = new float*[linha];
        for (unsigned int i = 0; i < linha; ++i)
                valores[i] = new float[coluna];

        //Copiando todos os valores
        for (unsigned int i = 0; i < linha; ++i)
                for (unsigned int j = 0; j < coluna; ++j)
                        valores[i][j] = matriz.valores[i][j];
}

Matriz::~Matriz()
{
        destruir();
}


/** @brief rotacaoZ
  *
  * @todo: document this function
  */
Matriz* Matriz::RotacaoX(double alpha)
{
        Matriz* retorno = 0;
        retorno = new Matriz(3,3, true);
        retorno->setValor(1, 1, cos(alpha));
        retorno->setValor(1, 2, -sin(alpha));
        retorno->setValor(2, 1, sin(alpha));
        retorno->setValor(2, 2, cos(alpha));
        return retorno;
}

/** @brief rotacaoY
  *
  * @todo: document this function
  */
Matriz* Matriz::RotacaoY(double alpha)
{
        Matriz* retorno = 0;
        retorno = new Matriz(3,3, true);
        retorno->setValor(0, 0, cos(alpha));
        retorno->setValor(0, 2, sin(alpha));
        retorno->setValor(2, 0, -sin(alpha));
        retorno->setValor(2, 2, cos(alpha));
        return retorno;
}

/** @brief rotacaoX
  *
  * @todo: document this function
  */
Matriz* Matriz::RotacaoZ(double alpha)
{
        Matriz* retorno = 0;
        retorno = new Matriz(3,3, true);
        retorno->setValor(0, 0, cos(alpha));
        retorno->setValor(0, 1, -sin(alpha));
        retorno->setValor(1, 0, sin(alpha));
        retorno->setValor(1, 1, cos(alpha));
        return retorno;
}

/** @brief operator+
  *
  * @todo: document this function
  */
Matriz * Matriz::operator+(const Matriz& matriz) const
{
        Matriz* nova = new Matriz(*this);
        if (coluna == matriz.getColuna() && linha == matriz.getLinha())
                for (unsigned int i = 0; i < linha; ++i)
                        for (unsigned int j = 0; j < coluna; ++j)
                                nova->valores[i][j] = valores[i][j] + matriz.valores[i][j];
        return nova;
}


/** @brief operator-
  *
  * @todo: document this function
  */
Matriz * Matriz::operator-(const Matriz& matriz) const
{
        Matriz* nova = new Matriz(*this);
        if (coluna == matriz.getColuna() && linha == matriz.getLinha())
                for (unsigned int i = 0; i < linha; ++i)
                        for (unsigned int j = 0; j < coluna; ++j)
                                nova->valores[i][j] = valores[i][j] - matriz.valores[i][j];
        return nova;
}

/** @brief operator*
  *
  * @todo: document this function
  */
Matriz * Matriz::operator*(const Matriz& matriz) const
{
        Matriz* nova = new Matriz(*this);
        if (coluna == matriz.linha)
        {
                for (unsigned int i = 0; i < nova->linha; ++i)
                        for (unsigned int j = 0; j < matriz.coluna; ++j)
                        {
                                float somatorio = 0;
                                for (unsigned int k = 0; k < nova->coluna; ++k)
                                        somatorio += valores[i][k]*matriz.valores[k][j];
                                nova->valores[i][j] = somatorio;
                        }
                delete nova;
        }
        return nova;
}

/** @brief operator*
  *
  * @todo: document this function
  */
Matriz * Matriz::operator*(float k) const
{
        Matriz* nova = new Matriz(*this);
        for (unsigned int i = 0; i < linha; ++i)
                for (unsigned int j = 0; j < coluna; ++j)
                {
                        nova->valores[i][j] = valores[i][j] * k;
                }
        return nova;
}



/** @brief operator=
  *
  * @todo: document this function
  */
Matriz & Matriz::operator=(const Matriz& matriz)
{
        if (linha == matriz.linha && coluna == matriz.coluna)
        {
                //Copiando todos os valores
                for (unsigned int i = 0; i < linha; ++i)
                        for (unsigned int j = 0; j < coluna; ++j)
                                valores[i][j] = matriz.valores[i][j];
        }
        return *this;
}

/** @brief getVectorLinha
  *
  * @todo: document this function
  */
Matriz*  Matriz::getVectorLinha(unsigned int lin) const
{
        if (lin >= 0 && lin < linha)
        {
                Matriz* retorno = new Matriz(coluna, 1);
                for (unsigned int j = 0; j < coluna; ++j)
                        retorno->valores[0][j] = valores[lin][j];
                return retorno;
        }
        return 0;
}

/** @brief getVectorColuna
  *
  * @todo: document this function
  */
Matriz* Matriz::getVectorColuna(unsigned int col) const
{
        if (col >= 0 && col < coluna)
        {
                Matriz* retorno = new Matriz(linha, 1);
                for (unsigned int i = 0; i < linha; ++i)
                        retorno->valores[i][0] = valores[i][col];
                return retorno;
        }
        return 0;
}

/** @brief getColuna
  *
  * @todo: document this function
  */
unsigned int Matriz::getColuna() const
{
        return coluna;
}

/** @brief getLinha
  *
  * @todo: document this function
  */
unsigned int Matriz::getLinha() const
{
        return linha;
}

/** @brief setValor
  *
  * @todo: document this function
  */
void Matriz::setValor(unsigned int lin, unsigned int col, float valor)
{
        if (lin >= 0 && lin < linha && col >= 0 && col < coluna)
                valores[lin][col] = valor;
}
/** @brief diminuirDimensao
  *
  * @todo: document this function
  */
Matriz* Matriz::diminuirDimensao()
{
        Matriz matriz(*this);
        destruir();
        --linha;
        --coluna;

        valores = new float*[linha];
        for (unsigned int i = 0; i < linha; ++i)
                valores[i] = new float[coluna];

        //Copiando todos os valores
        for (unsigned int i = 0; i < linha; ++i)
                for (unsigned int j = 0; j < coluna; ++j)
                        valores[i][j] = matriz.valores[i][j];
        return this;
}

/** @brief aumentarDimensao
  *
  * @todo: document this function
  */
Matriz* Matriz::aumentarDimensao()
{
        Matriz matriz(*this);
        destruir();
        ++linha;
        ++coluna;

        valores = new float*[linha];
        for (unsigned int i = 0; i < linha; ++i)
                valores[i] = new float[coluna];

        //Copiando todos os valores
        for (unsigned int i = 0; i < linha - 1; ++i)
                for (unsigned int j = 0; j < coluna - 1; ++j)
                        valores[i][j] = matriz.valores[i][j];

        //Setando os valores recém criados
        for (unsigned int i = 0; i < linha - 1; ++i)
                valores[i][coluna - 1] = 0;

        for (unsigned int j = 0; j < coluna - 1; ++j)
                valores[linha - 1][j] = 0;

        valores[linha - 1][coluna - 1] = 1;
        return this;
}

/** @brief getValor
  *
  * @todo: document this function
  */
float Matriz::getValor(unsigned int lin, unsigned int col) const
{
        if (lin >= 0 && lin < linha && col >= 0 && col < coluna)
                return valores[lin][col];
}

/** @brief destruir
  *
  * @todo: document this function
  */
void Matriz::destruir()
{
        for (unsigned int i = 0; i < linha; ++i)
                delete[] valores[i];
        delete[] valores;
        valores = 0;
}

/** @brief print
  *
  * @todo: document this function
  */
void Matriz::print() const
{
        printf("--------------   %d    x     %d\n", linha, coluna);
        for (unsigned int i = 0; i < linha; ++i)
        {
                for (unsigned int j = 0; j < coluna; ++j)
                        printf("%f,  ", valores[i][j]);
                printf("\n");
        }
}

/** @brief transformacaoAfim
  *
  * @todo: document this function
  */
void Matriz::transformacaoAfim(const Matriz& matriz, float alfa)
{
        if (matriz.linha == linha && matriz.coluna == coluna)
        {
                float beta = 1 - alfa;
                Matriz* outraModificada = matriz*beta;
                Matriz* euModificada = (*this)*alfa;
                Matriz* resultado = *euModificada + *outraModificada;

                //Copiar o resultado em mim
                //Copiando todos os valores
                for (unsigned int i = 0; i < linha; ++i)
                        for (unsigned int j = 0; j < coluna; ++j)
                                valores[i][j] = resultado->valores[i][j];

                delete outraModificada;
                delete euModificada;
                delete resultado;
        }
}


