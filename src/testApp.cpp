#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
void testApp::setup(){	 
	
	ofBackground(128);	
	ofSetCircleResolution(200);
	
	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	soundStream.listDevices();
	
	//setup of sound input
	left = new float[512];	
	right = new float[512];
	
	AA.setup();
	dinFont.loadFont("DIN.otf", 50);

	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
	
	soundStream.setup(this, 0, 2, 44100, 512, 4);
	
	pitchIn = (int)AA.pitch; //pitch input
	height = ofGetHeight();
	width = ofGetWidth();

	
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	//lets scale the vol up to a 0-1 range 
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
	
	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
	


}


//--------------------------------------------------------------
void testApp::draw(){
	
	//ofSetColor(225);
	ofDrawBitmapString("AUDIO INPUT EXAMPLE", 32, 32);
	ofDrawBitmapString("press 's' to unpause the audio\n'e' to pause the audio", 31, 92);
	
	ofNoFill();
	
	pitchIn = (float)AA.pitch; //pitch input
	myPos = (pitchIn * 100) / 3000 ;  // x position on screen
	
	ofSetHexColor(0x000000);
	ofDrawBitmapString( "pitch is : " + ofToString(myPos) + "\namplitude is : " + ofToString(scaledVol * 100.0, 0), 14,ofGetHeight()-20);
	
	ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 4, 18);

	if (myPos <= 10) {
		ofSetColor(20, 249, 135);
	}
	else if (myPos >= 11 || myPos <= 20){
		ofSetColor(242, 81, 81);
	}
	else if ( myPos >= 21 || myPos <= 30) {
		ofSetColor(180, 16, 0);
	}
	else if ( myPos >= 31 || myPos <= 40 ) {
		ofSetColor(155, 46, 18);
	}
	else if ( myPos >= 41 || myPos <= 50 ) {
		ofSetColor(18, 255,140);
	}
	else if ( myPos >= 51 || myPos <= 60 ) {
		ofSetColor(90, 255, 19);
	}
	else if ( myPos >= 61 || myPos <= 70 ) {
		ofSetColor(81, 220, 44);
	}
	else if ( myPos >= 71 || myPos <= 80 ) {
		ofSetColor(38, 158, 254);
	}
	else if ( myPos >= 81 || myPos <= 90 ) {
		ofSetColor(47, 38, 233);
	}
	else if ( myPos >= 91 || myPos <= 100 ) {
		ofSetColor(233, 125, 38);
	}
	else if ( myPos >= 101 || myPos <= 110 ) {
		ofSetColor(233, 38, 116);
	}
	else if ( myPos >= 111 || myPos <= 120 ) {
		ofSetColor(114, 4, 48);
	}
	else if ( myPos >= 121 || myPos <= 130 ) {
		ofSetColor(228, 216, 79);
	}
	else if ( myPos >= 131 || myPos <= 140 ) {
		ofSetColor(228, 114, 79);
	}
	else if ( myPos >= 141 ) {
		ofSetColor(233, 255, 0);
	}
	
	ofFill();		
	ofCircle(ofGetWidth()/2, ofGetHeight()/2, scaledVol * 890.0f);
	
	/*  //lets draw the volume history as a graph
	ofBeginShape();
	for (int i = 0; i < volHistory.size(); i++){
		if( i == 0 ) ofVertex(i, 400);
		
		ofVertex(i, 400 - volHistory[i] * 70);
		
		if( i == volHistory.size() -1 ) ofVertex(i, 400);
	}
	ofEndShape(false);	 */	

	
}


//--------------------------------------------------------------
void testApp::audioReceived (float * input, int bufferSize, int nChannels){	
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
	
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;		
		right[i]	= input[i*2+1]*0.5;
		
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;

	AA.processAudio(right, bufferSize);
}



//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
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
void testApp::mouseReleased(){
	
}


