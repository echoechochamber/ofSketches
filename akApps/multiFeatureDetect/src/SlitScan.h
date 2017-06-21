//
//  SlitScan.h
//  multiFeatureDetect
//
//  Created by A. K. Williams on 6/20/17.
//
//

#ifndef SlitScan_h
#define SlitScan_h
#include "ofMain.h" // include this so we have a reference to the openFrameworks framework

class SlitScan {
    
public:
    void setup(int w, int h);
    void update(ofImage img, int colPosition);
    void draw(int x, int y);
    void draw(int x, int y, int w, int h);
    
    ofImage getImg();
    
    ofImage scan;
    //    int scanColumn ; // to be used later if you want to have an internal variable
    int scanWidth;
    int scanHeight;
    
    SlitScan();
    
private:
    void shiftPixelsLeft(ofImage * img);
};

#endif /* SlitScan_h */
