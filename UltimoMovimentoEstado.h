#ifndef ULTIMOMOVIMENTOESTADO_H
#define ULTIMOMOVIMENTOESTADO_H

#include "EstadoAlgoritmo.h"

class UltimoMovimentoEstado: public EstadoAlgoritmo
{
        public:
                UltimoMovimentoEstado(AAlgoritmo*);
                virtual ~UltimoMovimentoEstado();
                virtual void atualiza();
        protected:
        private:
                void executa();
};

#endif // ULTIMOMOVIMENTOESTADO_H
