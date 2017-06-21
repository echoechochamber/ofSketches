#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "SlitScan.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    bool showEye;
    bool showFace;
    bool showFaceAlt;
    bool showFaceProfile;
    
    ofVideoGrabber cam;
    ofxCv::ObjectFinder eye;
    ofxCv::ObjectFinder face;
    ofxCv::ObjectFinder face_alt;
    ofxCv::ObjectFinder face_profile;
    
    ofImage tmpImg; 
    SlitScan scan;
    
    
};
