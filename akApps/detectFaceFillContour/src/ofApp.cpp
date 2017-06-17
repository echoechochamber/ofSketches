#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    cam.setup(640, 480);
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(150);
//    contourFinder.setInvert(true); // find black instead of white
    
    img.load("/Users/akwilliams/Documents/CODE/openFrameworks/examples/gl/alphaMaskingShaderExample/bin/data/B.jpg");
}

void ofApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        contourFinder.setTargetColor(targetColor,TRACK_COLOR_HS ); // track target color hue and saturation
       //contourFinder.setTargetColor(targetColor,TRACK_COLOR_RGB); // track target color rgb (less helpful for what I need
        contourFinder.setThreshold(75);
        contourFinder.findContours(cam);
    }
}

void ofApp::draw() {
    ofSetColor(255);
    cam.draw(0, 0);
    
    ofSetLineWidth(2);
    ofFill();
//    contourFinder.draw();
    
    /*
     draw into contour shapes by iterating through the polylines, using their vertices to build a 
     ofPath, which you can draw into 
     in order to render onto them, you'll have to find a way to make a mesh from the contour - but that will come later
     */
    int n = contourFinder.size();
    for(int i = 0; i < n; i++){
//        draw the path and fill it in 
//        ofPath pathToDraw = getPathFromPoly(i);
//        ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
//        ofFill();
//        pathToDraw.draw();
        
        
//        draw the mesh
        ofMesh mesh = getMeshFromPoly(i);
        img.bind();
//        mesh.drawWireframe();
                mesh.draw();
        img.unbind();
    }
    
    ofTranslate(8, 75);
    ofFill();
    ofSetColor(0);
    ofDrawRectangle(-3, -3, 64+6, 64+6);
    ofSetColor(targetColor);
    ofDrawRectangle(0, 0, 64, 64);
}

void ofApp::mousePressed(int x, int y, int button) {
    targetColor = cam.getPixels().getColor(x, y);
}

// create path (which you can draw into) from the polyLines of the contour
ofPath ofApp::getPathFromPoly(int index){
    //FOR FILLING
    ofPolyline polyline = contourFinder.getPolyline(index);//to convert
    ofPath pathFromContour;//path to be built
    
    for(int i = 0; i < polyline.getVertices().size(); i++) {
        if(i == 0) {
            pathFromContour.newSubPath();
            pathFromContour.moveTo(polyline.getVertices()[i]);
        } else {
            pathFromContour.lineTo(polyline.getVertices()[i]);
        }
    }
    pathFromContour.close();
    pathFromContour.simplify();
    
    return pathFromContour;
}


ofMesh ofApp::getMeshFromPoly(int index){
    ofPath pathForMesh = getPathFromPoly(index);
    ofMesh mesh =pathForMesh.getTessellation();
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    return mesh ;
}

