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
    showFaceProfile = true;
    
    eye.setup("haarcascade_eye.xml");
    eye.setPreset(ObjectFinder::Fast);
    eye.getTracker().setSmoothingRate(.3);
    face.setup("haarcascade_frontalface_default.xml");
    face.setPreset(ObjectFinder::Fast);
    face.getTracker().setSmoothingRate(.3);
    face_alt.setup("haarcascade_frontalface_alt.xml");
    face_alt.setPreset(ObjectFinder::Fast);
    face_alt.getTracker().setSmoothingRate(.3);
    face_profile.setup("haarcascade_profileface.xml");
    face_profile.setPreset(ObjectFinder::Fast);
    face_profile.getTracker().setSmoothingRate(.3);
    imgPadding = 180;
    
    scan.setup(120,120);
    tmpImg.allocate(1024,768, OF_IMAGE_COLOR); // get an image you can use to get rabber info iinto slitscan
    cam.setup(1024,768);
    //    fbo.allocate(640,480, GL_LUMINANCE );
    fbo.allocate(1024,768);
    ofEnableAlphaBlending();
}



//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()){
        // update the slitscan no matter what
        tmpImg.setFromPixels(cam.getPixels());
        scan.update(tmpImg, ofGetWidth()/2);
        
        // update whatever you need to update
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
    
    // update the fbo
    fbo.begin();
    ofClear(0, 0, 0, 0);
    //    ofBackground(255);
    //    ofSetColor(0);
    //    ofFill();
    int fboWidth = ofGetWidth() / 3;
    int fboHeight =fboWidth;
    ofDrawEllipse(fboWidth/2, fboHeight/2, fboWidth, fboHeight);
    fbo.end();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //    ofClear(0,0,0,0);
    cam.draw(0,0);
    
    
    //    scan.draw(0,0);
    if(showEye){
        eye.draw();
        ofDrawBitmapStringHighlight("drawing eye", 0, 15);
    }
    if(showFace){
        //        face.draw();
        if(face.size() > 0){
            ofRectangle r = face.getObjectSmoothed(0); // get the first object
                                                       //            scan.draw(r.x, r.y, r.width, r.height);
            
            // get the image from the scan and mask
            ofImage scanImg = scan.getImg();
            scanImg.getTexture().setAlphaMask(fbo.getTexture());
            scanImg.resize(r.width + imgPadding, r.height+ imgPadding);
            scanImg.draw(r.x,r.y);
            lastDisplayedPosition = r;
        } else {
            ofImage scanImg = scan.getImg();
            scanImg.getTexture().setAlphaMask(fbo.getTexture());
            scanImg.resize(lastDisplayedPosition.width+ imgPadding, lastDisplayedPosition.height+ imgPadding);
            scanImg.draw(lastDisplayedPosition.x,lastDisplayedPosition.y);
            //            scan.draw(lastDisplayedPosition.x, lastDisplayedPosition.y, lastDisplayedPosition.width, lastDisplayedPosition.height );
        }
        //        ofDrawBitmapStringHighlight("drawing face", 0, 45);
    }
    if(showFaceAlt){
        face_alt.draw();
        //        ofDrawBitmapStringHighlight("drawing face alt", 0, 75);
    }
    if(showFaceProfile){
        if(face_profile.size() > 0){
            ofRectangle r = face.getObjectSmoothed(0); // get the first object
                                                       //            scan.draw(r.x, r.y, r.width, r.height);
            
            // get the image from the scan and mask
            ofImage scanImg = scan.getImg();
            scanImg.getTexture().setAlphaMask(fbo.getTexture());
            scanImg.resize(r.width + imgPadding, r.height+ imgPadding);
            scanImg.draw(r.x,r.y);
            lastDisplayedPosition = r;
        } else {
            ofImage scanImg = scan.getImg();
            scanImg.getTexture().setAlphaMask(fbo.getTexture());
            scanImg.resize(lastDisplayedPosition.width+ imgPadding, lastDisplayedPosition.height+ imgPadding);
            scanImg.draw(lastDisplayedPosition.x,lastDisplayedPosition.y);
            //            scan.draw(lastDisplayedPosition.x, lastDisplayedPosition.y, lastDisplayedPosition.width, lastDisplayedPosition.height );
        }
        //        face_profile.draw();
        //        ofDrawBitmapStringHighlight("drawing face profile", 0, 105);
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