#pragma once

#include "ofMain.h"
/* Step 1: include the rapidlib header file */

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
	/* Step 2: declare a series classification object */

	/* Step 3: declare a temporary training series object */

	/* Step 4: declare a vector to hold training data */
	
	/* Step 5: create a string to store the output label */
	
	int label; 

	bool isRecording;
	bool isTrained;
	bool isEmpty;
	bool isRunning;

	/* GUI objects */
	ofFbo fbo1, fbo2, fbo3;
	float fboWidth, fboHeight;
	ofPolyline line, inputLine;
};
