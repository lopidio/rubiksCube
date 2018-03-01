#ifndef COLOR_H
#define COLOR_H

#include "Definicoes.h"

class Color
{
        public:
                Color();
                Color(const Color&);
                Color(float r_, float g_, float b_);
                virtual ~Color();
                static const Color& Vermelho();
                static const Color& Branco();
                static const Color& Amarelo();
                static const Color& Azul();
                static const Color& Cinza();
                static const Color& Verde();
                static const Color& Laranja();
                static const Color& Indefinido();
                static const Color& enumToColor(eFaceNome);
                float getR() const;
                float getG() const;
                float getB() const;
                void print() const;
                bool operator==(const Color&) const;
        protected:
        private:
                float r, g, b;
};

#endif // COLOR_H
