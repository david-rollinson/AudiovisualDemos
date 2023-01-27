#pragma once

#include "ofMain.h"
#include "particle.hpp"
#include "primitive.hpp"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        ~ofApp();
    
    private:
        ofxFloatSlider particleThreshold;
        ofxFloatSlider primitiveThreshold;
        ofxPanel gui;
    
        ofSoundPlayer sound;
    
        float *fft;
        float *soundSpectrum;
        int bands;
    
        vector<Particle*> particles;
        vector<Prmtv*> primitives;
    
        float rotateAmnt;
        ofEasyCam cam;
};
