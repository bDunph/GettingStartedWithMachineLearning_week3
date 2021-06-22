#pragma once

#include "ofMain.h"
#include "ofxRapidLib.h"

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

	ofFbo fbo1, fbo2, fbo3;
	float fboWidth, fboHeight;
	ofPolyline line, inputLine;
};
