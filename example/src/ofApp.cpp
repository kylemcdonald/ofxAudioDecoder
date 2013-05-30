#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(120);
	loadFile("demo.mp3");
}

void ofApp::update() {
	
}

void ofApp::draw() {
	ofBackground(0);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofScale((float) ofGetWidth() / audio.getNumFrames(), ofGetHeight() / 2);
	ofTranslate(0, 1);
	ofSetColor(ofColor::red);
	left.drawWireframe();
	ofSetColor(ofColor::green);
	right.drawWireframe();
}

void ofApp::dragEvent(ofDragInfo dragInfo) {
	loadFile(dragInfo.files[0]);
}

void ofApp::loadFile(string filename) {
	audio.load(filename);
	
	left.clear();
	right.clear();
	
	left.setMode(OF_PRIMITIVE_LINE_STRIP);
	right.setMode(OF_PRIMITIVE_LINE_STRIP);
	
	const vector<float>& rawSamples = audio.getRawSamples();
	int channels = audio.getChannels();
	int n = rawSamples.size();
	for(int c = 0; c < channels; c++) {
		for(int i = c; i < n; i+= channels) {
			(c == 0 ? left : right).addVertex(ofVec2f(i / channels, rawSamples[i]));
		}
	}
}
