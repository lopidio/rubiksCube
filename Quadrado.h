#ifndef QUADRADO_H
#define QUADRADO_H

#include "Vector3.h"
#include "Color.h"
#include <list>
#include "Desenhavel.h"

using namespace std;

class Quadrado: public Desenhavel
{
        public:
                Quadrado();
                Quadrado(const Vector3*, const Vector3*, const Vector3*, const Vector3*, const Color&);
                virtual ~Quadrado();
                virtual void desenha() const;
                Vector3* getCentroide() const;
                Vector3* getNormal() const;
        protected:
        private:
                void desenhaContorno() const;
                list<const Vector3*> vertices; //arranjados no sentido anti-horário
};

#endif // QUADRADO_H
