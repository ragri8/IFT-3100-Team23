#include "application.h"

//--------------------------------------------------------------
void Application::setup(){
	ofSetWindowTitle("Infographico");
	/********************/
	is_key_press_plus = false;
	is_key_press_moins = false;
	is_key_press_left = false;
	is_key_press_right = false;

	is_key_press_a = false;
	is_key_press_d = false;
	is_key_press_down = false;
	is_key_press_up = false;
	is_key_press_s = false;
	/*************************/

	renderer.setup();
}

//--------------------------------------------------------------
void Application::update(){
	/*****************************/
	if (!renderer.is2D) {
		if (renderer.isSurfaceParametriqueActive) {
			renderer.is_camera_move_forward = is_key_press_plus;
			renderer.is_camera_move_backward = is_key_press_moins;

			renderer.is_camera_move_left = is_key_press_left;
			renderer.is_camera_move_right = is_key_press_right;

			renderer.is_camera_move_up = is_key_press_up;
			renderer.is_camera_move_down = is_key_press_down;

			if (is_key_press_w) {
				renderer.pointDeControleSelectionneSurface->y += renderer.vitessePointDeControle * time_elapsed;
			}
			if (is_key_press_a) {
				renderer.pointDeControleSelectionneSurface->x -= renderer.vitessePointDeControle * time_elapsed;
			}
			if (is_key_press_d) {
				renderer.pointDeControleSelectionneSurface->x += renderer.vitessePointDeControle * time_elapsed;
			}
			if (is_key_press_s) {
				renderer.pointDeControleSelectionneSurface->y -= renderer.vitessePointDeControle * time_elapsed;
			}
		}
		else {
		renderer.is_camera_move_forward = is_key_press_plus;
		renderer.is_camera_move_backward = is_key_press_moins;

		renderer.is_camera_move_left = is_key_press_left || is_key_press_a;
		renderer.is_camera_move_right = is_key_press_right || is_key_press_d;

		renderer.is_camera_move_up = is_key_press_up || is_key_press_w;
		renderer.is_camera_move_down = is_key_press_down || is_key_press_s;
		}
	}
	else {
		if (renderer.isCourbeParametriqueActive) {
			if (is_key_press_up)
				renderer.pointDeControleSelectionne->y -= renderer.vitessePointDeControle * time_elapsed;
			if (is_key_press_down)
				renderer.pointDeControleSelectionne->y += renderer.vitessePointDeControle * time_elapsed;
			if (is_key_press_left)
				renderer.pointDeControleSelectionne->x -= renderer.vitessePointDeControle * time_elapsed;
			if (is_key_press_right)
				renderer.pointDeControleSelectionne->x += renderer.vitessePointDeControle * time_elapsed;
		}
	}
	
	/*****************************/

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

	/******************************/
	if (!renderer.is2D) {
		switch (key) {
			case 97:  // touche A
				is_key_press_a = true;
				break;

			case 100: // touche D
				is_key_press_d = true;
				break;

			case 359: // touche v
				is_key_press_down = true;
				break;

			case 357: // touche ^
				is_key_press_up = true;
				break;

			case 115: // touche S
				is_key_press_s = true;
				break;

			case 119: // touche W
				is_key_press_w = true;
				break;

			case 356: // touche <-
				is_key_press_left = true;
				break;

			case 43: // 43touche +
				is_key_press_plus = true;
				break;

			case 358: // touche ->
				is_key_press_right = true;
				break;

			case 45: // 45touche -
				is_key_press_moins = true;
				break;

			default:
				break;
		}
	}
	else {
		if (renderer.isCourbeParametriqueActive) {
			switch (key) {

			case 359: // touche v
				is_key_press_down = true;
				break;

			case 357: // touche ^
				is_key_press_up = true;
				break;

			case 356: // touche <-
				is_key_press_left = true;
				break;

			case 358: // touche ->
				is_key_press_right = true;
				break;

			default:
				break;
			}
		}
	}
	/**************************/
}

