#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "SlitScan.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed();
    
    ofVideoGrabber cam;
    ofxCv::ObjectFinder face;
    ofxCv::ObjectFinder face_alt;
    ofxCv::ObjectFinder face_profile;
    
    bool showGui;
    ofxPanel gui;
    ofParameter<bool> showFace, showFaceAlt, showFaceProfile, randScan, scanVertical, clearFbo;
    ofParameter<float> maxDistBetweenFrames, erosion;

    
    int w, h;

    ofImage tmpImg;
    ofFbo fbo;
    SlitScan scan;
    ofRectangle lastDisplayedPosition;
    int imgPadding;
    int scanPosition ;
};
