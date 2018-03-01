#include "Camera.h"

Camera::Camera()
{
        //Essa câmera tá sendo inútil.. Impressionante!
//        printf("Camera criada");
        posicao = Vector3(10,10,10);
        foco = Vector3(0,0,0);
}

Camera::~Camera()
{
        //dtor
}

void Camera::update()
{
        gluLookAt (posicao.getX(), posicao.getY(), posicao.getZ(),
                                foco.getX(), foco.getY(), foco.getZ(),
                                                0.0, 1.0, 0.0);
}
