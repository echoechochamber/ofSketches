#pragma once

#include "ofMain.h"

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

        ofImage img;
        ofFbo fbo;
        ofMesh mesh;
    vector<ofPoint> tri;
    
    private:
        int picWidth;
        int picHeight;
        int videoWidth = 720;
        int videoHeight = 480;
        int W = 100; //Grid size
        int H = 100;
        int meshSize = 6;
		
};
