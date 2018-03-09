#include "renderer.h"

void Renderer::setup() {
    ofSetFrameRate(60);

    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();

    is2D = true;

    //Curseur
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
    is_preview = false;

    //Modele 3D
    isGenererModele3D = false;
    //eclairage
    ofEnableLighting();
    light.setAmbientColor(ofColor(0, 255, 0));
    light.setDiffuseColor(ofColor(255, 255, 255));
    light.setPosition(0.0f, 0.0f, 1000.0f);
    light.enable();

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

    boutonTetraedre.addListener(this, &Renderer::boutonTetraedrePressed);
    boutonOctaedre.addListener(this, &Renderer::boutonOctaedrePressed);
    boutonLapin.addListener(this, &Renderer::boutonLapinPressed);
    boutonDragon.addListener(this, &Renderer::boutonDragonPressed);




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


    //interface pour mod�le 3D
    guiModel3D.setup();

    guiModel3D.add(labelRotation3D.setup("Rotation 3D", ""));
    guiModel3D.add(sliderRotation3DX.setup("Rotation X", 1, 1, 360));
    guiModel3D.add(sliderRotation3DY.setup("Rotation Y", 1, 1, 360));
    guiModel3D.add(sliderRotation3DZ.setup("Rotation Z", 1, 1, 360));

    guiModel3D.add(labelProportion3D.setup("Proportion 3D", ""));
    guiModel3D.add(sliderProportion3DX.setup("Proportion en X", 1, 0.5, 2));
    guiModel3D.add(sliderProportion3DY.setup("Proportion en Y", 1, 0.5, 2));
    guiModel3D.add(sliderProportion3DZ.setup("Proportion en Z", 1, 0.5, 2));

    guiModel3D.add(labelGenerationPrimitiveGeometrique.setup("Primitive geometrique 3D", ""));
    guiModel3D.add(boutonTetraedre.setup("Tetraedre"));
    guiModel3D.add(boutonOctaedre.setup("Octaedre"));

    guiModel3D.add(labelGenerationModel3D.setup("Modele 3D", ""));
    guiModel3D.add(boutonLapin.setup("Generer Lapin"));
    guiModel3D.add(boutonDragon.setup("Generer Dragon"));
    guiModel3D.add(animer.setup("Animer", false));
    guiModel3D.add(dessierBoite.setup("Dessiner boite", false));
    guiModel3D.setPosition(-guiModel3D.getWidth(), 0);

    //color picker
    rgbMode.addListener(this, &Renderer::rgbModeSwitched);
    color_picker_gui.setup();
    color_picker_gui.add(rgbMode.setup("RGB mode", true));
    color_picker_gui.add(redOrHue);
    color_picker_gui.add(greenOrSaturation);
    color_picker_gui.add(blueOrBrightness);
    color_picker_gui.add(alpha.set("alpha", 255, 0, 255));

    ofAddListener(ofEvents().mouseReleased, this, &Renderer::mouseReleased, OF_EVENT_ORDER_BEFORE_APP - 100);

}

