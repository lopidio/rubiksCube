#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#define PRINCIPAL Principal::getInstancia()

#include "Cubo.h"
#include "Definicoes.h"

using namespace std;

class Principal
{
        friend class Device;
        public:
                virtual ~Principal();
                static Principal* getInstancia();
                virtual void atualiza(float);
                Cubo* getCubo() const;
                float getVelocidadeAngular() const;
                void criarAlgoritmo();
        protected:
        private:
                float velocidadeAngular;
                static Principal* instancia;
                Cubo* cubo;
                AAlgoritmo* algoritmo; //Provisorio
                Principal();
};

#endif // PRINCIPAL_H
