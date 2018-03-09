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
}

//--------------------------------------------------------------
void Application::draw(){
	renderer.draw();
}

//--------------------------------------------------------------
void Application::keyPressed(int key){
    switch (key) {
        case 768: //768 and 769 is ctrl button
            renderer.is_ctrl_pressed = true;
            break;

        default:
            break;
    }

}

//--------------------------------------------------------------
void Application::keyReleased(int key){
	switch (key) {
        case 122: // z button
            if (renderer.is_ctrl_pressed) {
                renderer.undo();
            }
            break;

        case 121: // y button
            if (renderer.is_ctrl_pressed) {
                renderer.redo();
            }
            break;

        case 768:
            renderer.is_ctrl_pressed = false;
            break;

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
	if (renderer.draw_tool == DrawTool::primitive && renderer.is2D) {
        renderer.is_preview = true;
		renderer.create_preview();
	}
	ofLog() << "<Mouse pressed at (" << x << ", " << y << ")>";
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button){

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	if (renderer.is_mouse_button_pressed && renderer.is2D) {
		renderer.is_mouse_button_pressed = false;
		switch (renderer.draw_tool) {
			case DrawTool::primitive:
				renderer.addForm();
                renderer.is_preview = false;
				break;

			case DrawTool::select:
				renderer.selectObject();
				break;
		}
	}
}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y) {
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
	renderer.is_mouse_button_pressed = false;
	ofLog() << "<Mouse entered at (" << x << ", " << y << ")>";
}

//--------------------------------------------------------------
void Application::mouseExited(int x, int y) {
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
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
