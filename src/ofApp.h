#pragma once

#include "ofMain.h"
#include "ofxHapPlayer.h"
#include "ofxTweenzor.h"

class ofApp : public ofBaseApp{

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
		void drawHome();
		void drawPlayer();
		void switchToPlay(int num);
		
		ofxHapPlayer video[3];

		ofImage homeBck, homeDA, homeDE, homeEN, homePlay, homeLine;
		ofImage playDA, playDE, playEN, playRectangle, playPlayButtonDA, playPlayButtonDE, playPlayButtonEN, playReloadButtonDA, playReloadButtonDE, playReloadButtonEN;

		bool play;

		float currentPos;
		float transToHome;
		float transToPlay;
		float playGlow;

		int selectedVideo;
};