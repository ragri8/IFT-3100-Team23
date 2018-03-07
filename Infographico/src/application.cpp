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
    renderer.mouse_current_x = x;
    renderer.mouse_current_y = y;

	if (!renderer.is_mouse_button_legit) {
		renderer.is_mouse_button_pressed = false;
	}
}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button){
    renderer.mouse_current_x = x;
    renderer.mouse_current_y = y;
}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){
	renderer.is_mouse_button_pressed = true;
	renderer.is_mouse_button_legit = true;

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	renderer.mouse_press_x = x;
	renderer.mouse_press_y = y;
	ofLog() << "<Mouse pressed at (" << x << ", " << y << ")>";
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button){

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	if (renderer.is_mouse_button_pressed) {
		renderer.is_mouse_button_pressed = false;
		switch (renderer.draw_tool) {
			case DrawTool::primitive: {
				renderer.addForm();
				break;
			}

			case DrawTool::select: {
				renderer.selectObject();
				break;
			}
		}
	}
}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y) {
	renderer.is_mouse_button_pressed = false;
	ofLog() << "<Mouse entered at (" << x << ", " << y << ")>";
}

//--------------------------------------------------------------
void Application::mouseExited(int x, int y) {
	renderer.is_mouse_button_pressed = false;
	ofLog() << "<Mouse exited at (" << x << ", " << y << ")>";
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
