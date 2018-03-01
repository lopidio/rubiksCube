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
#include "Display.h"

Display::Display()
{
        int i = 1; //Famoso jabuti trepado na árvore
        char* oi = "Nome qualquer";

        /* estabelecimento de comunicacao com o sistema de janela */
        glutInit(&i, &oi);
        /* setar o " visual" do display */

        glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
        /* definir a janela */
        glutInitWindowSize (800, 600);
        glutInitWindowPosition (100, 100);
        glutCreateWindow ("Projeto Final");
        glEnable( GL_DEPTH_TEST );

        reshape();
}

Display::~Display()
{
}

/** @brief addDesenhavel
  *
  * @todo: document this function
  */
void Display::addDesenhavel(const Desenhavel* des)
{
        lista.push_back(des);
}

void desenhaTexto()
{
        char* string = new char[20];
        for (int i = 0; i < 20; ++i)
                string[i] = i + 40;
  	glPushMatrix();
        // Posição no universo onde o texto será colocado
        glRasterPos2f(20,20);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++);
	glPopMatrix();
}

/** @brief drawAll
  *
  * @todo: document this function
  */
void Display::drawAll()
{
        /* "CLEAR" o display */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);

        desenhaTexto();

        for (list<const Desenhavel*>::iterator it = lista.begin(); it != lista.end(); it++)
                (*it)->desenhaTudo();
        glutSwapBuffers();
}


/** @brief setColor
  *
  * @todo: document this function
  */
void Display::setColor(const Color& cor) const
{
        glColor3f(cor.getR(), cor.getG(), cor.getB());
}

/** @brief reshape
  *
  * @todo: document this function
  */
void Display::reshape()
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(50,(GLfloat)widthGLPort/(GLfloat)heightGLPort,0.4,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

        //Atualiza a camera
        gluLookAt (15,15,15,
                                0,0,0,
                                0.0, 1.0, 0.0);}

/** @brief setViewPort
  *
  * @todo: document this function
  */
void Display::setViewPort(int width, int height)
{
        widthGLPort = width;
        heightGLPort = height;
}



