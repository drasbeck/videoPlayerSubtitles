#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);

	Tweenzor::init();

	video[0].loadMovie("EwaldDa.mov"); // nummer 0 er den danske
	video[1].loadMovie("EwaldDe.mov"); // nummer 1 er den tyske
	video[2].loadMovie("EwaldEn.mov"); // nummer 2 er den engelske

	homeBck.loadImage("home/background.png");
	homeDA.loadImage("home/da.png");
	homeDE.loadImage("home/de.png");
	homeEN.loadImage("home/en.png");
	homePlay.loadImage("home/play.png");
	homeLine.loadImage("home/line.png");
	playDA.loadImage("play/da.png");
	playDE.loadImage("play/de.png");
	playEN.loadImage("play/en.png");
	playPlayButtonDA.loadImage("play/play.png");
	playPlayButtonDE.loadImage("play/play.png");
	playPlayButtonEN.loadImage("play/play.png");
	playReloadButtonDA.loadImage("play/reload.png");
	playReloadButtonDE.loadImage("play/reload.png");
	playReloadButtonEN.loadImage("play/reload.png");
	playRectangle.loadImage("play/rectangle.png");

	transToHome = 255.f;
	transToPlay = 0.f;

	for (int i = 0; i < 3; i++) {
		video[i].setLoopState(OF_LOOP_NONE);
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	Tweenzor::update(ofGetElapsedTimeMillis());

	if (selectedVideo > -1) {
		video[selectedVideo].update();
	}

	video[1].update();
	
	if (selectedVideo > -1) {
		currentPos = video[selectedVideo].getPosition();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);
	ofSetColor(255, transToHome);
	drawHome();

	ofSetColor(255, transToPlay);
	if (selectedVideo > -1) {
		video[selectedVideo].draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		
		// progress bar
		ofSetColor(0, 100);
		ofRect(0, ofGetWindowHeight() - 4, ofGetWindowWidth(), ofGetWindowHeight());
		ofSetColor(255);
		ofRect(0, ofGetWindowHeight() - 4, ofGetWindowWidth() * video[selectedVideo].getPosition(), ofGetWindowHeight());

		// go to home screen when video is done
		if (video[selectedVideo].getIsMovieDone()) {
			selectedVideo = -1;
			currentPos = 0;
		}
		ofSetColor(255, transToPlay);
		drawPlayer();
	}

	// fps-o-meter
	ofSetColor(255, 200);
	string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, 10, ofGetWindowHeight() - 10);
}

//--------------------------------------------------------------
void ofApp::drawHome() {
	homeBck.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	homeDA.draw(966, 153);
	homePlay.draw(865, 153);
	//homeLine.draw(0, 360);
	homeDE.draw(966, 511);
	homePlay.draw(865, 511);
	//homeLine.draw(0, 720);
	homeEN.draw(966, 869);
	homePlay.draw(865, 869);
}

//--------------------------------------------------------------
void ofApp::drawPlayer() {
	playRectangle.draw(1723, 812);
	
	playDA.draw(1791, 836);
	if (!video[0].isPlaying()) {
			playPlayButtonDA.draw(1747, 836);
	} else {
		playReloadButtonDA.draw(1747, 836);
	}
	
	playDE.draw(1791, 900);
	if (!video[1].isPlaying()) {
		playPlayButtonDE.draw(1747, 900);
	} else {
		playReloadButtonDE.draw(1747, 900);
	}

	playEN.draw(1791, 964);
	if (!video[2].isPlaying()) {
		playPlayButtonEN.draw(1747, 964);
	} else {
		playReloadButtonEN.draw(1747, 964);
	}
}

//--------------------------------------------------------------
void ofApp::switchToPlay(int num) {
	selectedVideo = num;
	for (int i = 0; i < 3; i++) {
		if (i != num) {
			if (video[i].isPlaying()) {
				video[i].stop();
			}
		}
	}
	video[selectedVideo].setPosition(currentPos);
	video[selectedVideo].play();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'f') {
		ofToggleFullscreen();
	}
	if (key == '1') {
		Tweenzor::add(&transToHome, transToHome, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
		Tweenzor::add(&transToPlay, transToPlay, 255.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
		switchToPlay(0);
	}
	if (key == '2') {
		Tweenzor::add(&transToHome, transToHome, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
		Tweenzor::add(&transToPlay, transToPlay, 255.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
		switchToPlay(1);
	}
	if (key == '3') {
		Tweenzor::add(&transToHome, transToHome, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
		Tweenzor::add(&transToPlay, transToPlay, 255.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
		switchToPlay(2);
	}
	if (key == '4') {
		Tweenzor::add(&transToHome, transToHome, 255.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
		Tweenzor::add(&transToPlay, transToPlay, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
		selectedVideo = -1;
		currentPos = 0;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (selectedVideo < 0) {
		if (y < 360) {
			Tweenzor::add(&transToHome, transToHome, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
			Tweenzor::add(&transToPlay, transToPlay, 255.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
			switchToPlay(0);
		} else if (y > 360 && y < 720) {
			Tweenzor::add(&transToHome, transToHome, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
			Tweenzor::add(&transToPlay, transToPlay, 255.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
			switchToPlay(1);
		} else if (y > 720) {
			Tweenzor::add(&transToHome, transToHome, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
			Tweenzor::add(&transToPlay, transToPlay, 255.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
			switchToPlay(2);
		}
	} else {
		if (x > 1747 && x < 1747 + playDA.getWidth()) {
			if (y > 836 && y < 836 + playDA.getHeight()) {
				if (video[0].isPlaying()) {
					video[0].setPosition(0);
				} else {
					switchToPlay(0);
				}
			} else if (y > 900 && y < 900 + playDA.getHeight()) {
				if (video[1].isPlaying()) {
					video[1].setPosition(0);
				} else {
					switchToPlay(1);
				}
			} else if (y > 964 && y < 964 + playDA.getHeight()) {
				if (video[2].isPlaying()) {
					video[2].setPosition(0);
				} else {
					switchToPlay(2);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 

}
