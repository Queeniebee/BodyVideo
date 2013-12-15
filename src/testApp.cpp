#include "testApp.h"
#include <iostream.h>

//--------------------------------------------------------------
void testApp::setup(){
    video.loadMovie( "GoodHair_shorter/Resources/GoodHair_shorter.mov" );
    sound.loadSound( "GoodHair_short.mp3" );
    shader.load("shaders/pixelate");
    
    kinect.init(false, false); // disable video image (faster fps)
    kinect.open();
    
    sound.play();
    sound.setVolume(0.8f);
    
    video.play();
    video.setVolume(0.0f);
    
    point.set(20, 20);

    angle = 0;
	kinect.setCameraTiltAngle(angle);
    

}

//--------------------------------------------------------------
void testApp::update(){
    ofSoundUpdate;
    kinect.update();

    //I DON'T KNOW HOW TO ACHIEVE THE EFFECT I WANT
    //MAYBE CLOSEST BLOB INSTEAD OR ALSO?
    
    /*
     contourFinder
     */

    // What is the difference between distance pixels and depth pixels?
    //both allow for 8bit and 11bit values
   
    int currentDepthPixel = 0;
    closestValue = 50;
    farthestValue = 1000;
    
    //holdover value from Processing
    
    //I believe I need to set parameters since the three examples found do
    //int minimumDistance = 450;
    //int maximumDistance = 800;
    
    unsigned char* depthPixels = kinect.getDepthPixels();
    
//    int sumX = 0;    
//    int sumY = 0;
//    int counter = 0;

    //I don't know if the bounds should be the Kinect, Video, or App Window
    for(int x = 0; x < kinect.getWidth(); x++){
        for(int y = 0; y < kinect.getHeight(); y++){
            int i = x + y * kinect.getWidth();
            int currentDepthPixel = depthPixels[i];
            // int currentDepthPixel = depthPixels[x + y * ofGetWindowWidth()]
            if(currentDepthPixel > closestValue && currentDepthPixel < farthestValue){
                // save its value
                closestValue = currentDepthPixel;

                // and save its position (both X and Y coordinates)
//                closestX = x;
//                closestY = y;
                closePixel.x = x;
                closePixel.y = y;

                
        }
    
    }
    }
    cout<<"closestX: "<<closestX<<"\tclosestY: "<<closestY<<"\tclosestZ: "<<closestValue<<endl;
    
//    kinectValue(closestX, closestY);
//    contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
    kinectValue(closePixel.x, closePixel.y);

    
    video.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    shader.begin();
    shader.setUniform2f("sampleDivisor", point.x, point.y);
    shader.setUniform2f("depthPoint", closePixel.x, closePixel.y);
//    shader.setUniform2f("depthPoint", closePixel.x, closePixel.y);
    video.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    shader.end();
    
    ofSetColor(20);
    ofRect(point.x, point.y, 20, 20);
//    ofCircle( closestX, closestY, 10 );
    ofCircle( closePixel.x, closePixel.y, 10 );

}

//--------------------------------------------------------------
void testApp::kinectValue(int cx, int cy){
    
    float dist = ofDist(10, 10, cx, cy);
    float max = ofDist(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    float pixelSize = ofMap(dist, 0, max, 1, 50);
    point.x = pixelSize;
    point.y = pixelSize;

}
//--------------------------------------------------------------
void testApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
