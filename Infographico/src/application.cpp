#include "application.h"

//--------------------------------------------------------------
void Application::setup(){
	renderer.setup();
}

//--------------------------------------------------------------
void Application::update(){

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

}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){
	ofLog() << "<Mouse pressed at (" << x << ", " << y << ")>";
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button){
	ofLog() << "<Mouse released at (" << x << ", " << y << ")>";
}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void Application::mouseExited(int x, int y){

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
