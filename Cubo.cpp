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


#include "Cubo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Cubo::Cubo()
{
        //Alocando todos os cubículos

        //Sim, o cubículo central é criado.. Mas na hora de construir, ele é 'praticamente' destruído
        for (int x = 0; x < 3; ++x)
                for (int y = 0; y < 3; ++y)
                        for (int z = 0; z < 3; ++z)
                        {
                                cubiculos[x][y][z] = new Cubiculo(Vector3(x-1,y-1,z-1));
                        }

        //Alocando Faces
        faces = new Face*[6];
        for (int  face = 0; face < 6; ++face)
        {
                eFaceNome faceNome = (eFaceNome)face;
                faces[face] = new Face(faceNome, cubiculos);
        }

        //Só posso construir depois de criar as faces, pq agora eles sabem de quais facículas eles vão precisar!
        for (int x = 0; x < 3; ++x)
                for (int y = 0; y < 3; ++y)
                        for (int z = 0; z < 3; ++z)
                        {
                                cubiculos[x][y][z]->construir();
                                addDesenhavel(cubiculos[x][y][z]);
                        }
}

Cubo::~Cubo()
{
        //deletar tudo!!

        //Deletar faces
        for (int  face = 0; face < 6; ++face)
                delete faces[face];
        delete[] faces;
        faces = NULL;


        //deletando cubículos
        for (int x = 0; x < 3; ++x)
                for (int y = 0; y < 3; ++y)
                        for (int z = 0; z < 3; ++z)
                                        delete cubiculos[x][y][z];
}

/** @brief atualiza
  *
  * @todo: document this function
  */
void Cubo::atualiza(float msecs)
{
        //Atualizo todos os cubículos
        for (int x = 0; x < 3; ++x)
                for (int y = 0; y < 3; ++y)
                        for (int z = 0; z < 3; ++z)
                        {
                                cubiculos[x][y][z]->atualiza(msecs);
                        }
        verificaNecessidadeDeRotacao();
}

/** @brief rotacionarTodo
  *
  * @todo: document this function
  */
void Cubo::addRotacaoTodo(const Rotacao& rot, double alfa)
{
        filaRotacoes.push_back(rot);
}

/** @brief rotacionarFace
  *
  * @todo: document this function
  */
void Cubo::addRotacaoFace(const Rotacao& rot, double alfa)
{
        filaRotacoes.push_back(rot);
}

/** @brief executarRotacaoFace
  *
  * @todo: document this function
  */
void Cubo::executarRotacaoFace(const Rotacao& rot)
{
        faces[rot.face]->rotaciona(rot.sentido, rot.animado);
}

/** @brief executarRotacaoTodo
  *
  * @todo: document this function
  */
void Cubo::executarRotacaoTodo(const Rotacao& rot)
{
        //Rotaciona todos os cubos independente das faces!
        for (int x = 0; x < 3; ++x)
                for (int y = 0; y < 3; ++y)
                        for (int z = 0; z < 3; ++z)
                        {
                                cubiculos[x][y][z]->rotacionar(rot.eixo, rot.sentido, rot.animado);
                        }
}


/** @brief getFace
  *
  * @todo: document this function
  */
const Face* Cubo::getFace(eFaceNome face) const
{
        return faces[face];
}

//Função utilizada para ordenar os cubículos
bool comparaCubiculos(Cubiculo* a, Cubiculo*b)
{
        return a->getCentroValorOrdenacao() < b->getCentroValorOrdenacao();
}

/** @brief reordenarCubiculos
  *
  * @todo: document this function
  */
void Cubo::reordenarCubiculos()
{
        if (!estaRotacionando()) //Se ainda tá rolando alguma rotação
        {
                //Pego os valores dos cubículos
                list<Cubiculo*> lista;
                for (int x = 0; x < 3; ++x)
                        for (int y = 0; y < 3; ++y)
                                for (int z = 0; z < 3; ++z)
                                {
                                        lista.push_back(cubiculos[x][y][z]);
                                }

                //Ordeno de acordo com a posição
                lista.sort(comparaCubiculos);

                //Transfiro os valores de volta
                for (int x = 0; x < 3; ++x)
                        for (int y = 0; y < 3; ++y)
                                for (int z = 0; z < 3; ++z)
                                {
                                        cubiculos[x][y][z] = lista.front();
                                        lista.pop_front();
                                }

                //Informo às faces que houve a mudança
                for (int  face = 0; face < 6; ++face)
                        faces[face]->capturarRespectivosCubiculos(cubiculos);

                verificaNotificacoes();
        }
}

void Cubo::verificaNecessidadeDeRotacao()
{
        /** @todo  se tou rotacionando o lado oposto
                Existe uma variável de classe chamada rotacaoFaces[] && roptacaoTodo.. Ler
        */
        //Informo aos observadores que eu tou pronto pro próximo
        if (filaRotacoes.size() > 0 && !estaRotacionando())
        {
                Rotacao rot = filaRotacoes.front();
                filaRotacoes.pop_front();
                if (rot.rotacaoFace)
                {
                        executarRotacaoFace(rot);
                        if (filaRotacoes.size() > 0){ //Verifica se a próxima rotação é o lado oposto
                                Rotacao rot2  = filaRotacoes.front();
                                //São lados opostos
                                if (rot2.rotacaoFace && rot2.face + rot.face == 5)
                                {
                                        filaRotacoes.pop_front();
                                        executarRotacaoFace(rot2);
                                }

                        }
                }
                else
                        executarRotacaoTodo(rot);
        }
}

