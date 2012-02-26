#ifndef _TEST_APP
#define _TEST_APP



#include "ofMain.h"
//#include "ofAddons.h"
#include "ofxAubioAnalyzer.h"

class testApp : public ofSimpleApp{
	
	public:
				
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();		
		void audioReceived		(float * input, int bufferSize, int nChannels);
	

	//(float *) left;
	//(float *) right;
	 float* left;
	 float* right;
	vector <float> volHistory;
	
	float curLeft;
	float curRight;
	
	
	
	int 	bufferCounter;
	int 	drawCounter;
	
	float smoothedVol;
	float scaledVol;
	
	ofSoundStream soundStream;
		
	
		ofxAubioAnalyzer AA;
	
		ofTrueTypeFont dinFont;
	
	
		int posX;
		int posY;
		float height;
		float width;
		float myPos;
	
	
		float pitchMin;
		float pitchMax;
		float pitchIn;
		float pitchPercent;
		float finalPitch;

	
		float vol;
		float calcVol;
	
		int r;
		int g;
		int b;


	
};

#endif	

