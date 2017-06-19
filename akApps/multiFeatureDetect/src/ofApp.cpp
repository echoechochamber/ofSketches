#include "ofApp.h"
using namespace ofxCv;
using namespace cv;
/*
 void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(120);
 finder.setup("haarcascade_frontalface_default.xml");
 finder.setPreset(ObjectFinder::Fast);
	cam.setup(640, 480);
 }*/
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    //default to showing the face and nothing else
    showEye = false;
    showFace = true;
    showFaceAlt = false;
    showFaceProfile = false;
    
    eye.setup("haarcascade_eye.xml");
     eye.setPreset(ObjectFinder::Fast);
    face.setup("haarcascade_frontalface_default.xml");
     face.setPreset(ObjectFinder::Fast);
    face_alt.setup("haarcascade_frontalface_alt.xml");
     face_alt.setPreset(ObjectFinder::Fast);
    face_profile.setup("haarcascade_profileface.xml");
     face_profile.setPreset(ObjectFinder::Fast);
    
    cam.setup(640,480);
    ofEnableAlphaBlending();
}



//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()){
        if(showEye){
            eye.update(cam);
        }
        if(showFace){
            face.update(cam);
        }
        if(showFaceAlt){
            face_alt.update(cam);
        }
        if(showFaceProfile){
            face_profile.update(cam);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.draw(0,0);
    if(showEye){
        eye.draw();
        ofDrawBitmapStringHighlight("drawing eye", 0, 15);
    }
    if(showFace){
        face.draw();
        ofDrawBitmapStringHighlight("drawing face", 0, 45);
    }
    if(showFaceAlt){
        face_alt.draw();
        ofDrawBitmapStringHighlight("drawing face alt", 0, 75);
    }
    if(showFaceProfile){
        face_profile.draw();
        ofDrawBitmapStringHighlight("drawing face profile", 0, 105);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case '1':
            showEye = !showEye;
            break;
        case '2':
            showFace = !showFace;
            break;
        case '3':
            showFaceAlt = !showFaceAlt;
            break;
        case '4':
            showFaceProfile = !showFaceProfile;
            break;
            
    }
}