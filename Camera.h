#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

class Camera
{
        public:
                Camera();

                void update();
                virtual ~Camera();
        protected:
        private:
                Vector3 posicao;
                Vector3 foco;
};

#endif // CAMERA_H