/** @brief verificaNotificacoes
  *
  * @todo: document this function
  */
void Cubo::verificaNotificacoes()
{
        bool fimRotacoes =  filaRotacoes.size() == 0;
        bool resolvido = estaResolvido();
        for (list<ICuboObserver*>::iterator it = observers.begin(); it != observers.end(); it++)
        {
                if (fimRotacoes)
                {
                        (*it)->onFimCuboRotacoes(this);
                }
                if (resolvido)
                {
                        (*it)->onCuboCompleto();
                }
        }
}


/** @brief getCubiculo
  *
  * @todo: document this function
  */
const Cubiculo* Cubo::getCubiculo(int x, int y, int z) const
{
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && z >=0 && z < 3)
                return cubiculos[x][y][z];
        return NULL;
}


/** @brief getCubiculoCentroDeCor
  *
  * @todo: document this function
  */
const Cubiculo* Cubo::getCubiculoCentroDeCor(const Color& c) const
{
        for (int x = 0; x < 3; ++x)
                for (int y = 0; y < 3; ++y)
                        for (int z = 0; z < 3; ++z)
                                if (cubiculos[x][y][z]->temCor(c) && cubiculos[x][y][z]->getNumFaciculas() == 1)
                                        return cubiculos[x][y][z];
        return NULL;
}

/** @brief getCubiculoLadoDeCor
  *
  * @todo: document this function
  */
const Cubiculo* Cubo::getCubiculoLadoDeCor(const Color& c1,const Color& c2) const
{
        if (c1 == c2)
                return NULL;

        for (int x = 0; x < 3; ++x)
                for (int y = 0; y < 3; ++y)
                        for (int z = 0; z < 3; ++z)
                                if (cubiculos[x][y][z]->getNumFaciculas() == 2)
                                {
                                        if (cubiculos[x][y][z]->temCor(c1) && cubiculos[x][y][z]->temCor(c2))
                                                return cubiculos[x][y][z];
                                }
        return NULL;

}

/** @brief getCubiculoQuinaDeCor
  *
  * @todo: document this function
  */
const Cubiculo* Cubo::getCubiculoQuinaDeCor(const Color& c1,const Color& c2,const Color& c3) const
{
        if (c1 == c2 || c2 == c3 || c1 == c3)
                return NULL;

        for (int x = 0; x < 3; ++x)
                for (int y = 0; y < 3; ++y)
                        for (int z = 0; z < 3; ++z)
                                if (cubiculos[x][y][z]->getNumFaciculas() == 3)
                                {
                                        if (cubiculos[x][y][z]->temCor(c1) && cubiculos[x][y][z]->temCor(c2) &&
                                                        cubiculos[x][y][z]->temCor(c3))
                                                return cubiculos[x][y][z];
                                }
        return NULL;
}

/** @brief estaResolvido
  *
  * @todo: document this function
  */
bool Cubo::estaResolvido() const
{
        //Enquanto está rotacionando, pode haver erro ns cálculos
        if (estaRotacionando())
                return false;
        for (int i = 0; i < 6; ++i)
                if (!faces[i]->estaCompleta())
                        return false;
        return true;
}

/** @brief removeObserver
  *
  * @todo: document this function
  */
void Cubo::removeObserver(ICuboObserver* observer)
{
        observers.remove(observer);
}

/** @brief addObserver
  *
  * @todo: document this function
  */
void Cubo::addObserver(ICuboObserver* observer)
{
        observers.push_back(observer);
}


void Cubo::Rotacao::criarAleatoriamente()
{
        //Crio os passos de um algoritmo aleatoriamente
        rotacaoFace = (rand()%10)%2;

        int sentidoInt = rand()%2;
        sentido = sentidoInt?eSENTIDOROTACAO_HORARIO:eSENTIDOROTACAO_ANTIHORARIO;
        //Torno aeatório o tipo do movimento
        if (rotacaoFace)
        {
                int faceInt = rand()%6;
                face = (eFaceNome)faceInt;
        }
        else
        {
                int eixoInt = rand()%3;
                eixo = (eEixoRotacao)eixoInt;
        }
}

/** @brief estaRotacionando
  *
  * @todo: document this function
  */
bool Cubo::estaRotacionando() const
{
        //Verifica se ainda tem algum rotacionando
        for (int x = 0; x < 3; ++x)
                for (int y = 0; y < 3; ++y)
                        for (int z = 0; z < 3; ++z)
                        {
                                if (cubiculos[x][y][z]->isRotacionando())
                                        return true;
                        }
        return false;
}

/** @brief filaRotacoesVazia
  *
  * @todo: document this function
  */
bool Cubo::filaRotacoesVazia() const
{
        return filaRotacoes.size() == 0;
}

/** @brief estaCubiculoNaPosicaoCorreta
  *
  * @todo: document this function
  */
bool Cubo::estaCubiculoNaPosicaoCorreta(const Cubiculo* cubi) const
{
        for (int i = 0; i < 6; ++i)
        {
                eFaceNome fa = (eFaceNome)i;
                Color c = cubi->getCorAtravesDaFace(fa);
                if (!(c == Color::Indefinido())) //Se for diferente é pq aquela facícula existe
                {
                        if (!(c == getFace(fa)->getColorDoCubiculoCentral())) //A cor da facícula tem que ser igual a cor da face
                                return false;
                }
        }
        return true;
}

