#pragma once

#include "ofMain.h"

#include <audiodecoder.h>

class ofxAudioDecoder {
protected:
	ofSoundBuffer buffer;
public:
	static void load(ofSoundBuffer & buffer, string filePath, size_t framesToRead = 0);
	
	int getNumChannels() const;
	int getSampleRate() const;
	int getNumSamples() const;
	int getNumFrames() const;
	void load(string filename, size_t framesToRead = 0);
	const ofSoundBuffer & getBuffer() const;
	const vector<float> & getRawSamples() const;
};

