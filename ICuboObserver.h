#ifndef ICUBOOBSERVER_H
#define ICUBOOBSERVER_H

#include "Cubo.h"

class Cubo; //Forward declaration

//Interface dos observadores do cubo

class ICuboObserver
{
        public:
                virtual void onCuboCompleto() = 0;
                virtual void onFimCuboRotacoes(const Cubo*) = 0;
        protected:
};

#endif // ICUBOOBSERVER_H
