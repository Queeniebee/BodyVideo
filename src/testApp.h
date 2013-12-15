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
    ofShader shader1, shaderX, shaderY;
    
    ofFbo BlurOne, BlurTwo;
    
    ofVideoPlayer video;
    ofSoundPlayer sound;
    
    ofPoint point;
    ofPoint closePixel;
    
    int quad1;
    int quad2;
    int quad3;
    int quad4;

    bool upLeftQuad;
    bool upRightQuad;
    bool lowLeftQuad;
    bool lowRightQuad;
    
    int angle;
//    int closestX;
//    int closestY;
    
    int closestValue;
    int farthestValue;

    //should I use a vector instead?
    //int <depthPixels>;


};