//--------------------------------------------------------------
void Application::keyReleased(int key){
	/****************************/
	if (!renderer.is2D) { //nouveau
	/********************************/
		switch (key) {

			/*****************************/
		case 97:  // touche A
			is_key_press_a = false;
			break;

		case 100: // touche D
			is_key_press_d = false;
			break;

		case 359: // touche v
			is_key_press_down = false;
			break;

		case 357: // touche ^
			is_key_press_up = false;
			break;

		case 115: // touche S
			is_key_press_s = false;
			break;

		case 119: // touche W
			is_key_press_w = false;
			break;

		case 356: // touche <-
			is_key_press_left = false;
			break;

		case 43: // touche +
			is_key_press_plus = false;
			break;

		case 358: // touche ->
			is_key_press_right = false;
			break;

		case 45: // touche -
			is_key_press_moins = false;
			break;

		case 49: // touche 1
			renderer.pointDeControleSelectionneSurface = &renderer.pointDeControleSurface1;
			ofLog() << "<select control point 1>";
			break;

		case 50: // touche 2
			renderer.pointDeControleSelectionneSurface = &renderer.pointDeControleSurface2;
			ofLog() << "<select control point 2>";
			break;

		case 51: // touche 3
			renderer.pointDeControleSelectionneSurface = &renderer.pointDeControleSurface3;
			ofLog() << "<select control point 3>";
			break;

		case 52: // touche 4
			renderer.pointDeControleSelectionneSurface = &renderer.pointDeControleSurface4;
			ofLog() << "<select control point 4>";
			break;

		case 53: // touche 5
				renderer.pointDeControleSelectionneSurface = &renderer.pointDeControleSurface5;
			ofLog() << "<select control point 5>";
			break;

		case 54: // touche 6
				renderer.pointDeControleSelectionneSurface = &renderer.pointDeControleSurface6;
			break;

		case 55: //touche 7
			renderer.pointDeControleSelectionneSurface = &renderer.pointDeControleSurface7;
			break;

		case 56: //touche 8
			renderer.pointDeControleSelectionneSurface = &renderer.pointDeControleSurface8;
			break;

			/******************************/

		default:
			ofLog() << "<key released: " << key << ">"; // Useful for fast key recognition
			break;
		}
	/******************************/

	}
	else {
		if (renderer.isCourbeParametriqueActive) {
			switch (key) {
			case 359: // touche v
				is_key_press_down = false;
				break;

			case 357: // touche ^
				is_key_press_up = false;
				break;

			case 356: // touche <-
				is_key_press_left = false;
				break;

			case 358: // touche ->
				is_key_press_right = false;
				break;

			case 48: // touche 0
				ofLog() << "<0>";
				break;

			case 49: // touche 1
				renderer.pointDeControleSelectionne = &renderer.pointDeControle1;
				ofLog() << "<select control point 1>";
				break;

			case 50: // touche 2
				renderer.pointDeControleSelectionne = &renderer.pointDeControle2;
				ofLog() << "<select control point 2>";
				break;

			case 51: // touche 3
				renderer.pointDeControleSelectionne = &renderer.pointDeControle3;
				ofLog() << "<select control point 3>";
				break;

			case 52: // touche 4
				renderer.pointDeControleSelectionne = &renderer.pointDeControle4;
				ofLog() << "<select control point 4>";
				break;

			case 53: // touche 5
				if (renderer.curveId == CurveType::splineDeBezier) {
					renderer.pointDeControleSelectionne = &renderer.pointDeControle5;
				}
				ofLog() << "<select control point 5>";
				break;

			case 54: // touche 6
				if (renderer.curveId == CurveType::splineDeBezier) {
					renderer.pointDeControleSelectionne = &renderer.pointDeControle6;
				}
				ofLog() << "<select control point 6>";
				break;

			default:
				break;
			}
		}
	}

	/********************************/
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


