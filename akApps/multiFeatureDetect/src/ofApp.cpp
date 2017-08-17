#include "ofApp.h"
using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    
    showGui = true;
    gui.setup();
    gui.add(showFace.set("Face", true));
    gui.add(showFaceAlt.set("Face Alt", false));
    gui.add(showFaceProfile.set("Face Profile", true));
    gui.add(randScan.set("Scan Randomly", false));
    gui.add(clearFbo.set("Clear Circles", false));
    gui.add(maxDistBetweenFrames.set("Max Face Distance", 200.0, 150.0, 500.0));
    gui.add(erosion.set("Erosion value", 0.0, 0.0, 15.0));
    
    //default to showing the face and nothing else
    showFace = true;
    showFaceAlt = false;
    showFaceProfile = true;
    
    
    w = ofGetWidth();
    h = ofGetHeight();
    scanPosition = w/2;
    imgPadding = 200;
    
    
    // NOTE: next steps : create a vector of face trackers to simplify the code
    // set up haar cascades
    // we're using multiple so that there will be a number of versions no matter what
    face.setup("haarcascade_frontalface_default.xml");
    face.setPreset(ObjectFinder::Fast);
    face.getTracker().setSmoothingRate(.3);
    face_alt.setup("haarcascade_frontalface_alt.xml");
    face_alt.setPreset(ObjectFinder::Fast);
    face_alt.getTracker().setSmoothingRate(.3);
    face_profile.setup("haarcascade_profileface.xml");
    face_profile.setPreset(ObjectFinder::Fast);
    face_profile.getTracker().setSmoothingRate(.3);
    
    
    scan.setup(120,120); // set up slit scan
    tmpImg.allocate(w,h, OF_IMAGE_COLOR); // get an image you can use to get rabber info iinto slitscan
    cam.setup(w,h);

    
    fbo.allocate(w,h); // for alphamasking
    
}



//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()){
        
        // update the slitscan no matter what
        tmpImg.setFromPixels(cam.getPixels());
        if(randScan){
            scanPosition = (int)ofRandom((w/2-35),(w/2+35));
            scan.update(tmpImg, scanPosition);
        } else {
            scanPosition = w/2;
            scan.update(tmpImg, w/2);
        }
        
        
        // update whatever you need to update
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
    if(clearFbo){
        ofClear(0, 0, 0, 0);
    }
    int fboWidth = ofGetWidth() / 3;
    int fboHeight =fboWidth + 200;
    ofDrawEllipse(fboWidth/2, fboHeight/2, fboWidth, fboHeight);
    
    int circOffSet = 10;
    float randW = ofRandom(0.,fboWidth-circOffSet);
    float randH = ofRandom(0.,fboHeight-circOffSet);
    ofDrawEllipse(randW, randH,  circOffSet,circOffSet);
    fbo.end();
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    erode(cam, cam, erosion);
    cam.draw(0,0);
    
    ofRectangle r;
    if(showFace && face.size() > 0){
        r = face.getObjectSmoothed(0);
    } else if(showFaceAlt && face_alt.size() > 0){
        r = face_alt.getObjectSmoothed(0);
    } else if(showFaceProfile && face_profile.size() > 0){
        r = face_profile.getObjectSmoothed(0);
    } else { // use the last displayed position;
        r = lastDisplayedPosition;
    }
    
    // if this point is too far from the last position,
    // assume this is a false positive and just use the last position
    float distSinceLastFrame = ofDist(r.getX(), r.getY(), lastDisplayedPosition.getX(), lastDisplayedPosition.getY() );
    if(distSinceLastFrame > maxDistBetweenFrames){
        r = lastDisplayedPosition;
    }
    
    //    handle the drawing and alphamasking of the pic
    ofImage scanImg = scan.getImg();
    scanImg.getTexture().setAlphaMask(fbo.getTexture());
    scanImg.resize(r.width + imgPadding, r.height+ (imgPadding*2));
    scanImg.draw(r.x,(r.y-imgPadding));
    lastDisplayedPosition = r; // save this position as the last rectangle
    
    if(showGui){
        gui.draw();
    }
    
//    ofDrawLine(scanPosition, 0, scanPosition, h);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'h'){
        showGui = !showGui;
    }
}

