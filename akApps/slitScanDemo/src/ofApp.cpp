#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth = 640;
    camHeight = 480;
    scanWidth = 640;
    scanColumn = 320;
    
    cam.initGrabber(camWidth, camHeight);
    slitScanImg.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    
    ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()){
        // grab one colun of pixels from the
        unsigned char * vidPix = cam.getPixels().getData(); // the access to the raw data has been changed to this (months ago)
        unsigned char * imgPix = slitScanImg.getPixels().getData();
        
        
        // move all of the pixels
        movePixelsInImage(&slitScanImg);
        
        for (int y = 0; y < camHeight; y++) {
            int imagePosition = y*(scanWidth*3)+(scanWidth-1)*3;
            int videoPosition = y*(camWidth*3)+scanColumn*3;
            imgPix[imagePosition]   = vidPix[videoPosition];
            imgPix[imagePosition+1] = vidPix[videoPosition+1];
            imgPix[imagePosition+2] = vidPix[videoPosition+2];
        }
        
        slitScanImg.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    slitScanImg.draw(0,0);
    //    cam.draw(0,0);
}


void ofApp::movePixelsInImage(ofImage * image) {
    unsigned char * pixels = image->getPixels().getData(); // the val for the pointers
    for (int x=0; x<camWidth-1; x++) {
        for (int y=0; y<camHeight; y++) {
            int position = y*(camWidth*3)+x*3;
            int nextPosition = position+3;
            pixels[position] = pixels[nextPosition];
            pixels[position+1] = pixels[nextPosition+1];
            pixels[position+2] = pixels[nextPosition+2];
        }
    }
    image->update();
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
