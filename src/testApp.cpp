#include "testApp.h"
#include <iostream.h>

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);

    video.loadMovie( "GoodHair_JFleurantin/Resources/GoodHair_JFleurantin.mov" );
    sound.loadSound( "GoodHair_short.mp3" );
    
//    BlurOne.allocate(ofGetWidth(), ofGetHeight());
//    BlurTwo.allocate(ofGetWidth(), ofGetHeight());
    
    shader1.load("shaders/pixelate");    
//    shaderX.load("shaders/blur");
//    shaderY.load("shaders/blur2");
    
    kinect.init(false, false); // disable video image (faster fps)
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
    cout<<"closestX: "<<closePixel.x<<"\tclosestY: "<<closePixel.y<<"\tclosestZ: "<<closestValue<<endl;
    
    kinectValue(closePixel.x, closePixel.y);    
    
//    if(upLeftQuad || lowRightQuad){
//        BlurOne.begin();
//        video.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
//        
//        ofSetColor(255);
//        for(int y = 0; y<ofGetWindowHeight(); y+=10)
//            for(int x=0; x<ofGetWindowWidth(); x+=10) {
//                ofRect(x, y, 5, 5);
//            }
//        
//        BlurOne.end();
//    }
    
//    if(upLeftQuad || lowRightQuad){
//        int iterations = 5;
//        for (int i=0; i<iterations; i++){
//            
//            BlurTwo.begin();
//            shaderX.begin();
//            shaderX.setUniform1f("amount", point.x);
//            BlurOne.draw(0, 0);
//            shaderX.end();
//            BlurTwo.end();
//            
//            BlurOne.begin();
//            shaderY.begin();
//            shaderY.setUniform1f("amount", point.y);
//            BlurTwo.draw(0, 0);
//            shaderY.end();
//            BlurOne.end();
//        }
//    }
  
}

//--------------------------------------------------------------
void testApp::draw(){
    
//    if(upLeftQuad || lowRightQuad){
//        
//        BlurOne.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
//    }
//    
//    if((upRightQuad || lowLeftQuad)){
        shader1.begin();
        shader1.setUniform2f("sampleDivisor", point.x, point.y);
        shader1.setUniform2f("depthPoint", closePixel.x, closePixel.y);
        video.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        shader1.end();
//    }
//    
//    if(upLeftQuad || lowRightQuad){
//        BlurTwo.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
//    }
    
//    ofSetColor(20);
//    ofCircle( closePixel.x, closePixel.y, point.x );

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
    
//    float mapPlayback = (closestValue - 200) * 0.01;
//    float playback = ofMap(mapPlayback, 0, .55, 0, 1, true);
////    if(video.getPosition() == 1.0){
////        playback = 0;
////    }
//    video.setPosition(playback);
    
//    int counter = 0;
//    for (counter; counter < 5; counter++) {
//        int playheadAvg += mapPlayback;
//
//    } (mapPlayback) {
//        <#statements#>
//    }
//    cout<<"playhead\t"<<mapPlayback<<endl;

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
