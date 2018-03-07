#include "renderer.h"

void Renderer::setup() {
	ofSetFrameRate(60);

	screenWidth = ofGetWidth();
	screenHeight = ofGetHeight();

	is2D = true;

	//Valeur par défaut
	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0.0f;
	is_mouse_button_pressed = false;
	current_color = ofColor(255, 0, 0);
	current_thickness = 12.0f;
	model2D = Model2D();
    draw_tool = DrawTool::primitive;
	draw_primitive = DrawPrimitive::line;

	//Ajout des écouteurs de l'interface
	boutonEllipse.addListener(this, &Renderer::boutonEllipsePressed);
	boutonRectangle.addListener(this, &Renderer::boutonRectanglePressed);
	boutonTriangle.addListener(this, &Renderer::boutonTrianglePressed);
	boutonTriangleRectangle.addListener(this, &Renderer::boutonTriangleRectanglePressed);
	boutonLigne.addListener(this, &Renderer::boutonLignePressed);

	boutonMode2D.addListener(this, &Renderer::boutonMode2DPressed);
	boutonMode3D.addListener(this, &Renderer::boutonMode3DPressed);
	boutonImporterImage.addListener(this, &Renderer::boutonImporterImagePressed);
	boutonExporterImage.addListener(this, &Renderer::boutonExporterImagePressed);
	boutonUndo.addListener(this, &Renderer::boutonUndoPressed);
	boutonRedo.addListener(this, &Renderer::boutonRedoPressed);
	



	//menu
	guiMenu.setup();
	guiMenu.add(titreMenu.setup("Menu", "2D"));
	guiMenu.add(boutonMode2D.setup("Mode 2D"));
	guiMenu.add(boutonMode3D.setup("Mode 3D"));
	guiMenu.add(boutonImporterImage.setup("Importer image"));
	guiMenu.add(boutonExporterImage.setup("Exporter image"));
	guiMenu.add(boutonUndo.setup("<-Undo"));
	guiMenu.add(boutonRedo.setup("Redo->"));

	guiMenu.setPosition(0, 0);
	

	//Interface dessin
	guiDessin.setup();
	guiDessin.add(titreDessin.setup("Dessin", ""));
	guiDessin.add(sliderPosX.setup("Position en X", screenWidth / 2, 0, screenWidth));
	guiDessin.add(sliderPosY.setup("Position en Y", screenHeight / 2, 0, screenHeight));
	guiDessin.add(sliderRotation.setup("Rotation", 0, 0, 360));

	//Conversion de la largeur (float) en string
	largeurForme = 0.0;
	std::ostringstream oss1;
	oss1 << largeurForme;
	guiDessin.add(labelLargeur.setup("Largeur", oss1.str()));
	//Conversion de l'hauteur (float) en string
	hauteurForme = 0.0;
	std::ostringstream oss2;
	oss2 << hauteurForme;
	guiDessin.add(labelHauteur.setup("Hauteur", oss2.str()));
	guiDessin.add(choixDeForme.setup("Choix de Forme", ""));
	guiDessin.add(boutonLigne.setup("Ligne"));
	guiDessin.add(boutonRectangle.setup("Rectangle"));
	guiDessin.add(boutonTriangle.setup("Triangle"));
	guiDessin.add(boutonEllipse.setup("Cercle"));
	guiDessin.add(boutonTriangleRectangle.setup("Triangle rectangle"));

	guiDessin.add(labelPropriteteDuDessin.setup("Propriete du dessin", ""));
	guiDessin.add(sliderEpaisseurLigneContour.setup("Epaisseur contour", 1, 1, 50));

	guiDessin.add(labelCouleur.setup("Couleur", ""));
	guiDessin.setPosition(screenWidth - guiDessin.getWidth(), 0);


	//interface pour modèle 3D
	guiModel3D.setup();
	
	guiModel3D.add(labelRotation3D.setup("Rotation 3D", ""));
	guiModel3D.add(sliderRotation3DX.setup("Rotation X", 0, 0, 360));
	guiModel3D.add(sliderRotation3DY.setup("Rotation Y", 0, 0, 360));
	guiModel3D.add(sliderRotation3DZ.setup("Rotation Z", 0, 0, 360));
	
	guiModel3D.add(labelGenerationPrimitiveGeometrique.setup("Primitive geometrique 3D", ""));
	guiModel3D.add(boutonPyramide.setup("Pyramide"));
	guiModel3D.add(boutonCube.setup("Cube"));

	guiModel3D.add(labelGenerationModel3D.setup("Modele 3D", ""));
	guiModel3D.add(boutonDragon.setup("Generer Dragon"));
	guiModel3D.add(boutonAngelLucy.setup("Generer Angel Lucy"));
	guiModel3D.add(animer.setup("Animer", false));
	guiModel3D.setPosition(-guiModel3D.getWidth(), 0);

	ofxButton boutonPyramide;
	ofxButton boutonCube;
	ofxButton boutonDragon;
	ofxButton boutonAngelLucy;
	
}

