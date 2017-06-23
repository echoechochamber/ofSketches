#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    picWidth = 640;
    picHeight = 480;

    
// allocate six sspaces in the vector;
    // add the values into the vector
    tri.push_back(ofPoint(300,150));
        tri.push_back(ofPoint(350,50));
        tri.push_back(ofPoint(400,150));

    /* 
     NOTE: you only need to draw into a off frame buffer if you're rendering video to the mesh 
     when rendring video, during each update 
     */
    fbo.allocate(picWidth, picHeight);
//    // clear fbo
    fbo.begin();
    ofClear(0,0,0, 0);
    fbo.end();
    
    // allocate for image to be filled in later
        img.allocate(picWidth, picHeight,OF_IMAGE_COLOR);
    
    // loading in an image that's already created
//    img.load("/Users/akwilliams/Desktop/pic.jpg");
//    img.resize(picWidth, picHeight);
    
    
    // setting up the
    //Set up vertices
    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
            mesh.addVertex(ofPoint((x - W/2) * meshSize, (y - H/2) * meshSize, 0 )); // adding texure coordinates allows us to bind textures to it later // --> this could be made into a function so that textures can be swapped / updated
            mesh.addTexCoord(ofPoint(x * (videoWidth / W), y * (videoHeight / H)));
            mesh.addColor(ofColor(255, 255, 255));
        }
    }
    
    //Set up triangles' indices
    for (int y=0; y<H-1; y++) {
        for (int x=0; x<W-1; x++) {
            int i1 = x + W * y;
            int i2 = x+1 + W * y;
            int i3 = x + W * (y+1);
            int i4 = x+1 + W * (y+1);
            mesh.addTriangle( i1, i2, i3 );
            mesh.addTriangle( i2, i4, i3 );
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    // clear fbo
    fbo.begin();
    ofClear(0,0,0, 0);
    ofBackground(127,127,127);
    vector<ofPoint>::iterator it;
    for(it = tri.begin(); it < tri.end(); ++it, ++it){
        // make the triangle grow and shrink
        (*it) += sin(ofGetElapsedTimef());
    }
    ofSetColor(255);
//    ofPushMatrix();
//    ofRotate(10, 1, 0.5, 0);
    ofDrawTriangle(tri[0].x,tri[0].y,tri[1].x,tri[1].y, tri[2].x,tri[2].y);
//    ofPopMatrix();
    fbo.end();
    
    cout << tri[0] << endl;
    // get the fbo's pixels and map them to image
    ofPixels pixels; // declare pixels arr
    fbo.readToPixels(pixels); // read the fbo into the pixels array
    img.setFromPixels(pixels); // read the pixels vector into and image
    
    
    //Change vertices - applying noise to the mesh
    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
            
            //Vertex index
            int i = x + W * y;
            ofPoint p = mesh.getVertex( i );
            
            //Change z-coordinate of vertex
            p.z = ofNoise(x * 0.05, y * 0.05, ofGetElapsedTimef() * 0.5) * 100;
            mesh.setVertex( i, p );
            
            //Change color of vertex
            mesh.setColor(i , ofColor(255, 255, 255));
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofBackground(0,0,0);
    
//    mesh.drawWireframe();
    
//    fbo.begin();
//    img.draw(0,0);
//    fbo.end();
//    fbo.draw(180,120);
    
    ofPushMatrix(); //Store the coordinate system
    ofRotate(10, 1, 0.5, 0);
    //Move the coordinate center to screen's center
    ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 );

    //Draw mesh
    img.bind();
    mesh.draw();
//         mesh.drawWireframe();
    img.unbind();

    
    ofPopMatrix(); //Restore the coordinate system
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
