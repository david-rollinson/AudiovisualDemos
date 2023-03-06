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
    
    protected:
        
    private:
    ofIcoSpherePrimitive sphr;
    ofVec3f pos, vel;
    float lifespan;
    float _angle;
    float _alpha;
};
#endif /* particle_hpp */
