#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFlowTools.h"

//#define USE_PROGRAMMABLE_GL

using namespace flowTools;

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
    
    void drawParticles()	{ drawParticles(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
	void				drawParticles(int _x, int _y, int _width, int _height);
    
    ofImage mask;
    float lastTime;
    float deltaTime;
    int w, h;
    int flowWidth ;
    int flowHeight;
    
    ftDrawMouseForces mouseForces;
    ftFluidSimulation fluidSimulation;
    ftParticleFlow particleFlow;
		
};
