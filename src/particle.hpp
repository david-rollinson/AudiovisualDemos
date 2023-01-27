#ifndef particle_hpp
#define particle_hpp

#include <stdio.h>
#include "ofMain.h"

class Particle {
    
    public:
    Particle();
    ~Particle();
    
    void setup();
    void update();
    void draw();
    
    bool isAlive;
    
    ofIcoSpherePrimitive sphr;
        
    protected:
        
    private:
    ofVec3f pos, vel;
    float lifespan;
};
#endif /* particle_hpp */
