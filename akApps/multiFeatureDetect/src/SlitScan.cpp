//
//  SlitScan.cpp
//  multiFeatureDetect
//
//  Created by A. K. Williams on 6/20/17.
// NOTE : the image being passed to update must be the same size or osmaller than the
//
//

#include "SlitScan.h"

SlitScan::SlitScan(){}

void SlitScan::setup(int w, int h){
    scanWidth = w;
    scanHeight = h;
    
    scan.allocate(scanWidth, scanHeight, OF_IMAGE_COLOR);
}

void SlitScan::update(ofImage img, int colPosition){
    unsigned char * srcPixels = img.getPixels().getData();
    unsigned char * scanPixels = scan.getPixels().getData();
    
    // shift the scan's pixels to the left
    shiftPixelsLeft(&scan);
    
    
    for (int y = 0; y < scanHeight; y++) {
        int imagePosition = y*(scanWidth*3)+(scanWidth-1)*3;
        int videoPosition = y*(scanWidth*3)+colPosition*3;
        scanPixels[imagePosition]   = srcPixels[videoPosition];
        scanPixels[imagePosition+1] = srcPixels[videoPosition+1];
        scanPixels[imagePosition+2] = srcPixels[videoPosition+2];
    }
    
    // update the pixels array
    scan.update();
    
}

void SlitScan::draw(int x, int y){
    scan.draw(x, y);
}

ofImage SlitScan::getImg(){
    return scan;
}

// NOTE: if you are going to use grayscale, you'll have to update this so that the
void SlitScan::shiftPixelsLeft(ofImage * img){
    unsigned char * pixels = img->getPixels().getData(); // the val for the pointers
    for (int x=0; x<scanWidth-1; x++) {
        for (int y=0; y<scanHeight; y++) {
            int position = y*(scanWidth*3)+x*3;
            int nextPosition = position+3;
            pixels[position] = pixels[nextPosition];
            pixels[position+1] = pixels[nextPosition+1];
            pixels[position+2] = pixels[nextPosition+2];
        }
    }
    img->update();
}
