#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "model2D.h"
#include "primitives/line.h"
#include "primitives/rectangle.h"
#include "primitives/circle.h"
#include "primitives/triangleRect.h"
#include "historic.h"
#include "ofxAssimpModelLoader.h"
#include <cmath>

enum class DrawTool {select, primitive};
enum class DrawPrimitive {line, circle, rectangle, triangleRect};

class Renderer {
public:

	float screenWidth;
	float screenHeight;

	bool is2D;
    bool is_filled;

	//Curseur
	float mouse_press_x;
	float mouse_press_y;

	float mouse_current_x;
	float mouse_current_y;
	bool is_mouse_button_pressed;
	bool is_mouse_button_legit;
	float current_thickness;
	Primitive* preview_primitive;
    bool is_preview;
    bool is_selected;
	DrawTool draw_tool;
	DrawPrimitive draw_primitive;
    float origin_slider_x;
    float origin_slider_y;
    float temp_alpha;

	Model2D model2D;
	History history;
	ofImage background_image;
	bool is_ctrl_pressed;
	bool is_background_image_loaded;
	bool is_menu_displayed;
    bool is_current_primitive_selected;

	//Geometrie
	bool isGenererTetraedre;
	bool isGenererOctaedre;

	//Modele 3D
	bool isGenererModele3D;
	ofxAssimpModelLoader modele;
	ofLight light;

	bool isActiveTranslation3D;
	bool isActiveRotationX3D;
	bool isActiveRotationY3D;
	bool isActiveRotationZ3D;
	bool isActiveProportion3D;

	//Color picker
	ofColor current_color;
	ofxPanel color_picker_gui;
	ofxToggle rgbMode;
    ofxToggle fillingMode;
	ofParameter<float> redOrHue;
	ofParameter<float> greenOrSaturation;
	ofParameter<float> blueOrBrightness;
	ofParameter<float> alpha;


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
	ofxFloatSlider sliderEpaisseurLigneContour;

	ofxLabel labelCouleur;


	//interface pour modèle 3D
	ofxPanel guiModel3D;

	ofxLabel labelRotation3D;
	ofxFloatSlider sliderRotation3DX;
	ofxFloatSlider sliderRotation3DY;
	ofxFloatSlider sliderRotation3DZ;
	ofxLabel labelProportion3D;
	ofxFloatSlider sliderProportion3DX;
	ofxFloatSlider sliderProportion3DY;
	ofxFloatSlider sliderProportion3DZ;

	ofxLabel labelGenerationPrimitiveGeometrique;
	ofxButton boutonOctaedre;
	ofxButton boutonTetraedre;

	ofxLabel labelGenerationModel3D;
	ofxButton boutonLapin;
	ofxButton boutonDragon;
	ofxToggle animer;
	ofxToggle dessierBoite;




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
    void sliderEpaisseurChanged(float value);

	void boutonTetraedrePressed();
	void boutonOctaedrePressed();
	void boutonLapinPressed();
	void boutonDragonPressed();

	//Curseur
	void dessinerCurseur(float x, float y) const;
	void dessinerCurseurEtoile(float x, float y) const;
	void dessinerCurseurTriforce(float x, float y) const;
	void dessinerCurseurPoint(float x, float y) const;
	void dessinerCurseurVise(float x, float y) const;
	void dessinerCurseurFleche(float x, float y) const;
	void dessinerCurseurPeace(float x, float y) const;


	void setup();
	void draw();
	void update();

	void create_preview();
	void preview_form();
	void addForm();
	void selectObject();
    void releaseSelection();
    void deleteSelection();

	//Geometrie
	void genererModele3D();
	void genererTetraedre();
	void genererOctaedre();

	//Color picker
	void rgbModeSwitched(bool &rgbMode);
    void fillingModeSwitched(bool &fillingMode);

	void saveModif(list<Primitive*>::iterator iter, Action action);
	void undo();
	void redo();

	void load_image(const std::string path);
	void image_export(const std::string name, const std::string extension) const;

	void mouseReleased(ofMouseEventArgs & mouse);

	~Renderer();

private:
    void generate_modified_primitive();

};