void Renderer::draw() {
    ofClear(255, 255, 255);
    //Color picker
    if (rgbMode){
        current_color = ofColor(redOrHue, greenOrSaturation, blueOrBrightness, alpha);
    }
    if (is_background_image_loaded) {
        ofSetColor(255, 255, 255);
        background_image.draw(0.0f, 0.0f, background_image.getWidth(), background_image.getHeight());
        ofSetColor(current_color);
    }
    model2D.draw();
    if (is_menu_displayed) {
        //GUI et affichage
        guiMenu.setPosition(0, 0);
        guiMenu.draw();
        if (!is2D) {
            guiModel3D.setPosition(screenWidth - guiDessin.getWidth(), 0);
            guiModel3D.draw();
        } else {
            guiDessin.setPosition(screenWidth - guiDessin.getWidth(), 0);
            guiDessin.draw();
        }
        // dessiner le color picker
        color_picker_gui.setPosition(0, guiMenu.getHeight());
        color_picker_gui.draw();
        ofSetColor(current_color);
        ofDrawRectangle(0, color_picker_gui.getPosition().y + color_picker_gui.getHeight(), color_picker_gui.getWidth(), 20);
        ofNoFill();
        ofSetLineWidth(5);
        ofSetColor(0, 0, 0);
        ofDrawRectangle(0, color_picker_gui.getPosition().y + color_picker_gui.getHeight(), color_picker_gui.getWidth(), 20);
        ofFill();
        ofSetColor(current_color);
    }
    if (!is2D) {
        if (isGenererModele3D) {
            genererModele3D();
        } else if (isGenererTetraedre) {
            genererTetraedre();
        } else if (isGenererOctaedre) {
            genererOctaedre();
        }
    }
    if (is_mouse_button_pressed && is_mouse_button_legit && draw_tool == DrawTool::primitive && is_preview) {
        preview_form();
    }
    dessinerCurseur(mouse_current_x, mouse_current_y);
}

void Renderer::update() {}

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

void Renderer::saveModif(list<Primitive*>::iterator iter, Action action) {}

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

void Renderer::boutonTrianglePressed() {}

void Renderer::boutonTriangleRectanglePressed() {
    draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::triangleRect;
    ofLog() << "< drawing rectangular triangle enabled>";
}

void Renderer::boutonSelectionPressed() {
    draw_tool = DrawTool::select;
    ofLog() << "< selection mode enabled>";
}

//Change l'interface de modele 3D pour l'interface de dessin 2D
void Renderer::boutonMode2DPressed() {
    is2D = true;
    titreMenu.setup("Menu", "2D");
    guiDessin.setPosition(screenWidth - guiDessin.getWidth(), 0);
    guiModel3D.setPosition(-guiModel3D.getWidth(), 0);
}

//Change l'interface de dessin pour l'interface de modele 3D
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
    } else {}
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
    redo();
}

void Renderer::mouseReleased(ofMouseEventArgs & mouse) {
    ofLog() << "< Mouse released at (" << mouse.x << ", " << mouse.y << ")>";
    is_mouse_button_legit = false;
}

void Renderer::boutonTetraedrePressed() {
    isGenererModele3D = false;
    isGenererOctaedre = false;
    isGenererTetraedre = true;
}

void Renderer::boutonOctaedrePressed() {
    isGenererModele3D = false;
    isGenererTetraedre = false;
    isGenererOctaedre = true;
}

//Si on appuie sur le bouton lapin, le modele 3D devient le lapin
void Renderer::boutonLapinPressed() {
    isGenererOctaedre = false;
    isGenererTetraedre = false;
    modele.loadModel("lapin.obj");
    isGenererModele3D = true;
}

//Si on appuie sur le bouton dragon, le modele 3D devient le dragon
void Renderer::boutonDragonPressed(){
    isGenererOctaedre = false;
    isGenererTetraedre = false;
    modele.loadModel("dragon.obj");
    isGenererModele3D = true;
}




//***************************************************//
//*******************Curseurs************************//
//***************************************************//

//Determine quel curseur utiliser
void Renderer::dessinerCurseur(float x, float y) const {
    ofSetLineWidth(2);

    if (is2D) {
        dessinerCurseurTriforce(x, y);
    }
    else {
        dessinerCurseurEtoile(x, y);
    }
}

//Curseur Etoile
void Renderer::dessinerCurseurEtoile(float x, float y) const {

    float taille = 10.0f;
    if (is_mouse_button_pressed) {
        ofSetColor(255, 0, 0);
    }
    else {
        ofSetColor(223, 238, 26);
    }
    ofDrawLine(x, y - (taille / 4) - taille, x+taille/4, y - (taille / 4));
    ofDrawLine(x, y - (taille / 4) - taille, x-taille/4, y - (taille / 4));
    ofDrawLine(x + taille / 4, y - (taille / 4), x + (taille / 4)+taille, y);
    ofDrawLine(x - taille / 4, y - (taille / 4), x - (taille / 4) - taille, y);
    ofDrawLine(x + (taille / 4) + taille, y, x + taille / 4,y + (taille / 2) - (taille / 4));
    ofDrawLine(x - (taille / 4) - taille, y, x - taille / 4, y + (taille / 2) - (taille / 4));
    ofDrawLine(x + taille / 4, y + (taille / 2) - (taille / 4), x, y+(taille)+(taille/2) - (taille / 4));
    ofDrawLine(x - taille / 4, y + (taille / 2) - (taille / 4), x, y + taille + (taille / 2) - (taille / 4));
}

