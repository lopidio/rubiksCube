#ifndef F2L_H
#define F2L_H

#include "AAlgoritmo.h"

//Eis o algoritmo que segui
//http://peter.stillhq.com/jasmine/rubikscubesolution.html

class F2L: public AAlgoritmo
{
        public:
                F2L();
                virtual ~F2L();
                virtual void atualizaFilho();
        protected:
                //Herdada de AAlgoritmo -> herdada de ICuboObserver
                virtual void onCuboCompleto();
        private:
};

#endif // F2L_H