void Renderer::draw() {
    ofClear(255, 255, 255);
	guiMenu.draw();
	guiDessin.draw();
	guiModel3D.draw();
    model2D.draw();
	if (is_mouse_button_pressed && draw_tool == DrawTool::primitive) {
		preview_form();
	}
}

void Renderer::update() {

}

void Renderer::preview_form() {
    float x_clamp = min(max(0.0f, mouse_current_x), (float) ofGetWidth());
    float y_clamp = min(max(0.0f, mouse_current_y), (float) ofGetHeight());
	switch (draw_primitive) {
        case DrawPrimitive::line: {
            Line line = Line(current_color, mouse_press_x, mouse_press_y,
                             x_clamp, y_clamp, current_thickness);
            line.draw();
            break;
        }

        case DrawPrimitive::rectangle: {
            Rectangle rectangle = Rectangle(current_color, mouse_press_x, mouse_press_y,
                                            mouse_current_x, mouse_current_y, current_thickness);
            rectangle.draw();
            break;
        }

        case DrawPrimitive::circle: {
            Circle circle = Circle(current_color, mouse_press_x, mouse_press_y,
                                   mouse_current_x, mouse_current_y, current_thickness);
            circle.draw();
            break;
        }
	}
}

void Renderer::addForm() {
    switch (draw_primitive) {
        case DrawPrimitive::line: {
            Line line = Line(current_color, mouse_press_x, mouse_press_y,
                             mouse_current_x, mouse_current_y, current_thickness);
            model2D.addPrimitive(line);
            break;
        }

        case DrawPrimitive::rectangle: {
            Rectangle rectangle = Rectangle(current_color, mouse_press_x, mouse_press_y,
                                            mouse_current_x, mouse_current_y, current_thickness);
            model2D.addPrimitive(rectangle);
            break;
        }

        case DrawPrimitive::circle: {
            Circle circle = Circle(current_color, mouse_press_x, mouse_press_y,
                                   mouse_current_x, mouse_current_y, current_thickness);
            model2D.addPrimitive(circle);
            break;
        }
    }
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
	is2D = true;
	titreMenu.setup("Menu", "2D");
	guiDessin.setPosition(screenWidth - guiDessin.getWidth(), 0);
	guiModel3D.setPosition(-guiModel3D.getWidth(), 0);
}
void Renderer::boutonMode3DPressed() {
	is2D = false;
	titreMenu.setup("Menu", "3D");
	guiDessin.setPosition(-guiDessin.getWidth(), 0);
	guiModel3D.setPosition(screenWidth - guiModel3D.getWidth(), 0);
}

void Renderer::boutonImporterImagePressed() {
	if (is2D) {

	}
	else {

	}


}

void Renderer::boutonExporterImagePressed() {
	

}

void Renderer::boutonUndoPressed() {

}

void Renderer::boutonRedoPressed() {

}

