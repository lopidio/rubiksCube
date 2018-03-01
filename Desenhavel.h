#ifndef DESENHAVEL_H
#define DESENHAVEL_H

#include <list>
#include "Color.h"

using namespace std;

class Desenhavel
{
        public:
                Desenhavel();
                virtual ~Desenhavel();
                void desenhaTudo() const;
                void addDesenhavel(const Desenhavel*);
                void removeDesenhavel(const Desenhavel*);
                const Color& getColor() const;
                void setColor(const Color& color);
                unsigned int getNumFilhos() const;
        protected:
                Color cor;
                list<const Desenhavel*> filhos;
        private:
                virtual void desenha() const;
};

#endif // DESENHAVEL_H
