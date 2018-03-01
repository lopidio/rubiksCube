#ifndef DISPLAY_H
#define DISPLAY_H

#include "Desenhavel.h"
#include "Color.h"
#define DISPLAY DEVICE.getDisplay()



using namespace std;

class Display
{
        friend class Device;
        public:
                Display();
                virtual ~Display();
                void drawAll();
                void reshape();
                void addDesenhavel(const Desenhavel*);
                void setColor(const Color&) const;
                void setViewPort(int, int);
        protected:
        private:
                int widthGLPort, heightGLPort;
                list<const Desenhavel*> lista;
};

#endif // DISPLAY_H
