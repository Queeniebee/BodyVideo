#include "testApp.h"
#include <iostream.h>

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);

    video.loadMovie( "MOVIE.mov" );
    sound.loadSound( "SOUND.mp3" );
    
    shader1.load("shaders/pixelate");    

    kinect.init(false, false); 
    kinect.open();
    
    sound.play();
    sound.setVolume(0.8f);
    sound.setLoop(true);

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
    video.update();

    int currentDepthPixel = 0;
    closestValue = 50;
    farthestValue = 1000;

    unsigned char* depthPixels = kinect.getDepthPixels();
    
    for(int x = 0; x < kinect.getWidth(); x++){
        for(int y = 0; y < kinect.getHeight(); y++){
            int i = x + y * kinect.getWidth();
            int currentDepthPixel = depthPixels[i];
            if(currentDepthPixel > closestValue && currentDepthPixel < farthestValue){
                closestValue = currentDepthPixel;

                closePixel.x = x;
                closePixel.y = y;

        }
    
    }
}
    kinectValue(closePixel.x, closePixel.y);
}

//--------------------------------------------------------------
void testApp::draw(){

        shader1.begin();
        shader1.setUniform2f("sampleDivisor", point.x, point.y);
        shader1.setUniform2f("depthPoint", closePixel.x, closePixel.y);
        video.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        shader1.end();

}

//--------------------------------------------------------------
void testApp::kinectValue(int cx, int cy){
    
    float dist = ofDist(0, 0, cx, cy);
    float max = ofDist(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    float pixelSize = ofMap(dist, 0, max, 1, 50);
    point.x = pixelSize;
    point.y = pixelSize;
    
    float positionX = ofMap(dist, closePixel.x, 1000, 0, ofGetWindowWidth());
    float positionY = ofMap(dist, closePixel.y, 500, 0, ofGetWindowHeight());
/*    

//    float mapPlayback = (closestValue - 200) * 0.01;
//    float playback = ofMap(mapPlayback, 0, .55, 0, 1, true);
//    if(video.getPosition() == 1.0){
//        playback = 0;
//    }
//    video.setPosition(playback);


*/    
/*   
     Mapping playback position
     
    float mapPlayback = (closestValue - 200) * 0.01;
    float playback = ofMap(mapPlayback, 0, .55, 0, 1, true);
    if(video.getPosition() == 1.0){
        playback = 0;
   }
   video.setPosition(playback);
   
   */

/*
    If swapping between shaders
    
    quad1 = (positionX/2)-4;
    quad2 = (positionX/2)+4;
    quad3 = (positionY/2)-4;
    quad4 = (positionY/2)+4;
    
    if((cx % 5 == 0) && (cx % 3 != 0)) {
        
        if((closePixel.x > 0 && closePixel.x < quad1) && (closePixel.y > 0 && closePixel.y < quad3)){
            
            upLeftQuad = true;
            upRightQuad = false;
            lowLeftQuad = false;
            lowRightQuad = false;
            
        } else if((closePixel.x > quad2 && closePixel.x < ofGetWindowWidth()) && (closePixel.y > quad4 && closePixel.y < ofGetWindowHeight())){
            upLeftQuad = false;
            upRightQuad = false;
            lowLeftQuad = false;
            lowRightQuad = true;
            
        } else if((closePixel.x > 0 && closePixel.x < quad1) && (closePixel.y > quad4 && closePixel.y < ofGetWindowHeight())){
            
            upLeftQuad = false;
            upRightQuad = false;
            lowLeftQuad = true;
            lowRightQuad = false;
            
        }else if((closePixel.x > quad2 && closePixel.x < ofGetWindowWidth()) && (closePixel.y > 0 && closePixel.y < quad3)){
            
            upLeftQuad = false;
            upRightQuad = true;
            lowLeftQuad = false;
            lowRightQuad = false;
            
        }
    }
    if((cx % 3 == 0) || (cx % 5 != 0)){
        
        if((closePixel.x > 0 && closePixel.x < 510) && (closePixel.y > 0 && closePixel.y < 362)){
            
            upLeftQuad = false;
            upRightQuad = true;
            lowLeftQuad = false;
            lowRightQuad = false;
            
        } else if((closePixel.x > quad2 && closePixel.x < ofGetWindowWidth()) && (closePixel.y > quad4 && closePixel.y < ofGetWindowHeight())){
            upLeftQuad = false;
            upRightQuad = false;
            lowLeftQuad = true;
            lowRightQuad = false;
            
        } else if((closePixel.x > 0 && closePixel.x < quad1) && (closePixel.y > quad4 && closePixel.y < ofGetWindowHeight())){
            
            upLeftQuad = false;
            upRightQuad = false;
            lowLeftQuad = false;
            lowRightQuad = true;
            
        }else if((closePixel.x > quad2 && closePixel.x < ofGetWindowWidth()) && (closePixel.y > 0 && closePixel.y < quad3)){
            
            upLeftQuad = true;
            upRightQuad = true;
            lowLeftQuad = false;
            lowRightQuad = false;
            
        }
    }
*/

}
//--------------------------------------------------------------
void testApp::exit() {
	kinect.setCameraTiltAngle(0);
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
