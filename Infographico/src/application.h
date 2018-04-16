#pragma once

#include "ofMain.h"
#include "renderer.h"

class Application : public ofBaseApp
{
public:

	float time_current;
	float time_last;
	float time_elapsed;

	/********************/
	bool is_key_press_plus;
	bool is_key_press_moins;
	bool is_key_press_left;
	bool is_key_press_right;

	bool is_key_press_a;
	bool is_key_press_d;
	bool is_key_press_down;
	bool is_key_press_up;
	bool is_key_press_s;
	bool is_key_press_w;
	/**********************/

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void exit();

private: 
	Renderer renderer;
		
};
