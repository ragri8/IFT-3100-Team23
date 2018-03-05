#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Renderer
{
public:
	
	float screenWidth;
	float screenHeight;
	
	
	//*******************************************//
	//********************GUI********************//
	//*******************************************//

	//menu general
	ofxPanel menu;
	ofxLabel titreMenu;
	ofxButton boutonMode2D;
	ofxButton boutonMode3D;
	ofxButton boutonImporterImage;
	ofxButton boutonExporterImage;
	ofxButton boutonUndo;
	ofxButton boutonRedo;


	//interface dessin
	ofxPanel dessin;
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



	void setup();
	void draw();
	void update();

	void image_export(const std::string name, const std::string extension) const;



};