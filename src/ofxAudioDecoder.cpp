#include "ofxAudioDecoder.h"

//----------
void ofxAudioDecoder::load(ofSoundBuffer & buffer, string filename, size_t framesToRead) {
	AudioDecoder audioDecoder(ofToDataPath(filename));
	if (audioDecoder.open() != AUDIODECODER_OK) {
		ofLogError() << "Failed to load " << filename;
	}
	
	auto numSamples = audioDecoder.numSamples();
	auto numChannels = audioDecoder.channels();
	auto sampleRate = audioDecoder.sampleRate();
	
	buffer.setSampleRate(sampleRate);
	buffer.allocate(numSamples, numChannels);
	
	//if we asked for 0 samples, presume default value (i.e. read whole file)
	if(framesToRead == 0) {
		framesToRead = numSamples / numChannels;
	}
	int samplesToRead = framesToRead * numChannels;
	int readBufferSize = sampleRate / numChannels;
	
	int curSample = 0;
	auto & rawSamples = buffer.getBuffer();
	while(curSample < samplesToRead) {
		int remainingSamples = MIN(readBufferSize, samplesToRead - curSample);
		int samplesRead = audioDecoder.read(remainingSamples, &rawSamples[curSample]);
		curSample += samplesRead;
		if(samplesRead < readBufferSize) {
			break;
		}
	}
	
	
	ofLogVerbose() << "Read " << curSample << " of " << numSamples;
}

//----------
int ofxAudioDecoder::getNumChannels() const {
	return this->buffer.getNumChannels();
}

//----------
int ofxAudioDecoder::getSampleRate() const {
	return this->buffer.getSampleRate();
}

//----------
int ofxAudioDecoder::getNumSamples() const {
	return this->buffer.size();
}

//----------
int ofxAudioDecoder::getNumFrames() const {
	return this->buffer.getNumFrames();
}

//----------
void ofxAudioDecoder::load(string filename, size_t framesToRead) {
	ofxAudioDecoder::load(this->buffer, filename, framesToRead);
}

//----------
const ofSoundBuffer & ofxAudioDecoder::getBuffer() const {
	return this->buffer;
}

//----------
const vector<float> & ofxAudioDecoder::getRawSamples() const {
	return this->buffer.getBuffer();
}