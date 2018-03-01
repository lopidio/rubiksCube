#ifndef VECTOR3_H
#define VECTOR3_H

#include "Matriz.h"
#include "Definicoes.h"

class Vector3: public Matriz
{
        public:
                Vector3();
                Vector3(const Vector3& from, const Vector3& to);
                Vector3(eFaceNome);
                Vector3(float x, float y, float z);
                virtual ~Vector3();
                float getX() const;
                float getY() const;
                float getZ() const;
                void setX(float x);
                void setY(float y);
                void setZ(float z);
                GLfloat* toGLfloat() const;
                eFaceNome toFacicula() const;
                eEixoRotacao toEixo() const;
                void arredondar();
        public: //Operações
                bool eIgual(const Vector3& outro) const;
                float produtoInterno(const Vector3&) const;
                Vector3* produtoVetorial(const Vector3&) const;
                void normalizar();
                float norma() const;
                void multiplicaPor(const Matriz& matriz);
                Vector3* projetar(const Vector3&) const;
        protected:
        private:
};

#endif // VECTOR3_H
