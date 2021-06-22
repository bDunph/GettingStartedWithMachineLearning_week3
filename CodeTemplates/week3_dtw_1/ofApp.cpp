#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    /* RapidLib Bools */
    isTrained = false;
    isRunning = false;
    isEmpty = true;

    /* FBO setup for visual feedback */
    fboWidth = 100.0f;
    fboHeight = 100.0f;
    fbo1.allocate(fboWidth, fboHeight, GL_RGB);
    fbo1.begin();
    ofClear(255);
    fbo1.end();
    fbo2.allocate(fboWidth, fboHeight, GL_RGB);
    fbo2.begin();
    ofClear(255);
    fbo2.end();
    fbo3.allocate(fboWidth, fboHeight, GL_RGB);
    fbo3.begin();
    ofClear(255);
    fbo3.end();
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(100, 100, 100);

    ofPushStyle();
    ofSetColor(ofColor::cyan);
    inputLine.draw();
    ofPopStyle();

    ofSetColor(ofColor::beige);
    ofDrawBitmapString("Current training label: " + ofToString(label), 20, 50);
    ofDrawBitmapString("Current output label: ", 20, 30); /* display the current output label */
    ofDrawBitmapString("Number of training examples: " + ofToString(), 20, 68); /* display the size of the training data vector */
    ofDrawBitmapString("Model Trained: " + ofToString(isTrained), 20, 96);
    ofDrawBitmapString("Recording: " + ofToString(isRecording), 20, 110);
    ofDrawBitmapString("Running: " + ofToString(isRunning), 20, 130);

    fbo1.draw(20, 150);
    fbo2.draw(130, 150);
    fbo3.draw(240, 150);

    ofDrawBitmapString("Instructions:\n\nPress 1, 2 or 3 to pick a training label\nPress space to activate recording\nDrag the mouse around the screen to create a gesture", 20, 260);
    ofDrawBitmapString("Keyboard Controls:\n\n\tspace -> toggle record data\n\tt -> train model\n\tr -> toggle run model\n\tc -> clear training examples\n\tq -> reset model", 20, 350);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'c' || key == 'C') /* use the 'c' key to clear training data */

    if (key == 'r' || key == 'R') {
        isRunning = !isRunning;
    }

    if (key == 'q' || key == 'Q') {
        /* use the 'q' key to reset the dtw model */
        isEmpty = true;
        isTrained = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    switch (key) {
    case 49:
        label = 1;
        break;
    case 50:
        label = 2;
        break;
    case 51:
        label = 3;
        break;
    case 32:
        isRecording = !isRecording;
        line.clear();
        break;
    }

    if (key == 't' || key == 'T') {
        /* use the 't' key to train the dtw model with the training set. 
         check if it has trained successfully using a bool. */
        
        isEmpty = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

    ofPoint inputPoint;
    inputPoint.set(x, y);
    inputLine.addVertex(inputPoint);

    /* Create a vector of doubles to hold the input training data */

    if (isRecording && !isTrained) {
        
        /* Populate the input training data vector with the current x and y values. */
        
        /* Use a temporary training series object to hold the input training data. */
        
        /* Give the training series object the output label for this training data. */
        
        /* The following code maps the mouse x and y positions to the size of the FBO objects 
        before drawing the line to the FBO. */
        ofPoint point1, point2, point3;
        float xPos = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, fboWidth);
        float yPos = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, fboHeight);
        switch (label) {
        case 1:
            fbo1.begin();
            ofBackground(0);
            point1.set(xPos, yPos);
            line.addVertex(point1);
            ofSetColor(ofColor::beige);
            line.draw();
            fbo1.end();
            break;
        case 2:
            fbo2.begin();
            ofBackground(0);
            point2.set(xPos, yPos);
            line.addVertex(point2);
            ofSetColor(ofColor::beige);
            line.draw();
            fbo2.end();
            break;
        case 3:
            fbo3.begin();
            ofBackground(0);
            point3.set(xPos, yPos);
            line.addVertex(point3);
            ofSetColor(ofColor::beige);
            line.draw();
            fbo3.end();
            break;
        }
    }

    if (isRunning && isTrained) {
        /* Create a vector of doubles to hold the new input data. */
        
        /* Give the new input data to the vector. */
        
        /* Run the dtw model on the new input. Store the output label in a string. */
        
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    inputLine.clear();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    if (isRecording && !isTrained) {
        /* When the mouse is released give the current training example 
        to the training set vector. */
        
        /* After the current training example is given to the training set 
        clear the current training example input. */
        
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

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
