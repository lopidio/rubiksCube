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


#include "Principal.h"
#include "Device.h"
#include "Display.h"
#include <stdio.h>

Principal* Principal::instancia = NULL;

Principal::Principal()
{
        algoritmo = NULL;
        velocidadeAngular = M_PI*2; //Radianos/segundo
        cubo = new Cubo();
        DISPLAY.addDesenhavel(cubo);
}

Principal::~Principal()
{
        delete algoritmo;
        delete cubo;
}

/** @brief getInstancia
  *
  * @todo: document this function
  */
Principal * Principal::getInstancia()
{
        if (!instancia)
                instancia = new Principal();
        return instancia;
}

/** @brief temporario
  *
  * @todo: document this function
  */
void Principal::atualiza(float msecs)
{
        if (algoritmo)
                algoritmo->atualiza();
        cubo->atualiza(msecs);
}


/** @brief getCubo
  *
  * @todo: document this function
  */
Cubo* Principal::getCubo() const
{
        return cubo;
}

/** @brief getVelocidadeAngular
  *
  * @todo: document this function
  */
float Principal::getVelocidadeAngular() const
{
        return velocidadeAngular;
}

/** @brief criarAlgoritmo
  *
  * @todo: document this function
  */
void Principal::criarAlgoritmo()
{
        if (algoritmo)
                delete algoritmo;
        algoritmo = AAlgoritmo::Fabrica(eALGORITMOID_F2L, cubo);
        algoritmo->executa();
}

