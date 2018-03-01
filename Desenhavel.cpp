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


#include "Desenhavel.h"
#include "Definicoes.h"
#include "Device.h"
#include <stdio.h>

Desenhavel::Desenhavel()
{
        cor = Color::Indefinido();
}

Desenhavel::~Desenhavel()
{
}


/** @brief remove
  *
  * @todo: document this function
  */
void Desenhavel::removeDesenhavel(const Desenhavel* x)
{
       filhos.remove(x);
}

/** @brief add
  *
  * @todo: document this function
  */
void Desenhavel::addDesenhavel(const Desenhavel* x)
{
        filhos.push_back(x);
}

/** @brief getNumFilhos
  *
  * @todo: document this function
  */
unsigned int Desenhavel::getNumFilhos() const
{
        return filhos.size();
}



/** @brief desenhaTudo
  *
  * @todo: document this function
  */
void Desenhavel::desenhaTudo() const
{
        for (list<const Desenhavel*>::const_iterator it = filhos.begin(); it != filhos.end(); it++)
                (*it)->desenhaTudo();
        DISPLAY.setColor(cor);
        this->desenha();
}

/** @brief getColor
  *
  * @todo: document this function
  */
const Color & Desenhavel::getColor() const
{
        return cor;
}

/** @brief setColor
  *
  * @todo: document this function
  */
void Desenhavel::setColor(const Color& color)
{
        cor = color;
}

/** @brief desenha
  *
  * @todo: document this function
  */
void Desenhavel::desenha() const
{
        //hook
}

