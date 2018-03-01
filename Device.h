#ifndef DEVICE_H
#define DEVICE_H

#include "Display.h"
#include "Principal.h"

#define DEVICE Device::getInstancia()


class Device
{
        public:
                void initialize();
                void destroy();
                void run();
                Display& getDisplay();
                static Device& getInstancia(); //singleton
        protected:
        private:
                 void eventHandler(); //Cadastra as funções tratadoras de evento
                 static void DisplayEvent();
                 static void ReshapeEvent(int width, int height);
                 static void KeyboardEvent(unsigned char key, int x, int y);
                 static void UpdateEvent(int);
        private: //atributos
                Principal* principal;
                Display* display;

                Device(); //singleton
                ~Device();
};

#endif // DEVICE_H
