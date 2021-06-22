#pragma once

#include "ofMain.h"
#include "ofxRapidLib.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	/* Audio */
	ofSoundStream soundStream;
	void audioOut(ofSoundBuffer& output) override;
	double finalOut;

	/* FM synth */
	maxiOsc modulator;
	maxiOsc carrier;
	maxiOsc phasor;

	float index;
	float ratio;
	float carrierFreq;

	/* Step sequencer */
	int currentStep;
	int lastStep;
	int stepCounter;
	maxiOsc metronome;
	double arpFreq;

	/* RapidLib */
	rapidlib::seriesClassification dtw;
	std::vector<rapidlib::trainingSeries> data;
	rapidlib::trainingSeries tempSeries;
	int label;
	std::string outputLabel;

	bool isRecording;
	bool isTrained;
	bool isEmpty;
	bool isRunning;

	/* Visual Feedback */
	ofFbo fbo1, fbo2, fbo3;
	float fboWidth, fboHeight;
	ofPolyline line, inputLine;
};
