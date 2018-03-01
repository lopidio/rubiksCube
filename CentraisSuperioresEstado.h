#ifndef CENTRAISSUPERIORESESTADO_H
#define CENTRAISSUPERIORESESTADO_H

#include "EstadoAlgoritmo.h"


class CentraisSuperioresEstado: public EstadoAlgoritmo
{
        public:
                CentraisSuperioresEstado(AAlgoritmo*);
                virtual ~CentraisSuperioresEstado();
                virtual void atualiza();
        protected:
        private:
                const Color& verificaFaceMinerva(const Face*) const;
                void executa();
};

#endif // CENTRAISSUPERIORESESTADO_H
