#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "model2D.h"
#include "primitives/line.h"
#include "primitives/rectangle.h"
#include "primitives/circle.h"
#include "primitives/triangleRect.h"

enum class DrawTool {select, primitive};
enum class DrawPrimitive {line, circle, rectangle, triangleRect};

class Renderer {
public:

	float screenWidth;
	float screenHeight;

	float mouse_press_x;
	float mouse_press_y;
	float mouse_current_x;
	float mouse_current_y;
	bool is_mouse_button_pressed;
    bool is_mouse_button_legit;
	ofColor current_color;
	float current_thickness;
	DrawTool draw_tool;
    DrawPrimitive draw_primitive;

	Model2D model2D;
    ofImage background_image;
    bool is_background_image_loaded;
    bool is_menu_displayed;
	
	bool is2D;
	
	//*******************************************//
	//********************GUI********************//
	//*******************************************//

	//menu general
	ofxPanel guiMenu;
	ofxLabel titreMenu;
	ofxButton boutonMode2D;
	ofxButton boutonMode3D;
	ofxButton boutonImporterImage;
	ofxButton boutonExporterImage;
	ofxButton boutonUndo;
	ofxButton boutonRedo;


	//interface dessin
	ofxPanel guiDessin;
	ofxLabel titreDessin;

	ofxIntSlider sliderPosX;
	ofxIntSlider sliderPosY;
	ofxIntSlider sliderRotation;

	float largeurForme;
	float hauteurForme;
	ofxLabel labelLargeur;
	ofxLabel labelHauteur;

	ofxLabel choixDeForme;

	ofxButton boutonLigne;
	ofxButton boutonCercle;
	ofxButton boutonRectangle;
	ofxButton boutonTriangle;
	ofxButton boutonTriangleRectangle;

    ofxButton boutonSelection;

	ofxLabel labelPropriteteDuDessin;
	ofxIntSlider sliderEpaisseurLigneContour;

	ofxLabel labelCouleur;


	//interface pour modèle 3D
	ofxPanel guiModel3D;

	ofxLabel labelRotation3D;
	ofxIntSlider sliderRotation3DX;
	ofxIntSlider sliderRotation3DY;
	ofxIntSlider sliderRotation3DZ;

	ofxLabel labelGenerationPrimitiveGeometrique;
	ofxButton boutonPyramide;
	ofxButton boutonCube;

	ofxLabel labelGenerationModel3D;
	ofxButton boutonDragon;
	ofxButton boutonAngelLucy;
	ofxToggle animer;



	
	//Ecouteur de l'interface
	void boutonLignePressed();
	void boutonCerclePressed();
	void boutonRectanglePressed();
	void boutonTrianglePressed();
	void boutonTriangleRectanglePressed();
    void boutonSelectionPressed();
	void boutonMode2DPressed();
	void boutonMode3DPressed();
	void boutonImporterImagePressed();
	void boutonExporterImagePressed();
	void boutonUndoPressed();
	void boutonRedoPressed();



	void setup();
	void draw();
	void update();

	void preview_form();
    void addForm();
    void selectObject();

	void load_image(const std::string path);
    void image_export(const std::string name, const std::string extension) const;

    void mouseReleased(ofMouseEventArgs & mouse);

};