//Curseur Triforce
void Renderer::dessinerCurseurTriforce(float x, float y) const {
    float taille = 20.0f;

    if (is_mouse_button_pressed) {
        ofSetColor(255,0,0);
    }
    else {
        ofSetColor(223, 238, 26);
    }
    ofDrawLine(x, y, x, y+ taille);
    ofDrawLine(x, y, x - taille, y);
    ofDrawLine(x, y+ taille, x- taille, y);
    ofDrawLine(x, y+ taille / 2, x- taille/ 2, y);
    ofDrawLine(x-taille/2, y, x- taille / 2, y+ taille / 2);
    ofDrawLine(x, y+ taille / 2, x-taille/2, y+ taille / 2);
}

//Curseur Point
void Renderer::dessinerCurseurPoint(float x, float y) const {
    if (is_mouse_button_pressed) {
        ofSetColor(255, 0, 0);
    }
    else {
        ofSetColor(0);
    }
    ofDrawCircle(x, y, 5);
}

//Curseur Vise
void Renderer::dessinerCurseurVise(float x, float y) const {
    float offset = 5.0f;
    float taille = 12.0f;

    ofSetColor(0);
    ofDrawLine(x+offset, y, x+offset+taille, y);
    ofDrawLine(x-offset, y, x-offset-taille, y);
    ofDrawLine(x, y-offset, x, y-offset-taille);
    ofDrawLine(x, y+offset, x, y+offset+taille);

    if (is_mouse_button_pressed) {
        ofSetColor(255, 0, 0);
    }
    else {
        ofSetColor(0);
    }
    ofDrawCircle(x, y, 3);
}

//Curseur Fleche
void Renderer::dessinerCurseurFleche(float x, float y) const {

    float taille = 40.0f;
    ofSetColor(0);
    ofDrawArrow(ofVec3f(x, y, 0), ofVec3f(x - taille, y + taille, 0));
    ofDrawLine(x - taille, y + taille, x - taille - (taille*0.2), y + taille);
    ofDrawLine(x - taille, y + taille, x - taille, y + taille + (taille*0.2));

    if (is_mouse_button_pressed) {
        ofSetColor(255, 0, 0);
    }
    else {
        ofSetColor(0);
    }
    ofDrawTriangle(x, y, x - taille / 4, y, x, y + taille / 4);
}

//Curseur Peace
void Renderer::dessinerCurseurPeace(float x, float y) const {

    float taille = 20.0f;
    float racineDe2 = 1.4142;
    if (is_mouse_button_pressed) {
        ofSetColor(0, 255, 0);
    }
    else {
        ofSetColor(0);
    }
    ofNoFill();
    ofDrawCircle(x, y, taille);
    ofFill();
    ofDrawLine(x, y, x, y-taille);
    ofDrawLine(x, y, x+ (taille / racineDe2), y+ (taille / racineDe2));
    ofDrawLine(x, y, x- (taille / racineDe2), y+ (taille / racineDe2));
}


