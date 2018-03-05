#include "renderer.h"

void Renderer::setup() {
	ofSetFrameRate(60);

	screenWidth = ofGetWidth();
	screenHeight = ofGetHeight();


	//Ajout des écouteurs de l'interface
	boutonEllipse.addListener(this, &Renderer::boutonEllipsePressed);
	boutonRectangle.addListener(this, &Renderer::boutonRectanglePressed);
	boutonTriangle.addListener(this, &Renderer::boutonTrianglePressed);
	boutonTriangleRectangle.addListener(this, &Renderer::boutonTriangleRectanglePressed);
	boutonLigne.addListener(this, &Renderer::boutonLignePressed);

	boutonUndo.addListener(this, &Renderer::boutonUndoPressed);
	boutonRedo.addListener(this, &Renderer::boutonRedoPressed);


	//menu
	menu.setup();
	menu.add(titreMenu.setup("Menu", ""));
	menu.add(boutonMode2D.setup("Mode 2D"));
	menu.add(boutonMode3D.setup("Mode 3D"));
	menu.add(boutonImporterImage.setup("Importer image"));
	menu.add(boutonExporterImage.setup("Exporter image"));
	menu.add(boutonUndo.setup("<-Undo"));
	menu.add(boutonRedo.setup("Redo->"));

	menu.setPosition(0, 0);
	

	//dessin
	dessin.setup();
	dessin.add(titreDessin.setup("Dessin", ""));
	dessin.add(sliderPosX.setup("Position en X", screenWidth / 2, 0, screenWidth));
	dessin.add(sliderPosY.setup("Position en Y", screenHeight / 2, 0, screenHeight));
	dessin.add(sliderRotation.setup("Rotation", 0, 0, 360));

	//Conversion de la largeur (float) en string
	largeurForme = 0.0;
	std::ostringstream oss1;
	oss1 << largeurForme;
	dessin.add(labelLargeur.setup("Largeur", oss1.str()));
	//Conversion de l'hauteur (float) en string
	hauteurForme = 0.0;
	std::ostringstream oss2;
	oss2 << hauteurForme;
	dessin.add(labelHauteur.setup("Hauteur", oss2.str()));
	dessin.add(choixDeForme.setup("Choix de Forme", ""));
	dessin.add(boutonLigne.setup("Ligne"));
	dessin.add(boutonRectangle.setup("Rectangle"));
	dessin.add(boutonTriangle.setup("Triangle"));
	dessin.add(boutonEllipse.setup("Cercle"));
	dessin.add(boutonTriangleRectangle.setup("Triangle rectangle"));

	dessin.add(labelPropriteteDuDessin.setup("Propriete du dessin", ""));
	dessin.add(sliderEpaisseurLigneContour.setup("Epaisseur contour", 1, 1, 50));

	dessin.add(labelCouleur.setup("Couleur", ""));
	dessin.setPosition(screenWidth - dessin.getWidth(), 0);

	
}

void Renderer::draw() {
	menu.draw();
	dessin.draw();
}

void Renderer::update() {

}

void Renderer::image_export(const string name, const string extension) const {
	ofImage image;

	// extraire des données temporelles formatées
	string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

	// générer un nom de fichier unique et ordonné
	string file_name = name + time_stamp + "." + extension;

	// capturer le contenu du framebuffer actif
	image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	// sauvegarder le fichier image
	image.save(file_name);

	ofLog() << "<export image: " << file_name << ">";
}

//*******************************************//
//*********Ecouteur de l'interface***********//
//*******************************************//

void Renderer::boutonLignePressed() {

}

void Renderer::boutonEllipsePressed() {

}

void Renderer::boutonRectanglePressed() {

}
void Renderer::boutonTrianglePressed() {

}

void Renderer::boutonTriangleRectanglePressed() {

}

void Renderer::boutonMode2DPressed() {

}
void Renderer::boutonMode3DPressed() {

}

void Renderer::boutonImporter() {

}

void Renderer::boutonExporter() {

}

void Renderer::boutonUndoPressed() {

}

void Renderer::boutonRedoPressed() {

}

