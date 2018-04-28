#include "application.h"

//--------------------------------------------------------------
void Application::setup(){
	ofSetWindowTitle("Infographico");
	is_key_press_plus = false;
	is_key_press_moins = false;
	is_key_press_left = false;
	is_key_press_right = false;

	is_key_press_a = false;
	is_key_press_d = false;
	is_key_press_down = false;
	is_key_press_up = false;
	is_key_press_s = false;
	renderer.setup();
}

//--------------------------------------------------------------
void Application::update(){
	if (!renderer.is2D) {
        renderer.is_camera_move_forward = is_key_press_plus;
        renderer.is_camera_move_backward = is_key_press_moins;

        renderer.is_camera_move_left = is_key_press_left;
        renderer.is_camera_move_right = is_key_press_right;

        renderer.is_camera_move_up = is_key_press_up;
        renderer.is_camera_move_down = is_key_press_down;
		if (renderer.isSurfaceParametriqueActive) {

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
void Application::keyPressed(int key) {
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

        case 768:
            renderer.is_ctrl_pressed = true;

        default:
            break;
    }

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
}

//--------------------------------------------------------------
void Application::keyReleased(int key){
	if (!renderer.is2D) {
		switch (key) {
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

            default:
                ofLog() << "<key released: " << key << ">"; // Useful for fast key recognition
                break;
        }
        switch (renderer.selected_3D_instance) {
            case Select_3D::surface:
                switch (key) {
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

                    default:
                        break;
                }
                break;

            case Select_3D::lumiere: {
                ofLight* temp_light = NULL;
                switch (key) {
                    case 49: // touche 1
                        renderer.light_selected = Light_select::light1;
                        temp_light = &renderer.light_1;
                        renderer.sliderRotation3DX = renderer.light_1_angle.x;
                        renderer.sliderRotation3DY = renderer.light_1_angle.y;
                        renderer.sliderRotation3DZ = renderer.light_1_angle.z;
                        ofLog() << "< light 1 selected >";
                        break;

                    case 50: // touche 2
                        renderer.light_selected = Light_select::light2;
                        temp_light = &renderer.light_2;
                        renderer.sliderRotation3DX = renderer.light_2_angle.x;
                        renderer.sliderRotation3DY = renderer.light_2_angle.y;
                        renderer.sliderRotation3DZ = renderer.light_2_angle.z;
                        //ofLight light = *temp_light;
                        ofLog() << "< light 2 selected >";
                        break;

                    case 51: // touche 3
                        renderer.light_selected = Light_select::light3;
                        temp_light = &renderer.light_3;
                        renderer.sliderRotation3DX = renderer.light_3_angle.x;
                        renderer.sliderRotation3DY = renderer.light_3_angle.y;
                        renderer.sliderRotation3DZ = renderer.light_3_angle.z;
                        ofLog() << "< light 3 selected >";
                        break;

                    default:
                        break;
                }
                if (temp_light) {
                    ofLog() << "A light has been detected";
                    ofFloatColor temp_color;
                    switch (renderer.light_selected_aspect) {
                        case Light_aspect::ambient:
                            temp_color = temp_light->getAmbientColor();
                            break;

                        case Light_aspect::diffuse:
                            temp_color = temp_light->getDiffuseColor();
                            break;

                        case Light_aspect::specular:
                            temp_color = temp_light->getSpecularColor();
                            break;
                    }
                    renderer.setColor(temp_color.r*255, temp_color.g*255, temp_color.b*255);
                } else {
                    ofLog() << "<no light selected>";
                }
                break;
            }

            case Select_3D::shader:
                switch (key) {
                    case 49: // touche 1
                        renderer.shader_active = ShaderType::color_fill;
                        renderer.number_of_light = 1;
                        ofLog() << "<color fill shader selected>";
                        break;

                    case 50: // touche 2
                        renderer.shader_active = ShaderType::lambert;
                        renderer.number_of_light = 1;
                        ofLog() << "<lambert shader selected>";
                        break;

                    case 51: // touche 3
                        renderer.shader_active = ShaderType::gouraud;
                        renderer.number_of_light = 1;
                        ofLog() << "<gouraud shader selected>";
                        break;

                    case 52: // touche 4
                        renderer.shader_active = ShaderType::phong;
                        renderer.number_of_light = 1;
                        ofLog() << "<phong shader selected>";
                        break;

                    case 53: // touche 5
                        renderer.shader_active = ShaderType::blinn_phong;
                        renderer.number_of_light = 1;
                        ofLog() << "<blinn-phong shader selected>";
                        break;

                    case 54: // touche 6
                        renderer.shader_active = ShaderType::double_light;
                        renderer.number_of_light = 2;
                        ofLog() << "<double light blinn-phong shader selected>";
                        break;

                    case 55: //touche 7
                        renderer.shader_active = ShaderType::triple_light;
                        renderer.number_of_light = 3;
                        ofLog() << "<triple light blinn-phong shader selected>";
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    } else {
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
                    ofLog() << "<key released: " << key << ">"; // Useful for fast key recognition
                    break;
            }
        } else {
            switch (key) {
                case 8: // backspace
                    renderer.deleteSelection();
                    break;

                case 127: // delete, same as backspace
                    renderer.deleteSelection();
                    break;

                case 122: // z button
                    if (renderer.is_ctrl_pressed) {
                        if (renderer.is_selected) {
                            renderer.releaseWithNoChange();
                        } else {
                            renderer.undo();
                        }
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
    renderer.releaseSelection();

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
	renderer.screenWidth = ofGetWidth();
	renderer.screenHeight = ofGetHeight();
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
