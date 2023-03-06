#ifndef room_hpp
#define room_hpp

#include <stdio.h>
#include "ofMain.h"
class Prmtv
{
    public:
    
    Prmtv();
    ~Prmtv();
    
    void setup(int, int, int, int, int);
    void draw();
    void move(float);
    
    protected:
    
    private:
    ofIcoSpherePrimitive sphr;
    ofColor color;
    
};
#endif
