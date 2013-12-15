#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void exit();
    void kinectValue(int cx, int cy);
    
    
    ofxKinect kinect;
	ofxCvContourFinder contourFinder;
    ofxCvGrayscaleImage grayImage;
    
    ofVideoPlayer video;
    ofSoundPlayer sound;
    ofShader shader;
    ofPoint point;
    ofPoint closePixel;

    int angle;
    int closestX;
    int closestY;
    
    int closestValue;
    int farthestValue;

    //should I use a vector instead?
    //int <depthPixels>;


};
