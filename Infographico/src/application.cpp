#include "application.h"

//--------------------------------------------------------------
void Application::setup(){
	ofSetWindowTitle("Infographico");
	renderer.setup();
}

//--------------------------------------------------------------
void Application::update(){
	time_current = ofGetElapsedTimef();
	time_elapsed = time_current - time_last;
	time_last = time_current;
	renderer.update();
}

//--------------------------------------------------------------
void Application::draw(){
	renderer.draw();
}

//--------------------------------------------------------------
void Application::keyPressed(int key){

}

//--------------------------------------------------------------
void Application::keyReleased(int key){
	switch (key) {
		default:
			ofLog() << "<key released: " << key << ">"; // Useful for fast key recognition
			break;
	}
}

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y ){
	renderer.mousePosX = x;
	renderer.mousePosY = y;
}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button){
	renderer.mousePosX = x;
	renderer.mousePosY = y;
}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){
	renderer.isMouseButtonPressed = true;
	renderer.mousePosX = x;
	renderer.mousePosY = y;
	renderer.mousePressX = x;
	renderer.mousePressY = y;

	ofLog() << "<Mouse pressed at (" << x << ", " << y << ")>";
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button){
	renderer.isMouseButtonPressed = false;
	renderer.mousePosX = x;
	renderer.mousePosY = y;

	ofLog() << "<Mouse released at (" << x << ", " << y << ")>";
}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y){
	renderer.mousePosX = x;
	renderer.mousePosY = y;
}

//--------------------------------------------------------------
void Application::mouseExited(int x, int y){
	renderer.mousePosX = x;
	renderer.mousePosY = y;
}

//--------------------------------------------------------------
void Application::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Application::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Application::dragEvent(ofDragInfo dragInfo){

}

void Application::exit() {
	ofLog() << "<app::exit>";
}
