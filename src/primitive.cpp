#include "primitive.hpp"

//constructor
Prmtv::Prmtv(){
    cout << "Primitive constructed." << endl;
}

void Prmtv::setup(int x, int y, int z, int _rad, int _res){
    /*Set radius and resolution.*/
    sphr.set(_rad, _res);
    color = ofColor(255,255,255,255);
    /*Set position.*/
    sphr.setPosition(x, y, z);
    
}

void Prmtv::draw(){
    ofSetColor(color);
    sphr.drawWireframe();
}

void Prmtv::move(float _deg){
    /*Rotate the primitive by '_deg' number of degrees about the Y axis.*/
    sphr.rotateDeg(_deg,0,1,0);
}

Prmtv::~Prmtv(){
    cout << "Primitive destructed." << endl;
}
