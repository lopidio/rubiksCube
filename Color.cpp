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


#include "Color.h"
#include <stdio.h>

void Color::print() const
{
        printf("Color  r:%.2f, g:%.2f, b:%.2f\n", r, g, b);
}

Color::Color()
{
        //ctor
}

/** @brief Color
  *
  * @todo: document this function
  */
 Color::Color(float r_, float g_, float b_):r(r_), g(g_), b(b_)
{
}

/** @brief Color
  *
  * @todo: document this function
  */
 Color::Color(const Color& cor):r(cor.r), g(cor.g), b(cor.b)
{
}

Color::~Color()
{
        //dtor
}

/** @brief Indefinido
  *
  * @todo: document this function
  */
const Color & Color::Indefinido()
{
        static Color indefinido(0.1,0.1,0.1);
        return indefinido;
}

/** @brief getB
  *
  * @todo: document this function
  */
float Color::getB() const
{
        return b;
}

/** @brief getG
  *
  * @todo: document this function
  */
float Color::getG() const
{
        return g;
}

/** @brief getR
  *
  * @todo: document this function
  */
float Color::getR() const
{
        return r;
}

/** @brief Cinza
  *
  * @todo: document this function
  */
const Color & Color::Cinza()
{
        static Color indefinido(0.4,0.4,0.4);
        return indefinido;
}


/** @brief Laranja
  *
  * @todo: document this function
  */
const Color & Color::Laranja()
{
        static Color indefinido(1,0.6,0);
        return indefinido;
}

/** @brief Verde
  *
  * @todo: document this function
  */
const Color & Color::Verde()
{
        static Color indefinido(0,1,0);
        return indefinido;
}

/** @brief Azul
  *
  * @todo: document this function
  */
const Color & Color::Azul()
{
        static Color indefinido(0,0,1);
        return indefinido;
}

/** @brief Amarelo
  *
  * @todo: document this function
  */
const Color & Color::Amarelo()
{
        static Color indefinido(1,1,0);
        return indefinido;
}

/** @brief Branco
  *
  * @todo: document this function
  */
const Color & Color::Branco()
{
        static Color indefinido(1,1,1);
        return indefinido;
}

/** @brief Vermelho
  *
  * @todo: document this function
  */
const Color & Color::Vermelho()
{
        static Color indefinido(1,0,0);
        return indefinido;
}

//Cores iniciais do cubo
const Color& Color::enumToColor(eFaceNome face)
{
        if (face == eFACENOME_CIMA)
                return Branco(); //Cima
        if (face == eFACENOME_FRENTE)
                return Vermelho(); //Frente
        if (face == eFACENOME_ESQUERDA)
                return Azul(); //Esquerda
        if (face == eFACENOME_DIREITA)
                return Verde(); //Direita
        if (face == eFACENOME_TRAS)
                return Laranja(); //Trás
        if (face == eFACENOME_BAIXO)
                return Amarelo(); //baixo
        return Indefinido();
}


/** @brief operator==
  *
  * @todo: document this function
  */
bool Color::operator==(const Color& c) const
{
        return r == c.r && g == c.g && b == c.b;
}
