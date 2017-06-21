#include "ofApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
     ofSetVerticalSync(true);
    vid.initGrabber(width, height);
    
    tracker.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    vid.update();
    if(vid.isFrameNew()){
        tracker.update(toCv(vid));
        // anything you need to do in order to do with the new pixels
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0,0,0);
    vid.draw(0,0);
//    vector<ofVec2f> getImagePoints() const;
//    vector<ofVec3f> getObjectPoints() const;
//    vector<ofVec3f> getMeanObjectPoints() const;
    if(tracker.getFound()){
    vector<ofVec2f> points = tracker.getImagePoints();
    for(int i = 0; i < points.size(); i++){
        ofDrawCircle(points[i].x, points[i].y, 2.0);
        // getPOints returns a vector of ofVec3f
        // use the x and y values of each point to draw the points that are available
    }
    } else {

        ofDrawRectangle(0, 0, 40., 40.);
        
    }
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
