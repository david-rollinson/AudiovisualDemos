/*I referenced this guide in using FFT and SoundSpectrum: https://www.youtube.com/watch?v=vGZC72fAaBI */
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(particleThreshold.setup("Particle Threshold.",0.2, 0, 0.5));
    gui.add(primitiveThreshold.setup("Primitive Threshold.",0.15, 0, 0.5));
    
    /*Set up sound.*/
    sound.load("aphex.mp3");
    sound.play();
    sound.setLoop(true);
    /*Sey up FFT.*/
    bands = 100; //Set the number of frequency bands. I wanted this to be quite low, to make finding specific audio frequencies easier.
    fft = new float[bands]; //Create an array, with the number of indexes equalling the number of bands.
    for(int i = 0; i < bands; i++){
        fft[i] = 0; //Set each band frequency to 0 initially - to be filled with the true audio frequencies later.
    }
    
    /*Load particles.*/
    Particle* firstP = new Particle();
    firstP->setup(); //Setup the first particle and add its memory address to the vector of pointers.
    particles.push_back(firstP);
    
    /*Load 3D */
    ofEnableNormalizedTexCoords();
    cam.setPosition(ofGetWidth()*1.5, ofGetHeight()*2, 0);
//    cout << ofGetWidth() << endl;
//    cout << ofGetHeight() << endl;
    
    /*Populate the vector of pointers with the memory addresses of each primitive.*/
    for(int i = 0; i < 4; i++){
        Prmtv* prim = new Prmtv();
        primitives.push_back(prim);
        int j = (i + 1) % 2;
        if(j == 0){ //if j is a multiple of 2. if i == 1 || i == 3. Placing each primitive in square formation:
            int k = i - 2;
            primitives[i]->setup(-ofGetWidth(), 0, (-ofGetHeight()*1.5) * k, 400, 2);
        } else { //if i == 0 || i == 2.
            int k = i - 1;
            primitives[i]->setup(ofGetWidth(), 0, -ofGetHeight() * k, 200, 2);
        }
    }
    
//    Manual setup:
//    primitives[0]->setup(-ofGetWidth(), 0, -ofGetHeight()*1.5, 400, 2);
//    primitives[3]->setup(-ofGetWidth(), 0, ofGetHeight()*1.5, 400, 2);
//    primitives[1]->setup(ofGetWidth(), 0, ofGetHeight(), 200, 2);
//    primitives[2]->setup(ofGetWidth(), 0, -ofGetHeight(), 200, 2);
    
    /*Set the initial rotate amount.*/
    rotateAmnt = 1;
    
    /*Create a vector that more or less points the camera toward the primitives.*/
    ofVec3f tempPos = ofVec3f(ofGetWidth()/2, ofGetHeight()/2,0);
    cam.lookAt(tempPos);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    int index = 0;
    if(index < particles.size()){
        if(!particles[index]->isAlive){ /*Check the status of each particle.*/
            particles.erase(particles.begin()+index); /*If one has died, move along the array to its index and remove its address.*/
        }
    }
    
    /*Update each particle.*/
    for(int i=0; i<particles.size(); i++){
        particles[i]->update();
    }
    
    /*Sound.*/
    ofSoundUpdate();
    /*Create an array of sound frequencies.*/
    soundSpectrum = ofSoundGetSpectrum(bands);
    for(int i = 0; i < bands; i++){
        fft[i] *= 0.90; /*This decimal is used to smooth the output of the fft values. The higher it is, the greater the smoothing.*/
        if(fft[i] < soundSpectrum[i]){
            fft[i] = soundSpectrum[i]; /*If the fft frequency is less than the soundSpectrum frequency, set them to be equal. We want them to match so we can obtain accurate frequency values.*/
        }
    }
    for(int i = 5; i < bands/10; i++){ /*Check the low bands for frequencies above a value of 0.2.*/
        if(fft[i] >particleThreshold){
            Particle* newP = new Particle(); /*If an appropriate frequency is found, push a new particle.*/
            newP->setup(); /*This allows a kind of audio-reactive graphical effect.*/
            particles.push_back(newP);
        }
    }
    for(int i = 2; i < bands/10; i++){ /*Check the lower bands for frequencies above a value of 0.2*/
        if(fft[i]>primitiveThreshold){
            rotateAmnt = -3; /*If a value is found, swap the orbit of the primitives.*/
        }
        else{
            rotateAmnt = 1; /*This creates a stutter effect that responds to the music.*/
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    
    /*Set colors.*/
    ofSetBackgroundColor(0,0,0,0);
    ofSetColor(255, 255, 255, 255);
    ofFill();
    
    /*Draw a circle that graphically responds to the fft frequencies.*/
    for(int  i= 0; i < bands; i++){
        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, fft[i]*50); /*Here we multiply, because the frequency values are already mapped between 0 and 1.*/
    }
    
    ofEnableDepthTest();
    cam.begin();
    /*Draw each particle.*/
    for(int i=0; i<particles.size(); i++){
        particles[i]->draw();
    }
    /*Draw the 3d primitives to the screen.*/
    for(int i = 0; i < primitives.size();i++){
        primitives[i]->draw();
        primitives[i]->move(rotateAmnt); /*Rotate each primitive by an amount determined by the FFT analysis.*/
    }
    cam.end();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
ofApp::~ofApp(){
    /*Call destructors on each pointer array - give memory back.*/
    for(Particle* p : particles){
        delete p;
    }
    for(Prmtv* pr : primitives){
        delete pr;
    }
}
