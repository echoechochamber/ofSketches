#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    
    ofVideoGrabber cam;
    ofxCv::ContourFinder contourFinder;
    vector< vector<cv::Point> > quads;
    ofColor targetColor;
    ofImage unwarped;
    
    ofxPanel gui;
    ofParameter<float> minArea, maxArea, threshold, dilation, erosion;
    ofParameter<bool> holes, showContours;
		
};
