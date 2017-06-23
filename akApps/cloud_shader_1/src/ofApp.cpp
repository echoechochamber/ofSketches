#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    
    srcImg.load("/Users/akwilliams/Desktop/cloud.png");
    
    int width = srcImg.getWidth();
    int height = srcImg.getHeight();
    
    maskFbo.allocate(width,height);
    maskFbo.begin();
    srcImg.draw(0,0);
    maskFbo.end();
    
    fbo.allocate(width,height);
    
    
    // trying to map the picture to a plane in order to use the image
    float planeScale = 0.75;
    int planeWidth = ofGetWidth() * planeScale;
    int planeHeight = ofGetHeight() * planeScale;
    int planeGridSize = 20;
    int planeColumns = planeWidth / planeGridSize;
    int planeRows = planeHeight / planeGridSize;
    
    plane.set(planeWidth, planeHeight, planeColumns, planeRows, OF_PRIMITIVE_TRIANGLES);
      plane.mapTexCoordsFromTexture(srcImg.getTexture());
    // There are 3 of ways of loading a shader:
    //
    //  1 - Using just the name of the shader and ledding ofShader look for .frag and .vert:
    //      Ex.: shader.load( "myShader");
    //
    //  2 - Giving the right file names for each one:
    //      Ex.: shader.load( "myShader.vert","myShader.frag");
    //
    //  3 - And the third one it�s passing the shader programa on a single string;
    //
    
//    shader.load("shaders/cloud_rotate_fbm");
        shader.load("shaders/noise");

    
}

//--------------------------------------------------------------
void ofApp::update(){
    fbo.begin();
    ofClear(0, 0, 0, 0);
    ofSetColor(255,0,0);
//    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    

    fbo.end();
    
//        fbo.getTexture().setAlphaMask(maskFbo.getTexture());
}

//--------------------------------------------------------------
void ofApp::draw(){
    srcImg.getTexture().bind();
    shader.begin();
    //we want to pass in some varrying values to animate our type / color
    shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
    shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );
    //			shader.setUniform1f("u_time", ofGetElapsedTimef());
    //we also pass in the mouse position
    //we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped.
    shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
    //    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    plane.draw();
    //    fbo.draw(0,0);
    shader.end();
    srcImg.getTexture().unbind();
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
