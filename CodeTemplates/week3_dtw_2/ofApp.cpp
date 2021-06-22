#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    /* Audio Params */
    int sampleRate = 44100;
    int bufferSize = 512;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);

    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);

    /* Initialise the FM parameters */

    /* RapidLib bools */
    isTrained = false;
    isRunning = false;
    isEmpty = true;
    
    /* FBO initialisation */
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

    ofPushStyle();
    ofSetColor(ofColor::beige);
    ofDrawBitmapString("Current training label: " + ofToString(label), 20, 50);
    ofDrawBitmapString("Current output label: " + outputLabel, 20, 30);
    ofDrawBitmapString("Number of training examples: " + ofToString(data.size()), 20, 68);
    ofDrawBitmapString("Model Trained: " + ofToString(isTrained), 20, 96);
    ofDrawBitmapString("Recording: " + ofToString(isRecording), 20, 110);
    ofDrawBitmapString("Running: " + ofToString(isRunning), 20, 130);
    ofPopStyle();

    fbo1.draw(20, 150);
    fbo2.draw(130, 150);
    fbo3.draw(240, 150);

    ofDrawBitmapString("Instructions:\n\nPress 1, 2 or 3 to pick a training label\nPress space to activate recording\nDrag the mouse around the screen to create a gesture", 20, 260);
    ofDrawBitmapString("Keyboard Controls:\n\n\tspace -> toggle record data\n\tt -> train model\n\tr -> toggle run model\n\tc -> clear training examples\n\tq -> reset model", 20, 350);
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output) {

    std::size_t outChannels = output.getNumChannels();

    for (int i = 0; i < output.getNumFrames(); ++i) {

        float modFreq = /* modulating frequency is the carrier divided by the ratio */;
        float deviation = /* deviation is the modulating frequency multiplied by the index */ ;

        double modSignal = modulator.saw(modFreq) * deviation;
        double carrierSignal = carrier.sinewave(/* the original carrier frequency is added to the signal here */ + modSignal) * 0.3f;

        finalOut = carrierSignal;

        if (finalOut > 0.95f) {
            finalOut = 0.95f;
        }

        output[i * outChannels] = finalOut;
        output[i * outChannels + 1] = output[i * outChannels];
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'c' || key == 'C') data.clear();

    if (key == 'r' || key == 'R') {
        isRunning = !isRunning;
    }

    if (key == 'q' || key == 'Q') {
        dtw.reset();
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
        isTrained = dtw.train(data);
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

    std::vector<double> trainingInput;
    std::vector<double> trainingOutput;

    if (isRecording && !isTrained) {

        trainingInput.push_back(x);
        trainingInput.push_back(y);
        tempSeries.input.push_back(trainingInput);
        tempSeries.label = ofToString(label);

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
        std::vector<double> modelInput;
        modelInput.push_back((double)x);
        modelInput.push_back((double)y);
        outputLabel = dtw.runContinuous(modelInput);
        /* Use the outputLabel to change FM parameters. */
        
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    inputLine.clear();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    if (isRecording && !isTrained) {
        data.push_back(tempSeries);
        tempSeries.input.clear();
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
