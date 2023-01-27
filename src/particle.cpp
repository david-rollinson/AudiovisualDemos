/*I referenced this guide in building this particle system: https://subscription.packtpub.com/book/application_development/9781849518048/3 */
#include "particle.hpp"
Particle::Particle() {
    cout << "Particle constructed." << endl;
    isAlive = false;
}

/*Creating a random velocity for each particle.*/
ofVec3f randomVel(float minSpeed, float maxSpeed){
    ofVec3f randVel;
    float speed = ofRandom(minSpeed, maxSpeed); /*Generate a random speed.*/
    float direction = ofRandom(0, TWO_PI); /*Generate a random direction of travel.*/
    randVel.x = sin(direction)*speed; /*Use both cos and sine for 360 degree particle emmission.*/
    randVel.y = abs(cos(direction)*speed); /*I used the 'abs' method here to create 180 degree particle emission.*/
    randVel.z = cos(direction)*speed;
    return randVel; /*Return the velocity.*/
}

void Particle::setup(){
    // ofVec3f tempPos = ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0); /*Set an initial point for the particle to emit from.*/
    ofVec3f tempPos = ofVec3f(0, 0, 0); /*Set an initial point for the particle to emit from.*/
    pos = tempPos - randomVel(10, 50); /*Create a random velocity and subtract it from the initial position.*/
    vel = randomVel(10, 50); /*Create the particle's initial speed and direction.*/
    lifespan = 100; /*Each particle can only survive for 100 'frames'/loops of the update function.*/
    isAlive = true; /*Tell the rest of the program that the particle is alive.*/
}

void Particle::update(){
    if(isAlive){
        lifespan--; /*Decrement the particle's lifespan every loop.*/
        float timeAlive = ofMap(lifespan, 0, 100, 0, 1);
        pos += vel * timeAlive; /*Slow down the particle as it gets older.*/
        
        if(lifespan == 0){
            isAlive = false; /*When lifespan reaches zero, pronounce the particle dead.*/
        }
    }
}

void Particle::draw(){
    if(isAlive){
        ofColor color = ofColor(255,255,255);
        ofSetColor(color);
        //ofDrawCircle(pos, 10); /*Draw the particle to the screen.*/
        sphr.set(200, 2);
        sphr.setPosition(pos);
        sphr.drawWireframe();
    }
}

Particle::~Particle() {
    cout << "Particle destructed." << endl;
}