void Renderer::genererModele3D() {
    ofEnableDepthTest();
    ofFill();
    ofSetLineWidth(1);
    ofSetColor(1);

    //On ajuste la proportion du modele selon les sliders de proportion
    modele.setScale(sliderProportion3DX / 2, sliderProportion3DY / 2, sliderProportion3DZ / 2);
    //On ajuste l'angle de rotation selon les sliders de rotation
    modele.setRotation(0, sliderRotation3DX, 1, 0, 0);
    modele.setRotation(1, sliderRotation3DY, 0, 1, 0);
    modele.setRotation(2, sliderRotation3DZ, 0, 0, 1);

    modele.setPosition(screenWidth / 2, screenHeight*0.75, 0);
    modele.draw(OF_MESH_FILL);
    modele.drawFaces();

    ofDisableDepthTest();
}

//genere un tetraedre
void Renderer::genererTetraedre() {
    ofFill();
    ofSetColor(current_color);
    float taille = screenHeight/4;
    float origineX = screenWidth / 2;
    float origineY = screenHeight*0.6;
    float origineZ = 0;
    //rotation en x
    float rotation3DXenYSommetDessus = sin(ofDegToRad(sliderRotation3DX))*taille;
    float rotation3DXenZSommetDessus = cos(ofDegToRad(sliderRotation3DX))*taille;
    float rotation3DXenY = sin(ofDegToRad(sliderRotation3DX))*(taille / 2);
    float rotation3DXenZ = cos(ofDegToRad(sliderRotation3DX))*(taille / 2);
    //rotation en y
    float rotation3DYenX = sin(ofDegToRad(sliderRotation3DY))*(taille / 2);
    float rotation3DYenZ = cos(ofDegToRad(sliderRotation3DY))*(taille / 2);

    float rayon = 0.375*taille;


    //sommet du dessus
    ofVec3f sommet1 = ofVec3f(origineX, origineY-((0.75*taille)+ rotation3DXenYSommetDessus)*(1/sliderProportion3DY), origineZ+ rotation3DXenZSommetDessus);
    //sommet derriere
    ofVec3f sommet2 = ofVec3f(origineX+ rotation3DYenX, origineY - (rotation3DXenY)*sliderProportion3DY, origineZ-((0.375*taille)+rotation3DXenZ+ rotation3DYenZ)*(1 / sliderProportion3DZ));
    //sommet avant droit
    ofVec3f sommet3 = ofVec3f(origineX+((taille/2)-rotation3DYenX)*sliderProportion3DX, origineY+(rotation3DXenY) * sliderProportion3DY, origineZ + ((0.375*taille)-rotation3DXenZ+ rotation3DYenZ)*sliderProportion3DZ);
    //sommet avant gauche
    ofVec3f sommet4 = ofVec3f(origineX-((taille/2)+rotation3DYenX)*(sliderProportion3DX), origineY + (rotation3DXenY * sliderProportion3DY), origineZ + ((0.375*taille) - rotation3DXenZ+ rotation3DYenZ)*sliderProportion3DZ);
    ofDrawTriangle(sommet1, sommet2, sommet3);
    ofDrawTriangle(sommet1, sommet2, sommet4);
    ofDrawTriangle(sommet1, sommet3, sommet4);
    ofDrawTriangle(sommet2, sommet3, sommet4);

    //dessin des aretes
    ofSetColor(255, 255, 255);
    ofDrawLine(sommet1, sommet2);
    ofDrawLine(sommet1, sommet3);
    ofDrawLine(sommet1, sommet4);
    ofDrawLine(sommet2, sommet3);
    ofDrawLine(sommet2, sommet4);
    ofDrawLine(sommet3, sommet4);
}

void Renderer::genererOctaedre() {}

//Color picker
void Renderer::rgbModeSwitched(bool &rgbMode) {
    if (rgbMode) {
        color_picker_gui.setName("RGB Color Picker");
        redOrHue.set("red", 191, 0, 255);
        greenOrSaturation.set("green", 191, 0, 255);
        blueOrBrightness.set("blue", 191, 0, 255);
    } else {
        color_picker_gui.setName("HSB Color Picker");
        redOrHue.set("hue", 0, 0, 360);
        greenOrSaturation.set("saturation", 100, 0, 100);
        blueOrBrightness.set("brightness", 100, 0, 100);
    }
}

Renderer::~Renderer() {}
