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


#include "Device.h"
#include "Definicoes.h"
#include "AAlgoritmo.h" //Provisório
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Device::Device()
{
        srand ( time(NULL) );
        display = new Display(); //Alocando o display
        initialize();
}

/** @brief ~Device
  *
  * @todo: document this function
  */
 Device::~Device()
{
        destroy();
}



/** @brief getInstancia
  *
  * @todo: document this function
  */
Device & Device::getInstancia()
{
        static Device singleton; //Massa, né?
        return singleton;
}

void addLight()
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={5.0, 5.0, 5.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
}

/** @brief Inicializar
  *
  * @todo: document this function
  */
void Device::initialize()
{
        eventHandler(); //Cadastra as funções de evento

        addLight();

        /* setar a largura da linha em pixels */
        glLineWidth(3.0);

}

/** @brief Run
  *
  * @todo: document this function
  */
void Device::run()
{
        //instancia o principal
        principal = Principal::getInstancia();
        glutMainLoop();
}

/** @brief getDisplay
  *
  * @todo: document this function
  */
Display & Device::getDisplay()
{
        return *display;
}

/** @brief EventHandler
  *
  * @todo: document this function
  */
void Device::eventHandler()
{
        /* registrar os tratadores de eventos */
        glutDisplayFunc(DisplayEvent);
        glutReshapeFunc(ReshapeEvent);
        glutKeyboardFunc(KeyboardEvent);
        glutTimerFunc(UPDATE_TIMER, UpdateEvent, UPDATE_TIMER);
}

/** @brief Destroy
  *
  * @todo: document this function
  */
void Device::destroy()
{
        delete display;
        display = NULL;
}

/** @brief KeyboardEvent
  *
  * @todo: document this function
  */
void Device::KeyboardEvent(unsigned char key, int x, int y)
{
        Cubo* cubo = PRINCIPAL->getCubo();

        if (key == 'p')
        {
                PRINCIPAL->criarAlgoritmo();
                return;
        }


        Cubo::Rotacao rot;
        rot.animado = true;
        rot.sentido = eSENTIDOROTACAO_HORARIO;
        rot.rotacaoFace = true;
        switch (key)
        {
                case 'a':
                                rot.face = eFACENOME_ESQUERDA;
                        break;
                case 's':
                                rot.face = eFACENOME_FRENTE;
                        break;
                case 'd':
                                rot.face = eFACENOME_DIREITA;
                        break;
                case 'w':
                                rot.face = eFACENOME_CIMA;
                        break;
                case 'x':
                                rot.face = eFACENOME_BAIXO;
                        break;
                case 'c':
                                rot.face = eFACENOME_TRAS;
                        break;
                case 'u':
                                rot.rotacaoFace = false;
                                rot.eixo = eEIXOROTACAO_X;
                                cubo->addRotacaoTodo(rot);
                                return;
                case 'i':
                                rot.rotacaoFace = false;
                                rot.eixo = eEIXOROTACAO_Y;
                                cubo->addRotacaoTodo(rot);
                                return;
                case 'm':
                                AAlgoritmo::Embaralhar(cubo, false);
                                delete PRINCIPAL->algoritmo;
                                PRINCIPAL->algoritmo = NULL;
                                return;
                case 27:
                        exit(0);
                        return;
                default:
                        return;
        }
        delete PRINCIPAL->algoritmo;
        PRINCIPAL->algoritmo = NULL;
        cubo->addRotacaoFace(rot);
}

/** @brief ReshapeEvent
  *
  * @todo: document this function
  */
void Device::ReshapeEvent(int width, int height)
{
        DISPLAY.setViewPort(width, height);
        Device::getInstancia().getDisplay().reshape();
}

/** @brief DisplayEvent
  *
  * @todo: document this function
  */
void Device::DisplayEvent()
{
        Device::getInstancia().getDisplay().drawAll();

}


/** @brief UpdateEvent
  *
  * @todo: document this function
  */
void Device::UpdateEvent(int value)
{
        float msecs = (float)value/1000;
        PRINCIPAL->atualiza(msecs);

        /* forçar um evento para ativar o redesenho */
        glutPostRedisplay();
        //Cadastro a mesma função pra ser chamada novamente!
        glutTimerFunc(UPDATE_TIMER, UpdateEvent, UPDATE_TIMER);
}


