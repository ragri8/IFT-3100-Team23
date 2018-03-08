#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"

class Renderer
{
public:
	
	float screenWidth;
	float screenHeight;
	
	bool is2D;

	//Curseur
	int mousePressX;
	int mousePressY;

	int mousePosX;
	int mousePosY;

	bool isMouseButtonPressed;

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
	ofColor currentColor;
	ofxPanel color_picker_gui;
	ofxToggle rgbMode;
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
	ofxButton boutonEllipse;
	ofxButton boutonRectangle;
	ofxButton boutonTriangle;
	ofxButton boutonTriangleRectangle;

	ofxLabel labelPropriteteDuDessin;
	ofxIntSlider sliderEpaisseurLigneContour;

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
	void boutonEllipsePressed();
	void boutonRectanglePressed();
	void boutonTrianglePressed();
	void boutonTriangleRectanglePressed();
	void boutonMode2DPressed();
	void boutonMode3DPressed();
	void boutonImporterImagePressed();
	void boutonExporterImagePressed();
	void boutonUndoPressed();
	void boutonRedoPressed();

	void boutonTetraedrePressed();
	void boutonOctaedrePressed();
	void boutonLapinPressed();
	void boutonDragonPressed();




	void setup();
	void draw();
	void update();

	void image_export(const std::string name, const std::string extension) const;

	//Curseur
	void dessinerCurseur(float x, float y) const;
	void dessinerCurseurEtoile(float x, float y) const;
	void dessinerCurseurTriforce(float x, float y) const;
	void dessinerCurseurPoint(float x, float y) const;
	void dessinerCurseurVise(float x, float y) const;
	void dessinerCurseurFleche(float x, float y) const;
	void dessinerCurseurPeace(float x, float y) const;


	//Geometrie
	void genererModele3D();
	void genererTetraedre();
	void genererOctaedre();

	//Color picker
	void rgbModeSwitched(bool &rgbMode);

};