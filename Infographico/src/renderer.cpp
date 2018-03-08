#include "renderer.h"

void Renderer::setup() {
	ofSetFrameRate(60);

	screenWidth = ofGetWidth();
	screenHeight = ofGetHeight();

	is2D = true;

	//Valeur par défaut
	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0.0f;
	is_mouse_button_pressed = false;
    is_mouse_button_legit = false;
    is_ctrl_pressed = false;
	current_color = ofColor(255, 0, 0);
	current_thickness = 3.0f;
	model2D = Model2D();
    history = History();
    draw_tool = DrawTool::primitive;
	draw_primitive = DrawPrimitive::line;
    is_background_image_loaded = false;
    is_menu_displayed = true;

	//Ajout des écouteurs de l'interface
	boutonCercle.addListener(this, &Renderer::boutonCerclePressed);
	boutonRectangle.addListener(this, &Renderer::boutonRectanglePressed);
	boutonTriangle.addListener(this, &Renderer::boutonTrianglePressed);
	boutonTriangleRectangle.addListener(this, &Renderer::boutonTriangleRectanglePressed);
	boutonLigne.addListener(this, &Renderer::boutonLignePressed);
    boutonSelection.addListener(this, &Renderer::boutonSelectionPressed);

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
	guiDessin.add(boutonCercle.setup("Cercle"));
	guiDessin.add(boutonTriangleRectangle.setup("Triangle rectangle"));
    guiDessin.add(boutonSelection.setup("Selection objet"));



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

    ofAddListener(ofEvents().mouseReleased, this, &Renderer::mouseReleased, OF_EVENT_ORDER_BEFORE_APP - 100);

}

void Renderer::draw() {
    ofClear(255, 255, 255);
    if (is_background_image_loaded) {
        ofSetColor(255, 255, 255);
        background_image.draw(0.0f, 0.0f, background_image.getWidth(), background_image.getHeight());
        ofSetColor(current_color);
    }
    model2D.draw();
    if (is_menu_displayed) {
        guiMenu.draw();
        guiDessin.draw();
        guiModel3D.draw();
    }
	if (is_mouse_button_pressed && is_mouse_button_legit && draw_tool == DrawTool::primitive) {
		preview_form();
	}
}

void Renderer::update() {
}

void Renderer::create_preview() {
    float x_clamp = min(max(0.0f, mouse_current_x), (float) ofGetWidth());
    float y_clamp = min(max(0.0f, mouse_current_y), (float) ofGetHeight());
    switch (draw_primitive) {
        case DrawPrimitive::line: {
            Line line = Line(current_color, mouse_press_x, mouse_press_y,
                             x_clamp, y_clamp, current_thickness);
            preview_primitive = line.clone();
            break;
        }

        case DrawPrimitive::rectangle: {
            Rectangle rectangle = Rectangle(current_color, mouse_press_x, mouse_press_y,
                                            mouse_current_x, mouse_current_y, current_thickness);
            preview_primitive = rectangle.clone();
            break;
        }

        case DrawPrimitive::circle: {
            Circle circle = Circle(current_color, mouse_press_x, mouse_press_y,
                                   mouse_current_x, mouse_current_y, current_thickness);
            preview_primitive = circle.clone();;
            break;
        }

        case DrawPrimitive::triangleRect: {
            TriangleRect triangle = TriangleRect(current_color, mouse_press_x, mouse_press_y,
                                                 mouse_current_x, mouse_current_y, current_thickness);
            preview_primitive = triangle.clone();
            break;
        }
    }
}

void Renderer::preview_form() {
    float x_clamp = min(max(0.0f, mouse_current_x), (float) ofGetWidth());
    float y_clamp = min(max(0.0f, mouse_current_y), (float) ofGetHeight());
	preview_primitive->reshape(mouse_press_x, mouse_press_y, x_clamp, y_clamp);
    preview_primitive->draw();
}

void Renderer::addForm() {
    model2D.addPrimitive(*preview_primitive);
    history.addChange(model2D.lastIndex(), Action::add, preview_primitive);
    delete preview_primitive;
}

void Renderer::selectObject() {
    if (model2D.findPrimitive(mouse_current_x, mouse_current_y)) {
        ofLog() << "< object found at (" << mouse_current_x << ", " << mouse_current_y << ")>";
    } else {
        ofLog() << "< object not found at (" << mouse_current_x << ", " << mouse_current_y << ")>";
    }
}

void Renderer::saveModif(list<Primitive*>::iterator iter, Action action) {

}

void Renderer::undo() {
    history.undo(model2D.getPrimitives());
}

void Renderer::redo() {
    history.redo(model2D.getPrimitives());
}

void Renderer::load_image(const std::string path) {
    try {
        background_image.load(path);
        is_background_image_loaded = true;
        ofLog() << "< the file has been loaded>";
    } catch (runtime_error& e) {
        ofLog() << "< file not found>";
        is_background_image_loaded = false;
    }
}

void Renderer::image_export(const string name, const string extension) const {
	ofImage exp_image;

	// extraire des données temporelles formatées
	string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

	// générer un nom de fichier unique et ordonné
	string file_name = name + time_stamp + "." + extension;

	// capturer le contenu du framebuffer actif
	exp_image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	// sauvegarder le fichier image
	exp_image.save(file_name);

	ofLog() << "<export image: " << file_name << ">";
}

//*******************************************//
//*********Ecouteur de l'interface***********//
//*******************************************//

void Renderer::boutonLignePressed() {
    draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::line;
    ofLog() << "< drawing line enabled>";
}

void Renderer::boutonCerclePressed() {
    draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::circle;
    ofLog() << "< drawing circle enabled>";
}

void Renderer::boutonRectanglePressed() {
    draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::rectangle;
    ofLog() << "< drawing rectangle enabled>";
}
void Renderer::boutonTrianglePressed() {

}

void Renderer::boutonTriangleRectanglePressed() {
    draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::triangleRect;
    ofLog() << "< drawing rectangular triangle enabled>";
}

void Renderer::boutonSelectionPressed() {
    draw_tool = DrawTool::select;
    ofLog() << "< selection mode enabled>";
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
        ofFileDialogResult result = ofSystemLoadDialog("Load file");
        if(result.bSuccess) {
            string path = result.getPath();
            load_image(path);
        }
	}
	else {

	}
}

void Renderer::boutonExporterImagePressed() {
    ofFileDialogResult result = ofSystemSaveDialog("default.jpg", "Save");
    if(result.bSuccess) {
        string path = result.getPath();
        is_menu_displayed = false;
        draw();
        image_export(path, "png");
        is_menu_displayed = true;
    }
}

void Renderer::boutonUndoPressed() {
    undo();
}

void Renderer::boutonRedoPressed() {

}

void Renderer::mouseReleased(ofMouseEventArgs & mouse) {
    ofLog() << "< Mouse released at (" << mouse.x << ", " << mouse.y << ")>";
    is_mouse_button_legit = false;
}

Renderer::~Renderer() {

}
