#ifndef DEFINICOES_H_INCLUDED
#define DEFINICOES_H_INCLUDED

#include <windows.h>
#ifdef __APPLE__
        #include <GLUT/glut.h>
#else
        #include <GL/glut.h>
#endif

#include <math.h>

#include <iostream>
#include <stdio.h>

#define UPDATE_TIMER 33

#define DEBUG
#ifdef DEBUG
        #define TRACK_TRACE std::cout << __PRETTY_FUNCTION__ << "  " << __LINE__ << "\n"
#else
        #define TRACK_TRACE
#endif

//Lado + ladoOposto = 5
enum eFaceNome
{
        eFACENOME_CIMA,
        eFACENOME_FRENTE,
        eFACENOME_ESQUERDA,
        eFACENOME_DIREITA,
        eFACENOME_TRAS,
        eFACENOME_BAIXO,
        eFACENOME_INEXISTENTE
};

enum eSentidoRotacao
{
        eSENTIDOROTACAO_HORARIO = -1,
        eSENTIDOROTACAO_ANTIHORARIO = 1
};

enum eEixoRotacao
{
        eEIXOROTACAO_X,
        eEIXOROTACAO_Y,
        eEIXOROTACAO_Z
};

namespace utils
{
        eFaceNome rotacionarFaceNome(eFaceNome face, eEixoRotacao eixo, eSentidoRotacao sentido);
        eFaceNome iterar(eFaceNome face);

        eSentidoRotacao inverter(eSentidoRotacao);
        const char* faceToString(eFaceNome);
}

#endif // DEFINICOES_H_INCLUDED
