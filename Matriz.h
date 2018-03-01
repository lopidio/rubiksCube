#ifndef MATRIZ_H
#define MATRIZ_H

/**@TODO Lançar exceção "strings"
Ajeitar as sobrecargas.. elas não podem mudar o this
*/

class Matriz
{
        public:
                Matriz(unsigned int lin,unsigned  int col, bool identidade = true);
                Matriz(const Matriz& );
                virtual ~Matriz();
                unsigned int getLinha() const;
                unsigned int getColuna() const;
                Matriz* getVectorColuna(unsigned int col) const;
                Matriz* getVectorLinha(unsigned int lin) const;
                void setValor(unsigned int lin, unsigned int col, float valor);
                float getValor(unsigned int lin, unsigned int col) const;
                void print() const;
        public: //Sobrecarga de operador
                Matriz* operator*(const Matriz&) const;
                Matriz* operator*(float) const;
                Matriz* operator+(const Matriz&) const;
                Matriz* operator-(const Matriz&) const;
                Matriz& operator=(const Matriz&);
        public: //Matrizes de transformações lineares
                static Matriz* RotacaoX(double alpha);
                static Matriz* RotacaoY(double alpha);
                static Matriz* RotacaoZ(double alpha);
                void transformacaoAfim(const Matriz&, float alfa);
        protected:
                unsigned int linha, coluna;
        private:
                void destruir();
                float ** valores;
        private:
                Matriz* aumentarDimensao();
                Matriz* diminuirDimensao();
};

#endif // MATRIZ_H
