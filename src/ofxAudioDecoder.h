#pragma once

#include "ofMain.h"

#include <audiodecoder.h>

class ofxAudioDecoder {
protected:
	vector<float> rawSamples;
	int channels, sampleRate;
public:
	ofxAudioDecoder()
	:channels(0)
	,sampleRate(0) {
	}
	int getChannels() const {
		return channels;
	}
	int getSampleRate() const {
		return sampleRate;
	}
	int getNumSamples() const {
		return rawSamples.size();
	}
	int getNumFrames() const {
		return getNumSamples() / channels;
	}
	void load(string filename, unsigned long framesToRead = 0) {
		AudioDecoder* pAudioDecoder = new AudioDecoder(ofToDataPath(filename));
    if (pAudioDecoder->open() != AUDIODECODER_OK) {
			ofLogError() << "Failed to load " << filename;
		}
		
		int numSamples = pAudioDecoder->numSamples();
		channels = pAudioDecoder->channels();
		sampleRate = pAudioDecoder->sampleRate();
		
		if(framesToRead == 0) {
			framesToRead = numSamples / channels;
		}
		int samplesToRead = framesToRead * channels;
		rawSamples.resize(samplesToRead);
		int readBufferSize = sampleRate / channels;
		int curSample = 0;
		while(curSample < samplesToRead) {
			int remainingSamples = MIN(readBufferSize, samplesToRead - curSample);
			int samplesRead = pAudioDecoder->read(remainingSamples, &rawSamples[curSample]);
			curSample += samplesRead;
			if(samplesRead < readBufferSize) {
				break;
			}
		}
		
		ofLogVerbose() << "Read " << curSample << " of " << numSamples;
		
		delete pAudioDecoder;
	}
	const vector<float>& getRawSamples() const {
		return rawSamples;
	}
};