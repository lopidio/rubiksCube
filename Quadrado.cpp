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


#include "Quadrado.h"
#include "Definicoes.h"

Quadrado::Quadrado()
{
        //Construtor default!
        //NÃO USAR!
}

/** @brief Quadrado
  *
  * @todo: document this function
  */
 Quadrado::Quadrado(const Vector3* a, const Vector3* b, const Vector3* c, const Vector3* d, const Color& cor_)
{
        //Adicionando os vértices à lista
        vertices.push_back(a);
        vertices.push_back(b);
        vertices.push_back(c);
        vertices.push_back(d);
        cor = cor_;
}


Quadrado::~Quadrado()
{
        //dtor
}


#include "Device.h"
/** @brief draw
  *
  * @todo: document this function
  */
void Quadrado::desenha() const
{
        //Ajeitar esse método!
        glBegin(GL_QUADS);
        list<Vector3> verticesProvisorios;
        Vector3* centro = getCentroide();
        bool faceEscondida = ( centro->getX() <= -3*Cubiculo::LADO/2 ||
                                                centro->getY() <= -3*Cubiculo::LADO/2 ||
                                                centro->getZ() <= -3*Cubiculo::LADO/2  );
        delete centro;
        for (list<const Vector3*>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
        {
                float x = (*it)->getX();
                float y = (*it)->getY();
                float z = (*it)->getZ();
                if (faceEscondida)
                {
                        y -= 4*Cubiculo::LADO;
                        x += 4*Cubiculo::LADO;
                }
                verticesProvisorios.push_back(Vector3(x,y,z));
        }


        for (list<Vector3>::iterator it = verticesProvisorios.begin(); it != verticesProvisorios.end(); it++)
        {
                //Fazendo algumas brincadeiras só pra testas os reflexos
                GLfloat* temp = it->toGLfloat();
                //Normal de uma esfera
                Vector3 esfera = *it;
                esfera.normalizar();

                //Normal da face
                centro = getCentroide();
                centro->normalizar();

                //Cabe uma brincadeira com essa constante aqui..
                //Essa é a normal de cada vértice do cubículo
                centro->transformacaoAfim(esfera, 0.2);

                GLfloat* normalGL = centro->toGLfloat();
                glNormal3fv(normalGL);
                glVertex3fv(temp);

                delete[] normalGL;
                delete[] temp;
        }
        glEnd();

        desenhaContorno();

}

/** @brief desenhaContorno
  *
  * @todo: document this function
  */
void Quadrado::desenhaContorno() const
{
        list<Vector3> verticesProvisorios;
        Vector3* centro = getCentroide();
        bool faceEscondida = ( centro->getX() <= -3*Cubiculo::LADO/2 ||
                                                centro->getY() <= -3*Cubiculo::LADO/2 ||
                                                centro->getZ() <= -3*Cubiculo::LADO/2  );
        delete centro;
        for (list<const Vector3*>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
        {
                float x = (*it)->getX();
                float y = (*it)->getY();
                float z = (*it)->getZ();
                if (faceEscondida)
                {
                        y -= 4*Cubiculo::LADO;
                        x += 4*Cubiculo::LADO;
                }
                verticesProvisorios.push_back(Vector3(x,y,z));
        }

        glBegin(GL_LINE_LOOP);
        DISPLAY.setColor(Color::Cinza());
        for (list<Vector3>::iterator it = verticesProvisorios.begin(); it != verticesProvisorios.end(); it++)
        {
                GLfloat* temp = it->toGLfloat();
                glVertex3fv(temp);
                delete[] temp;
        }
        glEnd();
}




Vector3* Quadrado::getCentroide() const
{
        Vector3* retorno = new Vector3();
        Vector3 somatorio;
        for (list<const Vector3*>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
        {
                //eu sei que tá gambioso, mas foi o melhor que eu consegui
                somatorio.setX((*it)->getX() + somatorio.getX());
                somatorio.setY((*it)->getY() + somatorio.getY());
                somatorio.setZ((*it)->getZ() + somatorio.getZ());
        }
        retorno->setX(somatorio.getX()/3);
        retorno->setY(somatorio.getY()/3);
        retorno->setZ(somatorio.getZ()/3);
        return retorno;
}

Vector3* Quadrado::getNormal() const
{
        //Pego três vértices
        list<const Vector3*>::const_iterator c = vertices.begin();
        list<const Vector3*>::const_iterator a = c++;
        list<const Vector3*>::const_iterator b = c++;

        //Transformo em dois vetores
        Vector3 ab(**a,**b);
        Vector3 bc (**b,**c);

        //Calculo o produto vetorial
        Vector3* retorno = ab.produtoVetorial(bc);
        retorno->normalizar();
        return  retorno; //Essa é a normal original
}
