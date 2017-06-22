#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setup(640, 480);
    unwarped.allocate(640, 480, OF_IMAGE_COLOR);
    gui.setup();
    gui.add(minArea.set("Min area", 10, 1, 100));
    gui.add(maxArea.set("Max area", 300, 1, 500));
    gui.add(threshold.set("Threshold", 200, 0, 255));
    gui.add(dilation.set("Dilation", 5, 0, 10));
    gui.add(erosion.set("Erosion", 0, 0,10));
    gui.add(holes.set("Holes", false));
    gui.add(showContours.set("Show Contours", false));
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()) {
        contourFinder.setMinAreaRadius(minArea);
        contourFinder.setMaxAreaRadius(maxArea);
        // use erosion and dilation to change size shape of the
        erode(cam, cam, erosion);
        dilate(cam, cam, dilation);
        
        contourFinder.setThreshold(threshold);
        contourFinder.findContours(cam);
        contourFinder.setFindHoles(holes);
        
        int n = contourFinder.size();
        quads.clear();
        quads.resize(n);
        for(int i = 0; i < n; i++) {
            quads[i] = contourFinder.getFitQuad(i);
            
            // convert integer image coordinates Point2i to unwarp positions Point2f
            vector<Point2f> warpPoints;
            copy(quads[i].begin(), quads[i].end(), back_inserter(warpPoints));
            unwarpPerspective(cam, unwarped, warpPoints);
            unwarped.update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.draw(0,0);
    unwarped.draw(0,0);
    if(showContours){
            contourFinder.draw();
    }
    
    for(int i =0; i < contourFinder.size(); i ++){
        ofPolyline convexHull = toOf(contourFinder.getConvexHull(i));
        convexHull.draw();
    }

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}


//void ofApp::setup() {
//    cam.setup(640, 480);
//    gui.setup();
//    gui.add(minArea.set("Min area", 10, 1, 100));
//    gui.add(maxArea.set("Max area", 200, 1, 500));
//    gui.add(threshold.set("Threshold", 128, 0, 255));
//    gui.add(holes.set("Holes", false));
//}
//
//void ofApp::update() {
//    cam.update();
//    if(cam.isFrameNew()) {
//        contourFinder.setMinAreaRadius(minArea);
//        contourFinder.setMaxAreaRadius(maxArea);
//        contourFinder.setThreshold(threshold);
//        contourFinder.findContours(cam);
//        contourFinder.setFindHoles(holes);
//    }
//}
//
//void ofApp::draw() {
//    cam.draw(0, 0);
//    contourFinder.draw();
//    gui.draw();
//}