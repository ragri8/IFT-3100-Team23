#include "ofApp.h"

/*
 * Set up basic component for the OfApp object
 */
void ofApp::setup() {
    renderer.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
    renderer.update();
}

/*
 * Call the renderer draw function
 */
void ofApp::draw(){
    renderer.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

/*
 * Action performed when any key is released
 */
void ofApp::keyReleased(int key){
    switch (key) {
        default:
            ofLog() << "<key released: " << key << ">"; // Useful for fast key recognition
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    ofLog() << "<Mouse pressed at (" << x << ", " << y << ")>";
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    ofLog() << "<Mouse released at (" << x << ", " << y << ")>";
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

void ofApp::exit() {
    ofLog() << "<app::exit>";
}
