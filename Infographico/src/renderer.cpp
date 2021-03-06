#include "renderer.h"

void Renderer::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundColor(0);

    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();

    is2D = true;
    is_filled = false;

    //Curseur
    mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0.0f;
    is_mouse_button_pressed = false;
    is_mouse_button_legit = false;

    is_ctrl_pressed = false;
    currentColor = ofColor(255, 0, 0, 255);
    current_thickness = 3.0f;
    model2D = Model2D();
    history = History();
    draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::line;
    is_background_image_loaded = false;
    is_menu_displayed = true;
    is_preview = false;
    is_selected = false;

    origin_slider_x = 0;
    origin_slider_y = 0;
    temp_alpha = 0;

    selected_3D_instance = Select_3D::lumiere;
    material_aspect_selected = Material_aspect::ambient;
    light_selected_aspect = Light_aspect::ambient;

    //Modele 3D
    isGenererModele3D = false;
    //eclairage
    light_1.setPointLight();
    ofEnableLighting();
    light_1.setAmbientColor(ofColor(150, 50, 50));
    light_1.setDiffuseColor(ofColor(190, 100, 100));
    light_1.setSpecularColor(ofColor(100, 100, 100));
    light_1.setGlobalPosition(0, 50, 300);
    light_1.enable();

    light_2.setPointLight();
    light_2.setAmbientColor(ofColor(50, 50, 150));
    light_2.setDiffuseColor(ofColor(0, 0, 250));
    light_2.setSpecularColor(ofColor(50, 50, 250));
    light_2.setGlobalPosition(0, 50, 300);
    light_2.enable();

    light_3.setPointLight();
    light_3.setAmbientColor(ofColor(50, 150, 50));
    light_3.setDiffuseColor(ofColor(0, 200, 0));
    light_3.setSpecularColor(ofColor(60, 255, 60));
    light_3.setGlobalPosition(0, 50, 300);
    light_3.enable();

    ambient_light.setAmbientColor(ofColor(50, 50, 50));


    light_1_angle = ofVec3f(0, 45, 0);
    light_2_angle = ofVec3f(0, 315, 0);
    light_3_angle = ofVec3f(305, 0, 0);

    modele_angle = ofVec3f(0, 0, 0);

    //Ajout des écouteurs de l'interface
    boutonCercle.addListener(this, &Renderer::boutonCerclePressed);
    boutonRectangle.addListener(this, &Renderer::boutonRectanglePressed);
    boutonTriangle.addListener(this, &Renderer::boutonTrianglePressed);
    boutonTriangleRectangle.addListener(this, &Renderer::boutonTriangleRectanglePressed);
    boutonLigne.addListener(this, &Renderer::boutonLignePressed);
    boutonSelection.addListener(this, &Renderer::boutonSelectionPressed);
    fillingMode.addListener(this, &Renderer::fillingModeSwitched);

    boutonMode2D.addListener(this, &Renderer::boutonMode2DToggled);
	boutonMode3D.addListener(this, &Renderer::boutonMode3DToggled);
    boutonImporterImage.addListener(this, &Renderer::boutonImporterImagePressed);
    boutonExporterImage.addListener(this, &Renderer::boutonExporterImagePressed);
    boutonUndo.addListener(this, &Renderer::boutonUndoPressed);
    boutonRedo.addListener(this, &Renderer::boutonRedoPressed);

    boutonTetraedre.addListener(this, &Renderer::boutonTetraedrePressed);
    boutonOctaedre.addListener(this, &Renderer::boutonOctaedrePressed);
    boutonLapin.addListener(this, &Renderer::boutonLapinPressed);
    boutonDragon.addListener(this, &Renderer::boutonDragonPressed);

    boutonLumiere.addListener(this, &Renderer::boutonLumierePressed);
    boutonAmbient.addListener(this, &Renderer::boutonAmbientPressed);
    boutonDiffuse.addListener(this, &Renderer::boutonDiffusePressed);
    boutonSpeculaire.addListener(this, &Renderer::boutonSpeculairePressed);
    boutonShader.addListener(this, &Renderer::boutonShaderPressed);

	imageComposition.addListener(this, &Renderer::compositionToggled);
	convolutionFilter.addListener(this, &Renderer::convolutionToggled);
	proceduralTexture.addListener(this, &Renderer::proceduralToggled);
	raycastRenderer.addListener(this, &Renderer::raycastToggled);
	

    //menu
	guiMenu.setup();
	guiMenu.setName("Menu");
	guiMenu.add(boutonMode2D.set("Mode 2D", true));
	guiMenu.add(boutonMode3D.set("Mode 3D", false));
	guiMenu.add(boutonImporterImage.setup("Importer image"));
	guiMenu.add(labelSourceImage.set("None"));
	guiMenu.add(toggleAfficherImage.set("Afficher image", false));
	guiMenu.add(boutonExporterImage.setup("Exporter image"));
	guiMenu.add(labelTraitementImage.setup("Traitement d'image", ""));
	guiMenu.add(imageComposition.set("Composition", false));
	guiMenu.add(convolutionFilter.set("Filtre de convolution", false));
	guiMenu.add(proceduralTexture.set("Texture Procedurale", false));
	guiMenu.add(raycastRenderer.set("Raycast Renderer", false));

	guiMenu.add(labelCourbeParametrique.setup("Courbes parametriques", ""));
	guiMenu.add(labelPointDeControle.setup("Point de controle", ""));
	guiMenu.add(labelChoixPointDeControle.set("Choix : 1,2,3,4,5,6"));
	guiMenu.add(labelDeplacerPointDeControle.set("Deplacer : fleches"));
	guiMenu.add(toggleCourbeDeBezier.set("Courbe de Bezier", false));
	guiMenu.add(toggleCourbeDeHermite.set("Courbe de Hermite", false));
	guiMenu.add(toggleCourbeSplineDeBezier.set("Spline de Bezier", false));

    guiMenu.setPosition(0, 0);


    //Interface dessin
    guiDessin.setup();
    guiDessin.setName("Dessin 2D");
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
    guiDessin.add(fillingMode.setup("Mode remplissage", false));
    guiDessin.add(sliderEpaisseurLigneContour.setup("Epaisseur contour", current_thickness, 0.5f, 10.0f));

    guiDessin.add(boutonUndo.setup("<-Undo"));
	guiDessin.add(boutonRedo.setup("Redo->"));

    guiDessin.setPosition(screenWidth - guiDessin.getWidth(), 0);


    //interface pour modèle 3D
	guiModel3D.setup();
	guiModel3D.setName("Dessin 3D");

	guiModel3D.add(labelGenerationModel3D.setup("Modele 3D", ""));
	guiModel3D.add(boutonLapin.setup("Generer Lapin"));
	guiModel3D.add(boutonDragon.setup("Generer Dragon"));

	guiModel3D.add(labelRotation3D.setup("Rotation Modele 3D", ""));
	
	guiModel3D.add(sliderRotation3DX.setup("Rotation X", 0, 0, 360));
	guiModel3D.add(sliderRotation3DY.setup("Rotation Y", 45, 0, 360));
	guiModel3D.add(sliderRotation3DZ.setup("Rotation Z", 0, 0, 360));

	guiModel3D.add(labelProportion3D.setup("Proportion modele 3D", ""));

	guiModel3D.add(sliderProportion3DX.setup("Proportion en X", 1, 0.5, 2));
	guiModel3D.add(sliderProportion3DY.setup("Proportion en Y", 1, 0.5, 2));
	guiModel3D.add(sliderProportion3DZ.setup("Proportion en Z", 1, 0.5, 2));

	guiModel3D.add(labelEffet.setup("Effets", ""));
    guiModel3D.add(boutonLumiere.setup("Modifier les lumieres"));
    guiModel3D.add(boutonAmbient.setup("Composante ambiante"));
    guiModel3D.add(boutonDiffuse.setup("Composante diffuse"));
    guiModel3D.add(boutonSpeculaire.setup("Composante speculaire"));
    guiModel3D.add(sliderPorteeLumiere.setup("Portee lumiere", 500, 50, 2000));
    guiModel3D.add(sliderBrightness.setup("Brillance", 5, 0, 10));
    guiModel3D.add(boutonShader.setup("Choisir un shader"));
	guiModel3D.add(animer.setup("Animer", false));
	guiModel3D.add(dessierBoite.setup("Dessiner boite", false));

	//primitive geo
	guiModel3D.add(labelGenerationPrimitiveGeometrique.setup("Primitive geometrique 3D", ""));
	guiModel3D.add(boutonTetraedre.setup("Tetraedre"));
	guiModel3D.add(boutonOctaedre.setup("Octaedre"));
	

	guiModel3D.setPosition(-guiModel3D.getWidth(), 0);

    //color picker
	rgbMode.addListener(this, &Renderer::rgbModeSwitched);
	colorPickerGUI.setup();
	colorPickerGUI.add(rgbMode.setup("RGB mode", true));
	colorPickerGUI.add(redOrHue);
	colorPickerGUI.add(greenOrSaturation);
	colorPickerGUI.add(blueOrBrightness);
	colorPickerGUI.add(alpha.set("alpha", 255, 0, 255));

	//animer
	animationGrossit = true;

	// importer une image située dans ./bin/data
	currentImage.load("field.jpg");

	// sélectionner le filtre de convolution par défaut
	kernel_type = ConvolutionKernel::identity;
	kernel_name = "identity";

	// initialisation de l'interface graphique de composition de texture
	boutonImporterTexture1.addListener(this, &Renderer::boutonImporterImageTexture1);
	boutonImporterTexture2.addListener(this, &Renderer::boutonImporterImageTexture2);
	textureCompositionGUI.setup();
	textureCompositionGUI.setName("TEXTURE COMPOSITION");
	textureCompositionGUI.add(boutonImporterTexture1.setup("Import texture 1"));
	textureCompositionGUI.add(textureName1.set("None"));
	textureCompositionGUI.add(boutonImporterTexture2.setup("Import texture 2"));
	textureCompositionGUI.add(textureName2.set("None"));
	textureCompositionGUI.add(compositionAdd.set("Composition: ADD", false));

	// initialisation de l'interface graphique pour filtrage par convolution
	aiguiser.addListener(this, &Renderer::aiguiserToggled);
	detectionBordure.addListener(this, &Renderer::detectionBordureToggled);
	bosseler.addListener(this, &Renderer::bosselerToggled);
	flou.addListener(this, &Renderer::flouToggled);
	filtrageConvolutionGUI.setup();
	filtrageConvolutionGUI.setName("CONVOLUTION FILTER");
	filtrageConvolutionGUI.add(aiguiser.set("Sharpen", false));
	filtrageConvolutionGUI.add(detectionBordure.set("Edge Detection", false));
	filtrageConvolutionGUI.add(bosseler.set("Emboss", false));
	filtrageConvolutionGUI.add(flou.set("Blur", false));

	// initialisation de l'interface graphique pour texture procédural
	binaryTree.addListener(this, &Renderer::binaryTreeToggled);
	ternaryTree.addListener(this, &Renderer::ternaryTreeToggled);
	textureProceduralGUI.setup();
	textureProceduralGUI.setName("PROCEDURAL TEXTURE");
	textureProceduralGUI.add(binaryTree.set("Binary Tree", false));
	textureProceduralGUI.add(ternaryTree.set("Ternary Tree", false));
	textureProceduralGUI.add(branchLength.set("branch length", 100, 100, 300));
	textureProceduralGUI.add(angle.set("branch angle", 30, 0, 360));

	// initialisation de l'interface graphique pour ray tracing
	renderRayCastImage.addListener(this, &Renderer::boutonRenderRayCastImagePressed);
	viewLastRenderedImage.addListener(this, &Renderer::viewLastRayCastImageToggled);
	rayCasterGUI.setup();
	rayCasterGUI.setName("RAY CASTING");
	rayCasterGUI.add(widthOfRenderedImage.set("Raycast image width", 128, 100, 512));
	rayCasterGUI.add(heightOfRenderedImage.set("Raycast image height", 128, 100, 512));
	rayCasterGUI.add(raysPerPixel.set("Rays per pixel", 20, 10, 100));
	rayCasterGUI.add(renderRayCastImage.setup("Render ray cast image"));
	rayCasterGUI.add(viewLastRenderedImage.set("View last ray cast",false));

    ofAddListener(ofEvents().mouseReleased, this, &Renderer::mouseReleased, OF_EVENT_ORDER_BEFORE_APP - 100);

	//Camera
	camera_position = { 0.0f, 0.0f, 0.0f };
	camera_target = { 0.0f, 0.0f, 0.0f };

	camera_near = 50.0f;
	camera_far = 1750.0f;

	speed_delta = 250.0f;

	is_camera_move_left = false;
	is_camera_move_right = false;
	is_camera_move_up = false;
	is_camera_move_down = false;
	is_camera_move_forward = false;
	is_camera_move_backward = false;

    // Shaders
    shader_color_fill.load(
            "shader/color_fill_330_vs.glsl",
            "shader/color_fill_330_fs.glsl");

    shader_lambert.load(
            "shader/lambert_330_vs.glsl",
            "shader/lambert_330_fs.glsl");

    shader_gouraud.load(
            "shader/gouraud_330_vs.glsl",
            "shader/gouraud_330_fs.glsl");

    shader_phong.load(
            "shader/phong_330_vs.glsl",
            "shader/phong_330_fs.glsl");

    shader_blinn_phong.load(
            "shader/blinn_phong_330_vs.glsl",
            "shader/blinn_phong_330_fs.glsl");

    shader_2_light_blinn_phong.load(
            "shader/blinn_phong_330_vs.glsl",
            "shader/double_light_blinn_phong_330_fs.glsl");

    shader_3_light_blinn_phong.load(
            "shader/blinn_phong_330_vs.glsl",
            "shader/triple_light_blinn_phong_330_fs.glsl");

    shader_lights.load(
            "shader/lambert_330_vs.glsl",
            "shader/lambert_330_fs.glsl");

    shader_lights.begin();
    shader_lights.setUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
    shader_lights.setUniform3f("lightAmbient", 1.0f, 1.0f, 1.0f);
    shader_lights.setUniform1f("lightRange", 50.0f);
    shader_lights.setUniform1f("fogOpacity", 0.0f);
    shader_lights.end();

    shader_active = ShaderType::blinn_phong;

    shader = &shader_blinn_phong;

    shader->begin();
    shader->setUniform1f("fogOpacity", 0.0f);
    shader->end();

    // shininess is a value between 0 - 128, 128 being the most shiny //
    material_basic.setShininess( 100 );
    // the light highlight of the material //
    material_basic.setSpecularColor(ofColor(255, 225, 225));
    material_basic.setDiffuseColor(ofColor(150, 100, 80));
    material_basic.setAmbientColor(ofColor(180, 80, 40));

    primitive_color = ofColor(200, 0, 150, 180);

	ofEnableDepthTest();
	resetCamera();

	setup_camera();
	ofDisableDepthTest();

	//Courbe parametrique
	isCourbeParametriqueActive = false;
	resolutionCourbe = 100;

	curveId = CurveType::bezier;
	resetCourbeParametrique();
	vitessePointDeControle = 250.0f;
	//surface parametrique
	isSurfaceParametriqueActive = false;
	resolutionSurface = 100;
	rayonPointDeControle = 12;
	resetSurfaceParametrique();

	for (int i = 0; i <= resolutionSurface; ++i) {
		lineRendererC1.addVertex(ofPoint());
	}
	for (int i = 0; i <= resolutionSurface; ++i) {
		lineRendererC2.addVertex(ofPoint());
	}
	for (int i = 0; i <= resolutionSurface; ++i) {
		lineRendererC3.addVertex(ofPoint());
	}
	for (int i = 0; i <= resolutionSurface; ++i) {
		lineRendererC4.addVertex(ofPoint());
	}

	//triangulation
	isTriangulation = false;

	//brume
	brumeActiver = false;

	//interface brume
	guiModel3D.add(toogleActiverBrume.set("Activer brume", false));
    guiModel3D.add(sliderBrume.setup("Densite brume", 0.2f, 0.0f, 1.0f));
	//interface camera
	guiModel3D.add(labelCamera.setup("Camera", ""));
	guiModel3D.add(labelBougerCamera.setup("Pour bouger", "Fleches"));
	guiModel3D.add(labelZoomCamera.setup("Zoom", "+, -"));
	guiModel3D.add(toggleFrontCamera.set("Camera de devant", true));
	guiModel3D.add(toggleBackCamera.set("Camera de derriere", false));
	guiModel3D.add(toggleLeftCamera.set("Camera de gauche", false));
	guiModel3D.add(toggleRightCamera.set("Camera de droite", false));
	guiModel3D.add(toggleTopCamera.set("Camera du dessus", false));
	guiModel3D.add(toggleBottomCamera.set("Camera du dessous", false));
	guiModel3D.add(labelModeDeProjection.setup("Mode de projection", ""));
	guiModel3D.add(toggleProjectionPerspective.set("Projection en perspective", true));
	guiModel3D.add(toggleProjectionOrthogonale.set("Projection orthogonale", false));
	//interface surface parametrique
	guiModel3D.add(labelSurfaceParametrique.setup("Surface parametrique", ""));
	guiModel3D.add(labelPointDeControleSurface.setup("Point de controle", ""));
	guiModel3D.add(labelChoixPointDeControleSurface.set("Choix : 1,2,3,4,5,6,7,8"));
	guiModel3D.add(labelDeplacerPointDeControleSurface.set("Deplacer : w,a,s,d"));
	guiModel3D.add(toggleSurfaceDeCoons.set("Surface de Coons", false));
	//interface triangulation
	guiModel3D.add(toogleTriangulation.set("Ajouter triangulation", false));
	//interface tesselation
	guiModel3D.add(sliderNiveauTesselation.setup("Niveau de tesselation", 4, 1, 4));

	toggleFrontCamera.addListener(this, &Renderer::toggleFrontCameraPressed);
	toggleBackCamera.addListener(this, &Renderer::toggleBackCameraPressed);
	toggleLeftCamera.addListener(this, &Renderer::toggleLeftCameraPressed);
	toggleRightCamera.addListener(this, &Renderer::toggleRightCameraPressed);
	toggleTopCamera.addListener(this, &Renderer::toggleTopCameraPressed);
	toggleBottomCamera.addListener(this, &Renderer::toggleBottomCameraPressed);

    toggleFrontCamera.set(true);

	toggleProjectionOrthogonale.addListener(this, &Renderer::toggleProjectionOrthogonalePressed);
	toggleProjectionPerspective.addListener(this, &Renderer::toggleProjectionPerspectivePressed);

	//interface courbe parametrique
	toggleCourbeDeBezier.addListener(this, &Renderer::toggleCourbeDeBezierPressed);
	toggleCourbeDeHermite.addListener(this, &Renderer::toggleCourbeDeHermitePressed);
	toggleCourbeSplineDeBezier.addListener(this, &Renderer::toggleCourbeSplineDeBezierPressed);

	//interface surface parametrique
	toggleSurfaceDeCoons.addListener(this, &Renderer::toggleSurfaceDeCoonsPressed);

	//interface triangulation
	toogleTriangulation.addListener(this, &Renderer::toogleTriangulationPressed);

	//interface brume
	toogleActiverBrume.addListener(this, &Renderer::toggleActiverBrumePressed);

}

void Renderer::draw() {
    ofClear(255, 255, 255);
    current_thickness = sliderEpaisseurLigneContour;
    //Color picker
    if (rgbMode){
        currentColor = ofColor(redOrHue, greenOrSaturation, blueOrBrightness, alpha);
    } else {
		currentColor = ofColor::fromHsb(redOrHue, greenOrSaturation, blueOrBrightness, alpha);
	}
    draw2D();
    if (!is2D) {
        draw3D();
    }
    if (is_menu_displayed) {
        drawGui();
    }
    if (is_filled) {
        ofFill();
    } else {
        ofNoFill();
    }
    if (is_mouse_button_pressed && is_mouse_button_legit && draw_tool == DrawTool::primitive && is_preview) {
        preview_form();
    }
    if (is_selected) {
        preview_primitive->changeColor(currentColor);
        preview_primitive->translate(sliderPosX-origin_slider_x, sliderPosY-origin_slider_y);
        origin_slider_x = sliderPosX;
        origin_slider_y = sliderPosY;
        preview_primitive->setFill(is_filled);
        preview_primitive->setThickness(current_thickness);
        preview_primitive->draw();
    }
    dessinerCurseur(mouse_current_x, mouse_current_y);
    ofSetColor(255, 255, 255);
}

void Renderer::draw2D() {
    if (compositionAdd && is_texture1_loaded && is_texture2_loaded) {
        //if (texture1.getWidth() > 0 && texture1.getHeight() > 0 && texture2.getWidth() > 0 && texture2.getHeight() > 0)
        //	ofSetWindowShape(max(texture1.getWidth(), texture2.getWidth()), max(texture1.getHeight(), texture2.getHeight()));
        //ofEnableBlendMode(OF_BLENDMODE_ADD);
        texture1.draw(guiMenu.getWidth(), 0, texture1.getWidth(), texture1.getHeight());
        ofSetColor(255, 255, 255, 150);
        texture2.draw(guiMenu.getWidth(), 0, texture2.getWidth(), texture2.getHeight());
        ofSetColor(255, 255, 255, 255);
        //ofDisableBlendMode();
    }
    else if (aiguiser || detectionBordure || bosseler || flou) {        
        filteredImage.draw(guiMenu.getWidth(), 0, currentImage.getWidth(), currentImage.getHeight());
    }
    else if (ternaryTree || binaryTree) {
        ofSetColor(currentColor);
        ofSetLineWidth(2);

        if (ternaryTree) {
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
            drawTernaryTree(branchLength);
            ofPopMatrix();
        }
        else if (binaryTree) {
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
            drawBinaryTree(branchLength);
            ofPopMatrix();
        }
		ofSetColor(255, 255, 255, 255);
    }
	else if (raycastRenderer && viewLastRenderedImage) {
		lastRayCastResult.draw(guiMenu.getWidth(), 0, lastRayCastResult.getWidth(), lastRayCastResult.getHeight());
	}
    else if(toggleAfficherImage) {
        currentImage.draw(guiMenu.getWidth(), 0, currentImage.getWidth(), currentImage.getHeight());
    }
    // rendu 2D de la scène
    model2D.draw();
    if (isCourbeParametriqueActive) {
        switch (curveId) {
        case(CurveType::bezier):
            ofSetColor(150, 150, 150);
            ofSetLineWidth(4.0f);
            ofDrawLine(pointDeControle1.x, pointDeControle1.y, pointDeControle2.x, pointDeControle2.y);
            ofDrawLine(pointDeControle3.x, pointDeControle3.y, pointDeControle4.x, pointDeControle4.y);

            ofSetColor(66, 215, 244);
            ofSetLineWidth(8.0f);
            lineRenderer.draw();

            ofSetColor(65, 71, 244);
            ofDrawEllipse(pointDeControle1.x, pointDeControle1.y, rayonPointDeControle, rayonPointDeControle);
            ofDrawEllipse(pointDeControle2.x, pointDeControle2.y, rayonPointDeControle, rayonPointDeControle);
            ofDrawEllipse(pointDeControle3.x, pointDeControle3.y, rayonPointDeControle, rayonPointDeControle);
            ofDrawEllipse(pointDeControle4.x, pointDeControle4.y, rayonPointDeControle, rayonPointDeControle);

            break;

        case(CurveType::hermite):
            ofSetColor(150, 150, 150);
            ofSetLineWidth(4.0f);
            ofDrawLine(pointDeControle1.x, pointDeControle1.y, pointDeControle2.x, pointDeControle2.y);
            ofDrawLine(pointDeControle3.x, pointDeControle3.y, pointDeControle4.x, pointDeControle4.y);

            ofSetColor(66, 215, 244);
            ofSetLineWidth(8.0f);
            lineRenderer.draw();

            ofSetColor(65, 71, 244);
            ofDrawEllipse(pointDeControle1.x, pointDeControle1.y, rayonPointDeControle, rayonPointDeControle);
            ofDrawEllipse(pointDeControle2.x, pointDeControle2.y, rayonPointDeControle, rayonPointDeControle);
            ofDrawEllipse(pointDeControle3.x, pointDeControle3.y, rayonPointDeControle, rayonPointDeControle);
            ofDrawEllipse(pointDeControle4.x, pointDeControle4.y, rayonPointDeControle, rayonPointDeControle);
            break;

        case(CurveType::splineDeBezier):
            ofSetColor(150, 150, 150);
            ofSetLineWidth(4.0f);
            ofDrawLine(pointDeControle1.x, pointDeControle1.y, pointDeControle2.x, pointDeControle2.y);
            ofDrawLine(pointDeControle3.x, pointDeControle3.y, pointDeControle4.x, pointDeControle4.y);
            ofDrawLine(pointDeControle5.x, pointDeControle5.y, pointDeControle6.x, pointDeControle6.y);

            ofSetColor(66, 215, 244);
            ofSetLineWidth(8.0f);
            lineRenderer.draw();

            ofSetColor(65, 71, 244);
            ofDrawEllipse(pointDeControle1.x, pointDeControle1.y, rayonPointDeControle, rayonPointDeControle);
            ofDrawEllipse(pointDeControle2.x, pointDeControle2.y, rayonPointDeControle, rayonPointDeControle);
            ofDrawEllipse(pointDeControle3.x, pointDeControle3.y, rayonPointDeControle, rayonPointDeControle);
            ofDrawEllipse(pointDeControle4.x, pointDeControle4.y, rayonPointDeControle, rayonPointDeControle);
            ofDrawEllipse(pointDeControle5.x, pointDeControle5.y, rayonPointDeControle, rayonPointDeControle);
            ofDrawEllipse(pointDeControle6.x, pointDeControle6.y, rayonPointDeControle, rayonPointDeControle);
            break;

        default:
            break;
        }
    }	
}

void Renderer::draw3D() {
    //rendu 3D de la scène avec la caméra
    camera->begin();

    if (camera_active != Camera::front)
        camera_front.draw();
    if (camera_active != Camera::back)
        camera_back.draw();
    if (camera_active != Camera::left)
        camera_left.draw();
    if (camera_active != Camera::right)
        camera_right.draw();
    if (camera_active != Camera::top)
        camera_top.draw();
    if (camera_active != Camera::down)
        camera_down.draw();

    shader->begin();

    shader->setUniform3f("lightPosition", light_1.getGlobalPosition().rotate(light_1_angle.x, light_1_angle.y, light_1_angle.z) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
    if (number_of_light > 1) {
        shader->setUniform3f("lightPosition2", light_2.getGlobalPosition().rotate(light_2_angle.x, light_2_angle.y, light_2_angle.z) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
        if (number_of_light > 2) {
            shader->setUniform3f("lightPosition3", light_3.getGlobalPosition().rotate(light_3_angle.x, light_3_angle.y, light_3_angle.z) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
        }
    }
    shader->end();

    ofEnableDepthTest();
    if (brumeActiver) {
        //activerBrume();
    }
    ofDisableDepthTest();

    if (isSurfaceParametriqueActive) {
        ofEnableDepthTest();

        shader->begin();

        ofSetColor(150, 150, 150);
        ofSetLineWidth(4.0f);
        ofDrawLine(pointDeControleSurface1.x, pointDeControleSurface1.y, pointDeControleSurface1.z, pointDeControleSurface2.x, pointDeControleSurface2.y, pointDeControleSurface2.z);
        ofDrawLine(pointDeControleSurface3.x, pointDeControleSurface3.y, pointDeControleSurface3.z, pointDeControleSurface4.x, pointDeControleSurface4.y, pointDeControleSurface4.z);
        ofDrawLine(pointDeControleSurface5.x, pointDeControleSurface5.y, pointDeControleSurface5.z, pointDeControleSurface6.x, pointDeControleSurface6.y, pointDeControleSurface6.z);
        ofDrawLine(pointDeControleSurface7.x, pointDeControleSurface7.y, pointDeControleSurface7.z, pointDeControleSurface8.x, pointDeControleSurface8.y, pointDeControleSurface8.z);

        ofSetColor(66, 215, 244);
        ofSetLineWidth(8.0f);

        lineRendererC1.draw();
        lineRendererC2.draw();
        lineRendererC3.draw();
        lineRendererC4.draw();

        ofSetColor(65, 71, 244);
        ofDrawEllipse(pointDeControleSurface1.x, pointDeControleSurface1.y, pointDeControleSurface1.z, rayonPointDeControle, rayonPointDeControle);
        ofDrawEllipse(pointDeControleSurface2.x, pointDeControleSurface2.y, pointDeControleSurface2.z, rayonPointDeControle, rayonPointDeControle);
        ofDrawEllipse(pointDeControleSurface3.x, pointDeControleSurface3.y, pointDeControleSurface3.z, rayonPointDeControle, rayonPointDeControle);
        ofDrawEllipse(pointDeControleSurface4.x, pointDeControleSurface4.y, pointDeControleSurface4.z, rayonPointDeControle, rayonPointDeControle);
        ofDrawEllipse(pointDeControleSurface5.x, pointDeControleSurface5.y, pointDeControleSurface5.z, rayonPointDeControle, rayonPointDeControle);
        ofDrawEllipse(pointDeControleSurface6.x, pointDeControleSurface6.y, pointDeControleSurface6.z, rayonPointDeControle, rayonPointDeControle);
        ofDrawEllipse(pointDeControleSurface7.x, pointDeControleSurface7.y, pointDeControleSurface7.z, rayonPointDeControle, rayonPointDeControle);
        ofDrawEllipse(pointDeControleSurface8.x, pointDeControleSurface8.y, pointDeControleSurface8.z, rayonPointDeControle, rayonPointDeControle);

		if (isTriangulation) {
			maillageDeTriangulation.draw();
		}
		else {
			ofSetColor(46, 48, 51);
			ofSetLineWidth(2.0f);
			for (int i = 0; i < resolutionSurface; i++) {
				lignesDeSurfaceV.at(i).draw();
			}
			for (int i = 0; i < resolutionSurface; i++) {
				lignesDeSurfaceU.at(i).draw();
			}
		}
        shader->end();

        ofDisableDepthTest();
    }
    if (isGenererModele3D) {
        genererModele3D();
        // générer des sphères pour représenter les sources de lumière
        drawLightSources();
        if (dessierBoite) {
            genererBoite();
        }
    } else if (isGenererTetraedre) {
        genererTetraedre();
    } else if (isGenererOctaedre) {
        genererOctaedre();
    }

    ofSetColor(currentColor);
    ofFill();

    camera->end();
    ofDisableLighting();
}

void Renderer::drawGui() {
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
    colorPickerGUI.setPosition(0, guiMenu.getHeight());
    colorPickerGUI.draw();
    ofFill();
    ofSetColor(currentColor);
    ofDrawRectangle(0, colorPickerGUI.getPosition().y + colorPickerGUI.getHeight(), colorPickerGUI.getWidth(), 20);
    ofNoFill();
    ofSetLineWidth(3);
    ofSetColor(0, 0, 0);
    ofDrawRectangle(0, colorPickerGUI.getPosition().y + colorPickerGUI.getHeight(), colorPickerGUI.getWidth(), 20);
    ofFill();

    // definir position de l'interface graphique de composition de texture
    if (imageComposition) {
        textureCompositionGUI.setPosition(0, colorPickerGUI.getPosition().y + colorPickerGUI.getHeight() + 20);
        textureCompositionGUI.draw();
    }
    // definir position de l'interface graphique de filtrage par convolution
    if (convolutionFilter) {
        filtrageConvolutionGUI.setPosition(0, colorPickerGUI.getPosition().y + colorPickerGUI.getHeight() + 20);
        filtrageConvolutionGUI.draw();
    }
    // definir position de l'interface graphique de texture procédural
    if (proceduralTexture) {
        textureProceduralGUI.setPosition(0, colorPickerGUI.getPosition().y + colorPickerGUI.getHeight() + 20);
        textureProceduralGUI.draw();
    }
	// definir position de l'interface graphique de ray tracing
	if (raycastRenderer) {
		rayCasterGUI.setPosition(0, colorPickerGUI.getPosition().y + colorPickerGUI.getHeight() + 20);
		rayCasterGUI.draw();
	}
}

void Renderer::update() {
	if (isGenererModele3D) {
		if (animer) {
			animerMaillage();
		}
	}
	if (!is2D) {
        updateSelection();
		ofEnableDepthTest();
		time_current = ofGetElapsedTimef();
		time_elapsed = time_current - time_last;
		time_last = time_current;

		speed_translation = speed_delta * time_elapsed;

		if (is_camera_move_left) {
			camera->truck(-speed_translation);
		}
		if (is_camera_move_right)
			camera->truck(speed_translation);

		if (is_camera_move_up)
			camera->boom(speed_translation);
		if (is_camera_move_down)
			camera->boom(-speed_translation);

		if (is_camera_move_forward)
			camera->dolly(-speed_translation);
		if (is_camera_move_backward)
			camera->dolly(speed_translation);
		ofDisableDepthTest();

		if (isSurfaceParametriqueActive) {

			for (index = 0; index <= resolutionSurface; ++index) {
				bezier(
					index / (float)resolutionSurface,
					pointDeControleSurface1.x, pointDeControleSurface1.y, pointDeControleSurface1.z,
					pointDeControleSurface2.x, pointDeControleSurface2.y, pointDeControleSurface2.z,
					pointDeControleSurface4.x, pointDeControleSurface4.y, pointDeControleSurface4.z,
					pointDeControleSurface3.x, pointDeControleSurface3.y, pointDeControleSurface3.z,
					positionDansCourbeU.x, positionDansCourbeU.y, positionDansCourbeU.z);
				lineRendererC1[index] = positionDansCourbeU;
			}

			for (index = 0; index <= resolutionSurface; ++index) {
				bezier(
					index / (float)resolutionSurface,
					pointDeControleSurface5.x, pointDeControleSurface5.y, pointDeControleSurface5.z,
					pointDeControleSurface6.x, pointDeControleSurface6.y, pointDeControleSurface6.z,
					pointDeControleSurface8.x, pointDeControleSurface8.y, pointDeControleSurface8.z,
					pointDeControleSurface7.x, pointDeControleSurface7.y, pointDeControleSurface7.z,
					positionDansCourbeU.x, positionDansCourbeU.y, positionDansCourbeU.z);
				lineRendererC2[index] = positionDansCourbeU;
			}

			for (index = 0; index <= resolutionSurface; ++index) {
				bezier(
					index / (float)resolutionSurface,
					pointDeControleSurface1.x, pointDeControleSurface1.y, pointDeControleSurface1.z,
					pointDeControleSurface2.x, pointDeControleSurface2.y, pointDeControleSurface2.z,
					pointDeControleSurface6.x, pointDeControleSurface6.y, pointDeControleSurface6.z,
					pointDeControleSurface5.x, pointDeControleSurface5.y, pointDeControleSurface5.z,
					positionDansCourbeV.x, positionDansCourbeV.y, positionDansCourbeV.z);
				lineRendererC3[index] = positionDansCourbeV;
			}

			for (index = 0; index <= resolutionSurface; ++index) {
				bezier(
					index / (float)resolutionSurface,
					pointDeControleSurface3.x, pointDeControleSurface3.y, pointDeControleSurface3.z,
					pointDeControleSurface4.x, pointDeControleSurface4.y, pointDeControleSurface4.z,
					pointDeControleSurface8.x, pointDeControleSurface8.y, pointDeControleSurface8.z,
					pointDeControleSurface7.x, pointDeControleSurface7.y, pointDeControleSurface7.z,
					positionDansCourbeV.x, positionDansCourbeV.y, positionDansCourbeV.z);
				lineRendererC4[index] = positionDansCourbeV;
			}
			float u;
			float v;

			for (int i = 0; i < resolutionSurface; i++) {
				u = (float)(i + 1) / (float)resolutionSurface;
				for (int j = 0; j < resolutionSurface; j++) {
					v = (float)(j + 1) / (float)resolutionSurface;
					lerpu = (1 - v)*lineRendererC1[i] + v * lineRendererC2[i];
					lerpv = (1 - u)*lineRendererC3[j] + u * lineRendererC4[j];
					blerp = (1 - u)*(1 - v)*lineRendererC1[0] +
						u * (1 - v)*lineRendererC1[resolutionSurface - 1] +
						(1 - u)*v*lineRendererC2[0] + u * v*lineRendererC2[resolutionSurface - 1];
					surfaceCoons = lerpu + lerpv - blerp;
					lignesDeSurfaceV.at(i)[j] = surfaceCoons;
				}
			}

			for (int i = 0; i < resolutionSurface; i++) {
				v = (float)(i + 1) / (float)resolutionSurface;
				for (int j = 0; j < resolutionSurface; j++) {
					u = (float)(j + 1) / (float)resolutionSurface;
					lerpu = (1 - v)*lineRendererC1[j] + v * lineRendererC2[j];
					lerpv = (1 - u)*lineRendererC3[i] + u * lineRendererC4[i];
					blerp = (1 - u)*(1 - v)*lineRendererC1[0] + u * (1 - v)*lineRendererC1[resolutionSurface - 1] + (1 - u)*v*lineRendererC2[0] + u * v*lineRendererC2[resolutionSurface - 1];
					surfaceCoons = lerpu + lerpv - blerp;
					lignesDeSurfaceU.at(i)[j] = surfaceCoons;
				}
			}
			if (isTriangulation) {
				maillageDeTriangulation.clear();
				if (sliderNiveauTesselation == 4) {
					saut = 1;
				}
				else if (sliderNiveauTesselation == 3) {
					saut = 3;
				}
				else if (sliderNiveauTesselation == 2) {
					saut = 9;
				}
				else {
					saut = -1;
				}

				for (int x = 0; x < resolutionSurface; x++) {
					for (int y = 0; y < resolutionSurface; y++) {
						maillageDeTriangulation.addVertex(ofPoint(lignesDeSurfaceU.at(x)[y]));
						maillageDeTriangulation.addColor(ofColor(46, 48, 51));
					}
				}
				if (saut == -1) {
					maillageDeTriangulation.addIndex(0);
					maillageDeTriangulation.addIndex(resolutionSurface / 2);
					maillageDeTriangulation.addIndex(((resolutionSurface)*(resolutionSurface - 1)));

					maillageDeTriangulation.addIndex(((resolutionSurface)*(resolutionSurface - 1)));
					maillageDeTriangulation.addIndex(resolutionSurface / 2);
					maillageDeTriangulation.addIndex(((resolutionSurface)*(resolutionSurface - 1)) + resolutionSurface / 2);

					maillageDeTriangulation.addIndex(resolutionSurface / 2);
					maillageDeTriangulation.addIndex(((resolutionSurface)*(resolutionSurface - 1)) + resolutionSurface / 2);
					maillageDeTriangulation.addIndex(resolutionSurface - 1);

					maillageDeTriangulation.addIndex(((resolutionSurface)*(resolutionSurface - 1)) + resolutionSurface / 2);
					maillageDeTriangulation.addIndex(resolutionSurface - 1);
					maillageDeTriangulation.addIndex((resolutionSurface)*(resolutionSurface)-1);
				}
				else {
					for (int x = 0; x < resolutionSurface - 1; x += saut) {
						for (int y = 0; y < resolutionSurface - 1; y += saut) {
							maillageDeTriangulation.addIndex(x + y * resolutionSurface);
							maillageDeTriangulation.addIndex((x + saut) + y * resolutionSurface);
							maillageDeTriangulation.addIndex(x + (y + saut)*resolutionSurface);

							maillageDeTriangulation.addIndex((x + saut) + y * resolutionSurface);
							maillageDeTriangulation.addIndex((x + saut) + (y + saut)*resolutionSurface);
							maillageDeTriangulation.addIndex(x + (y + saut)*resolutionSurface);
						}
					}
				}

			}
		}
	} else {
		if (isCourbeParametriqueActive) {
			lineRenderer.clear();
			switch (curveId) {
                case CurveType::bezier:
                    for (int i = 0; i <= resolutionCourbe; ++i) {
                        lineRenderer.addVertex(ofPoint());
                    }
                    for (index = 0; index <= resolutionCourbe; ++index) {
                        bezier(
                            index / (float)resolutionCourbe,
                            pointDeControle1.x, pointDeControle1.y, pointDeControle1.z,
                            pointDeControle2.x, pointDeControle2.y, pointDeControle2.z,
                            pointDeControle4.x, pointDeControle4.y, pointDeControle4.z,
                            pointDeControle3.x, pointDeControle3.y, pointDeControle3.z,
                            positionDansCourbe.x, positionDansCourbe.y, positionDansCourbe.z);
                        lineRenderer[index] = positionDansCourbe;
                    }
                    break;

                case CurveType::hermite:
                    for (int i = 0; i <= resolutionCourbe; ++i) {
                        lineRenderer.addVertex(ofPoint());
                    }
                    for (index = 0; index <= resolutionCourbe; ++index)
                    {
                        tangente1 = pointDeControle2 - pointDeControle1;
                        tangente2 = pointDeControle3 - pointDeControle4;

                        hermite(
                            index / (float)resolutionCourbe,
                            pointDeControle1.x, pointDeControle1.y, pointDeControle1.z,
                            tangente1.x, tangente1.y, tangente1.z,
                            tangente2.x, tangente2.y, tangente2.z,
                            pointDeControle4.x, pointDeControle4.y, pointDeControle4.z,
                            positionDansCourbe.x, positionDansCourbe.y, positionDansCourbe.z);

                        lineRenderer[index] = positionDansCourbe;
                    }
                    break;

                case CurveType::splineDeBezier:
                    for (int i = 0; i <= resolutionCourbe * 2; ++i) {
                        lineRenderer.addVertex(ofPoint());
                    }
                    for (index = 0; index <= resolutionCourbe; ++index) {
                        bezier(
                            index / (float)resolutionCourbe,
                            pointDeControle1.x, pointDeControle1.y, pointDeControle1.z,
                            pointDeControle2.x, pointDeControle2.y, pointDeControle2.z,
                            pointDeControle4.x, pointDeControle4.y, pointDeControle4.z,
                            pointDeControle3.x, pointDeControle3.y, pointDeControle3.z,
                            positionDansCourbe.x, positionDansCourbe.y, positionDansCourbe.z);

                        lineRenderer[index] = positionDansCourbe;
                    }
                    for (index = 0; index <= resolutionCourbe; ++index) {
                        bezier(
                            index / (float)resolutionCourbe,
                            pointDeControle3.x, pointDeControle3.y, pointDeControle3.z,
                            pointDeControle4.x, pointDeControle4.y, pointDeControle4.z,
                            pointDeControle6.x, pointDeControle6.y, pointDeControle6.z,
                            pointDeControle5.x, pointDeControle5.y, pointDeControle5.z,
                            positionDansCourbe.x, positionDansCourbe.y, positionDansCourbe.z);

                        lineRenderer[resolutionCourbe + index] = positionDansCourbe;
                    }
                    break;

                default:
                    break;
			}
		}
	}
    updateShader();
}

void Renderer::updateSelection() {
    switch (selected_3D_instance) {
        case Select_3D::modele:
            modele_angle = ofVec3f(sliderRotation3DX, sliderRotation3DY, sliderRotation3DZ);
            break;

        case Select_3D::lumiere:
            if (rgbMode){
                currentColor = ofColor(redOrHue, greenOrSaturation, blueOrBrightness, alpha);
            } else {
                currentColor = ofColor::fromHsb(redOrHue, greenOrSaturation, blueOrBrightness, alpha);
            }
            switch (light_selected) {
                case Light_select::light1:
                    light_1_angle = ofVec3f(sliderRotation3DX, sliderRotation3DY, sliderRotation3DZ);
                    light_1.setAmbientColor(ofColor(currentColor.r, currentColor.g, currentColor.b));
                    break;

                case Light_select::light2:
                    light_2_angle = ofVec3f(sliderRotation3DX, sliderRotation3DY, sliderRotation3DZ);
                    light_2.setAmbientColor(ofColor(currentColor.r, currentColor.g, currentColor.b));
                    break;

                case Light_select::light3:
                    light_3_angle = ofVec3f(sliderRotation3DX, sliderRotation3DY, sliderRotation3DZ);
                    light_3.setAmbientColor(ofColor(currentColor.r, currentColor.g, currentColor.b));
                    break;

                case Light_select::ambient:
                    ambient_light.setAmbientColor(ofColor(currentColor.r, currentColor.g, currentColor.b));

                default:
                    break;
            }
            break;

        case Select_3D::material:
            switch (material_aspect_selected) {
                case Material_aspect::ambient:
                    material_basic.setAmbientColor(ofColor(currentColor.r, currentColor.g, currentColor.b));
                    break;

                case Material_aspect::diffuse:
                    material_basic.setDiffuseColor(ofColor(currentColor.r, currentColor.g, currentColor.b));
                    break;

                case Material_aspect::specular:
                    material_basic.setSpecularColor(ofColor(currentColor.r, currentColor.g, currentColor.b));
                    break;
            }
            break;

        case Select_3D::primitive3D:
            primitive_color = currentColor;
            modele_angle = ofVec3f(sliderRotation3DX, sliderRotation3DY, sliderRotation3DZ);
            break;

        case Select_3D::shader:
            break;

        case Select_3D::surface:
            break;
    }
}

void Renderer::updateShader() {

    switch (shader_active) {
        case ShaderType::color_fill:
            shader_name = "Color Fill";
            shader = &shader_color_fill;
            shader->begin();
            shader->setUniform3f(
                    "color",
                    light_1.getAmbientColor().r,
                    light_1.getAmbientColor().g,
                    light_1.getAmbientColor().b
            );
            shader->setUniform3f(
                    "lightAmbient",
                    ambient_light.getAmbientColor().r,
                    ambient_light.getAmbientColor().g,
                    ambient_light.getAmbientColor().b
            );
            shader->end();
            break;

        case ShaderType::lambert:
            shader_name = "Lambert";
            shader = &shader_lambert;
            shader->begin();
            shader->setUniform3f(
                    "lightColor",
                    light_1.getAmbientColor().r,
                    light_1.getAmbientColor().g,
                    light_1.getAmbientColor().b
            );
            shader->setUniform3f(
                    "lightAmbient",
                    ambient_light.getAmbientColor().r,
                    ambient_light.getAmbientColor().g,
                    ambient_light.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorAmbient",
                    material_basic.getAmbientColor().r,
                    material_basic.getAmbientColor().g,
                    material_basic.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorDiffuse",
                    material_basic.getDiffuseColor().r,
                    material_basic.getDiffuseColor().g,
                    material_basic.getDiffuseColor().b
            );
            shader->setUniform1f("lightRange", sliderPorteeLumiere);
            shader->end();
            break;

        case ShaderType::gouraud:
            shader_name = "Gouraud";
            shader = &shader_gouraud;
            shader->begin();
            shader->setUniform3f(
                    "lightColor",
                    light_1.getAmbientColor().r,
                    light_1.getAmbientColor().g,
                    light_1.getAmbientColor().b
            );
            shader->setUniform3f(
                    "lightAmbient",
                    ambient_light.getAmbientColor().r,
                    ambient_light.getAmbientColor().g,
                    ambient_light.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorAmbient",
                    material_basic.getAmbientColor().r,
                    material_basic.getAmbientColor().g,
                    material_basic.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorDiffuse",
                    material_basic.getDiffuseColor().r,
                    material_basic.getDiffuseColor().g,
                    material_basic.getDiffuseColor().b
            );
            shader->setUniform3f(
                    "colorSpecular",
                    material_basic.getSpecularColor().r,
                    material_basic.getSpecularColor().g,
                    material_basic.getSpecularColor().b
            );
            shader->setUniform1f("brightness", sliderBrightness);
            shader->setUniform1f("lightRange", sliderPorteeLumiere);
            shader->end();
            break;

        case ShaderType::phong:
            shader_name = "Phong";
            shader = &shader_phong;
            shader->begin();
            shader->setUniform3f(
                    "lightColor",
                    light_1.getAmbientColor().r,
                    light_1.getAmbientColor().g,
                    light_1.getAmbientColor().b
            );
            shader->setUniform3f(
                    "lightAmbient",
                    ambient_light.getAmbientColor().r,
                    ambient_light.getAmbientColor().g,
                    ambient_light.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorAmbient",
                    material_basic.getAmbientColor().r,
                    material_basic.getAmbientColor().g,
                    material_basic.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorDiffuse",
                    material_basic.getDiffuseColor().r,
                    material_basic.getDiffuseColor().g,
                    material_basic.getDiffuseColor().b
            );
            shader->setUniform3f(
                    "colorSpecular",
                    material_basic.getSpecularColor().r,
                    material_basic.getSpecularColor().g,
                    material_basic.getSpecularColor().b
            );
            shader->setUniform1f("brightness", sliderBrightness);
            shader->setUniform1f("lightRange", sliderPorteeLumiere);
            shader->end();
            break;

        case ShaderType::blinn_phong:
            shader_name = "Blinn-Phong";
            shader = &shader_blinn_phong;
            shader->begin();
            shader->setUniform3f(
                    "lightColor",
                    light_1.getAmbientColor().r,
                    light_1.getAmbientColor().g,
                    light_1.getAmbientColor().b
            );
            shader->setUniform3f(
                    "lightAmbient",
                    ambient_light.getAmbientColor().r,
                    ambient_light.getAmbientColor().g,
                    ambient_light.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorAmbient",
                    material_basic.getAmbientColor().r,
                    material_basic.getAmbientColor().g,
                    material_basic.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorDiffuse",
                    material_basic.getDiffuseColor().r,
                    material_basic.getDiffuseColor().g,
                    material_basic.getDiffuseColor().b
            );
            shader->setUniform3f(
                    "colorSpecular",
                    material_basic.getSpecularColor().r,
                    material_basic.getSpecularColor().g,
                    material_basic.getSpecularColor().b
            );
            shader->setUniform1f("brightness", sliderBrightness);
            shader->setUniform1f("lightRange", sliderPorteeLumiere);
            shader->end();
            break;

        case ShaderType::double_light:
            shader_name = "2-light-Blinn-Phong";
            shader = &shader_2_light_blinn_phong;
            shader->begin();
            shader->setUniform3f(
                    "lightColor",
                    light_1.getAmbientColor().r,
                    light_1.getAmbientColor().g,
                    light_1.getAmbientColor().b
            );
            shader->setUniform3f(
                    "lightColor2",
                    light_2.getAmbientColor().r,
                    light_2.getAmbientColor().g,
                    light_2.getAmbientColor().b
            );
            shader->setUniform3f(
                    "lightAmbient",
                    ambient_light.getAmbientColor().r,
                    ambient_light.getAmbientColor().g,
                    ambient_light.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorAmbient",
                    material_basic.getAmbientColor().r,
                    material_basic.getAmbientColor().g,
                    material_basic.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorDiffuse",
                    material_basic.getDiffuseColor().r,
                    material_basic.getDiffuseColor().g,
                    material_basic.getDiffuseColor().b
            );
            shader->setUniform3f(
                    "colorSpecular",
                    material_basic.getSpecularColor().r,
                    material_basic.getSpecularColor().g,
                    material_basic.getSpecularColor().b
            );
            shader->setUniform1f("brightness", sliderBrightness);
            shader->setUniform1f("lightRange", sliderPorteeLumiere);
            shader->end();
            break;

        case ShaderType::triple_light:
            shader_name = "3-light-Blinn-Phong";
            shader = &shader_3_light_blinn_phong;
            shader->begin();
            shader->setUniform3f(
                    "lightColor",
                    light_1.getAmbientColor().r,
                    light_1.getAmbientColor().g,
                    light_1.getAmbientColor().b
            );
            shader->setUniform3f(
                    "lightColor2",
                    light_2.getAmbientColor().r,
                    light_2.getAmbientColor().g,
                    light_2.getAmbientColor().b
            );

            shader->setUniform3f(
                    "lightColor3",
                    light_3.getAmbientColor().r,
                    light_3.getAmbientColor().g,
                    light_3.getAmbientColor().b
            );
            shader->setUniform3f(
                    "lightAmbient",
                    ambient_light.getAmbientColor().r,
                    ambient_light.getAmbientColor().g,
                    ambient_light.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorAmbient",
                    material_basic.getAmbientColor().r,
                    material_basic.getAmbientColor().g,
                    material_basic.getAmbientColor().b
            );
            shader->setUniform3f(
                    "colorDiffuse",
                    material_basic.getDiffuseColor().r,
                    material_basic.getDiffuseColor().g,
                    material_basic.getDiffuseColor().b
            );
            shader->setUniform3f(
                    "colorSpecular",
                    material_basic.getSpecularColor().r,
                    material_basic.getSpecularColor().g,
                    material_basic.getSpecularColor().b
            );
            shader->setUniform1f("brightness", sliderBrightness);
            shader->setUniform1f("lightRange", sliderPorteeLumiere);
            shader->end();
            break;

        default:
            break;
    }
    if (brumeActiver) {
        shader->begin();
        shader->setUniform1f("fogOpacity", sliderBrume);
        shader->end();
        shader_lights.begin();
        shader_lights.setUniform1f("fogOpacity", sliderBrume);
        shader_lights.end();
    }

}

void Renderer::create_preview() {
    float x_clamp = min(max(0.0f, mouse_current_x), (float) ofGetWidth());
    float y_clamp = min(max(0.0f, mouse_current_y), (float) ofGetHeight());
    switch (draw_primitive) {
        case DrawPrimitive::line: {
            Line line = Line(currentColor, mouse_press_x, mouse_press_y,
                             x_clamp, y_clamp, current_thickness);
            preview_primitive = line.clone();
            break;
        }
        case DrawPrimitive::rectangle: {
            /**
            Rectangle rectangle = Rectangle(currentColor, mouse_press_x, mouse_press_y,
                                            mouse_current_x, mouse_current_y, current_thickness);
            preview_primitive = rectangle.clone();
             **/
            break;
        }
        case DrawPrimitive::circle: {
            Circle circle = Circle(currentColor, mouse_press_x, mouse_press_y,
                                   mouse_current_x, mouse_current_y, current_thickness, is_filled);
            preview_primitive = circle.clone();
            break;
        }
        case DrawPrimitive::triangle: {
            Triangle triangle = Triangle(currentColor, mouse_press_x, mouse_press_y,
                                                 mouse_current_x, mouse_current_y, current_thickness, is_filled);
            preview_primitive = triangle.clone();
            break;
        }
        case DrawPrimitive::triangleRect: {
            TriangleRect triangle = TriangleRect(currentColor, mouse_press_x, mouse_press_y,
                                                 mouse_current_x, mouse_current_y, current_thickness, is_filled);
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
    if (preview_primitive->getOrigin() != preview_primitive->getSecondPoint()) {
        model2D.addPrimitive(*preview_primitive);
        history.addChange(model2D.lastIndex(), Action::add, preview_primitive);
    }
    delete preview_primitive;
}

void Renderer::selectObject() {
    releaseSelection();
    if (model2D.findPrimitive(mouse_current_x, mouse_current_y)) {
        ofLog() << "< object found at (" << mouse_current_x << ", " << mouse_current_y << ")>";
        is_selected = true;
        generate_modified_primitive();
    } else {
        ofLog() << "< no object found at (" << mouse_current_x << ", " << mouse_current_y << ")>";
    }
}

void Renderer::generate_modified_primitive() {
    ofColor temp_color = model2D.getCurrentPrimitive()->getColor();
    pair<float, float> temp_origin = model2D.getCurrentPrimitive()->getOrigin();
    preview_primitive = (*model2D.getCurrentPrimitive()).clone();
    fillingMode = is_filled = model2D.getCurrentPrimitive()->getFill();
    setColor(temp_color.r, temp_color.g, temp_color.b, temp_color.a);
    temp_alpha = temp_color.a;
    sliderPosX = origin_slider_x = temp_origin.first;
    sliderPosY = origin_slider_y = temp_origin.second;
    sliderEpaisseurLigneContour = current_thickness = preview_primitive->getThickness();
    temp_color.a = 0;
    model2D.getCurrentPrimitive()->changeColor(temp_color);
}

void Renderer::releaseSelection() {
    if (is_selected) {
        is_selected = false;
        ofColor temp_color = model2D.getCurrentPrimitive()->getColor();
        temp_color.a = (unsigned char)temp_alpha;
        model2D.getCurrentPrimitive()->changeColor(temp_color);
        if (!(*preview_primitive == *(model2D.getCurrentPrimitive()))) {
            history.addChange(model2D.lastIndex(), Action::modify, model2D.getCurrentPrimitive());
            model2D.replaceCurrentPrimitive(preview_primitive);
            ofLog() << "<replace selected primitive>";
        }
        delete preview_primitive;
    }
}

void Renderer::releaseWithNoChange() {
    if (is_selected) {
        is_selected = false;
        ofColor temp_color = model2D.getCurrentPrimitive()->getColor();
        temp_color.a = (unsigned char)temp_alpha;
        model2D.getCurrentPrimitive()->changeColor(temp_color);
        delete preview_primitive;
    }
}

void Renderer::deleteSelection() {
    if (is_selected) {
        is_selected = false;
        ofColor temp_color = model2D.getCurrentPrimitive()->getColor();
        temp_color.a = (unsigned char)temp_alpha;
        model2D.getCurrentPrimitive()->changeColor(temp_color);
        history.addChange(model2D.getCurrentIndex(), Action::remove, model2D.getCurrentPrimitive());
        model2D.deleteCurrentPrimitive();
        delete preview_primitive;
    }
}

void Renderer::setColor(float r, float g, float b, float a) {
    if (rgbMode) {
        redOrHue = r;
        greenOrSaturation = g;
        blueOrBrightness = b;
    } else {
        redOrHue = ofColor(r, g, b).getHue();
        greenOrSaturation = ofColor(r, g, b).getSaturation();
        blueOrBrightness = ofColor(r, g, b).getBrightness();
    }
    alpha = temp_alpha = a;
}

void Renderer::undo() {
    history.undo(model2D.getPrimitives());
}

void Renderer::redo() {
    history.redo(model2D.getPrimitives());
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
    releaseSelection();
    draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::line;
    ofLog() << "< drawing line enabled>";
}

void Renderer::boutonCerclePressed() {
    releaseSelection();
    draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::circle;
    ofLog() << "< drawing circle enabled>";
}

void Renderer::boutonRectanglePressed() {
    releaseSelection();
    /**draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::rectangle;
    ofLog() << "< drawing rectangle enabled>";**/
}

void Renderer::boutonTrianglePressed() {
    releaseSelection();
    draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::triangle;
    ofLog() << "< drawing triangle enabled>";
}

void Renderer::boutonTriangleRectanglePressed() {
    releaseSelection();
    draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::triangleRect;
    ofLog() << "< drawing rectangular triangle enabled>";
}

void Renderer::boutonSelectionPressed() {
    releaseSelection();
    draw_tool = DrawTool::select;
    ofLog() << "< selection mode enabled>";
}

//Change l'interface de modele 3D pour l'interface de dessin 2D
void Renderer::boutonMode2DToggled(bool &mode2D) {
	if (mode2D) {
		is2D = true;
		guiDessin.setPosition(screenWidth - guiDessin.getWidth(), 0);
		guiModel3D.setPosition(-guiModel3D.getWidth(), 0);
		boutonMode3D.set(false);
	}
}

//Change l'interface de dessin pour l'interface de modele 3D
void Renderer::boutonMode3DToggled(bool &mode3D) {
	if (mode3D) {
		is2D = false;
		guiDessin.setPosition(-guiDessin.getWidth(), 0);
		guiModel3D.setPosition(screenWidth - guiModel3D.getWidth(), 0);
		boutonMode2D.set(false);
	}
}

void Renderer::boutonImporterImagePressed() {
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		load_image(path, currentImage, is_current_image_loaded);
		is_current_image_loaded ? labelSourceImage.set(result.getName()) : labelSourceImage.set("None");
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
    releaseSelection();
    undo();
}

void Renderer::boutonRedoPressed() {
    releaseSelection();
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
    sliderRotation3DX = modele_angle.x;
    sliderRotation3DY = modele_angle.y;
    sliderRotation3DZ = modele_angle.z;
    selected_3D_instance = Select_3D::primitive3D;
}

void Renderer::boutonOctaedrePressed() {
    isGenererModele3D = false;
    isGenererTetraedre = false;
    isGenererOctaedre = true;
    sliderRotation3DX = modele_angle.x;
    sliderRotation3DY = modele_angle.y;
    sliderRotation3DZ = modele_angle.z;
    selected_3D_instance = Select_3D::primitive3D;
}

//Si on appuie sur le bouton lapin, le modele 3D devient le lapin
void Renderer::boutonLapinPressed() {
	isGenererOctaedre = false;
	isGenererTetraedre = false;
	modele.loadModel("lapin.obj");
    modele.disableMaterials();
	isGenererLapin = true;
	isGenererDragon = false;
	isGenererModele3D = true;
    selected_3D_instance = Select_3D::modele;
    sliderRotation3DX = modele_angle.x;
    sliderRotation3DY = modele_angle.y;
    sliderRotation3DZ = modele_angle.z;
    ofLog() << "lapin model loaded";
    ofLog() << "< Shader selected: " << shader_name << " >";
}

//Si on appuie sur le bouton dragon, le modele 3D devient le dragon
void Renderer::boutonDragonPressed(){
	isGenererOctaedre = false;
	isGenererTetraedre = false;
	modele.loadModel("dragon.obj");
    modele.disableMaterials();
	isGenererDragon = true;
	isGenererLapin = false;
	isGenererModele3D = true;
    selected_3D_instance = Select_3D::modele;
    sliderRotation3DX = modele_angle.x;
    sliderRotation3DY = modele_angle.y;
    sliderRotation3DZ = modele_angle.z;
    ofLog() << "< Dragon model loaded >";
    ofLog() << "< Shader selected: " << shader_name << " >";
}

void Renderer::boutonLumierePressed() {
    if (selected_3D_instance != Select_3D::lumiere) {
        selected_3D_instance = Select_3D::lumiere;
        light_selected = Light_select::light1;
        setColor(light_1.getAmbientColor().r*255, light_1.getAmbientColor().g*255, light_1.getAmbientColor().b*255);
        sliderRotation3DX = light_1_angle.x;
        sliderRotation3DY = light_1_angle.y;
        sliderRotation3DZ = light_1_angle.z;
    }
    ofLog() << "< Lights selected >";
}

void Renderer::boutonAmbientPressed() {
    selected_3D_instance = Select_3D::material;
    material_aspect_selected = Material_aspect::ambient;
    setColor(material_basic.getAmbientColor().r*255,
             material_basic.getAmbientColor().g*255,
             material_basic.getAmbientColor().b*255);
}

void Renderer::boutonDiffusePressed() {
    selected_3D_instance = Select_3D::material;
    material_aspect_selected = Material_aspect::diffuse;
    setColor(material_basic.getDiffuseColor().r*255,
             material_basic.getDiffuseColor().g*255,
             material_basic.getDiffuseColor().b*255);
}

void Renderer::boutonSpeculairePressed() {
    selected_3D_instance = Select_3D::material;
    material_aspect_selected = Material_aspect::specular;
    setColor(material_basic.getSpecularColor().r*255,
             material_basic.getSpecularColor().g*255,
             material_basic.getSpecularColor().b*255);
}

void Renderer::boutonShaderPressed() {
    selected_3D_instance = Select_3D::shader;
    ofLog() << "< shader selection >";
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
	else if(!is2D){
		if (isGenererModele3D) {
			dessinerCurseurVise(x, y);
		}
		else if (isGenererTetraedre || isGenererOctaedre) {
			dessinerCurseurPoint(x, y);
		}
		else {
			dessinerCurseurEtoile(x, y);
		}
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
    // activer l'occlusion en profondeur
    ofEnableDepthTest();

    // activer l'éclairage dynamique
    ofEnableLighting();

    ofFill();
    ofSetLineWidth(1);
    ofSetColor(1);

    shader->begin();

    //On ajuste la proportion du modele selon les sliders de proportion
    modele.setScale(sliderProportion3DX / 2, sliderProportion3DY / 2, sliderProportion3DZ / 2);
    //On ajuste l'angle de rotation selon les sliders de rotation
    modele.setRotation(0, modele_angle.x, 1, 0, 0);
    modele.setRotation(1, modele_angle.y, 0, 1, 0);
    modele.setRotation(2, modele_angle.z + 180, 0, 0, 1);

    modele.setPosition(0, 0, 0);
    modele.draw(OF_MESH_FILL);

    shader->end();

    // désactiver l'éclairage dynamique
    ofDisableLighting();
    // désactiver l'occlusion en profondeur
    ofDisableDepthTest();
}

void Renderer::drawLightSources() {
    // activer l'occlusion en profondeur
    ofEnableDepthTest();

    // activer l'éclairage dynamique
    ofEnableLighting();

    shader_lights.begin();
    shader_lights.setUniform3f(
            "colorAmbient",
            light_1.getAmbientColor().r,
            light_1.getAmbientColor().g,
            light_1.getAmbientColor().b
    );
    shader_lights.setUniform3f(
            "colorDiffuse",
            light_1.getAmbientColor().r,
            light_1.getAmbientColor().g,
            light_1.getAmbientColor().b
    );
    shader_lights.setUniform3f("lightPosition", camera->getGlobalPosition());
    shader_lights.setUniform1f("lightRange", 50.0f);
    shader_lights.end();

    shader_lights.begin();
    ofDrawSphere(light_1.getGlobalPosition().rotate(light_1_angle.x, light_1_angle.y, light_1_angle.z), 10);
    shader_lights.end();

    if (number_of_light > 1) {

        shader_lights.begin();
        shader_lights.setUniform3f(
                "colorAmbient",
                light_2.getAmbientColor().r,
                light_2.getAmbientColor().g,
                light_2.getAmbientColor().b
        );
        shader_lights.setUniform3f(
                "colorDiffuse",
                light_2.getAmbientColor().r,
                light_2.getAmbientColor().g,
                light_2.getAmbientColor().b
        );
        shader_lights.end();

        shader_lights.begin();
        ofDrawSphere(light_2.getGlobalPosition().rotate(light_2_angle.x, light_2_angle.y, light_2_angle.z), 10);
        shader_lights.end();

        if (number_of_light == 3) {

            shader_lights.begin();
            shader_lights.setUniform3f(
                    "colorAmbient",
                    light_3.getAmbientColor().r,
                    light_3.getAmbientColor().g,
                    light_3.getAmbientColor().b
            );
            shader_lights.setUniform3f(
                    "colorDiffuse",
                    light_3.getAmbientColor().r,
                    light_3.getAmbientColor().g,
                    light_3.getAmbientColor().b
            );
            shader_lights.end();

            shader_lights.begin();
            ofDrawSphere(light_3.getGlobalPosition().rotate(light_3_angle.x, light_3_angle.y, light_3_angle.z), 10);
            shader_lights.end();
        }
    }
    // désactiver l'éclairage dynamique
    ofDisableLighting();
    // désactiver l'occlusion en profondeur
    ofDisableDepthTest();
}

//genere un tetraedre
void Renderer::genererTetraedre() {

	ofFill();
    ofSetColor(primitive_color);

	float taille = screenHeight/4;
	float origineX = 0;
	float origineY = 0;
	float origineZ = -offset_scene;
	

	//origine
	ofVec3f origineTetraedre = ofVec3f(origineX, origineY, origineZ);
	/****************************/
	/***generation des points****/
	/***x' = x cos f - y sin f***/
	/***y' = y cos f + x sin f***/
	/****************************/

	//sommet du haut
	ofVec3f sommet1 = ofVec3f(0, -(taille*0.75) / 2, 0);
    //sommet de derriere
    ofVec3f sommet2 = ofVec3f(0, (taille*0.75) / 2, -(taille / (2* (sqrt(0.75)))));
    //sommet avant gauche
    ofVec3f sommet3 = ofVec3f(-(taille/2), (taille*0.75)/2, (taille / 4* sqrt(0.75)));
    //sommet avant droit
    ofVec3f sommet4 = ofVec3f((taille / 2), (taille*0.75) / 2, (taille / 4 * sqrt(0.75)));

    sommet1.rotate(modele_angle.x, modele_angle.y, modele_angle.z);
    sommet2.rotate(modele_angle.x, modele_angle.y, modele_angle.z);
    sommet3.rotate(modele_angle.x, modele_angle.y, modele_angle.z);
    sommet4.rotate(modele_angle.x, modele_angle.y, modele_angle.z);

	//ajoute l'origine
	sommet1 += origineTetraedre;
	sommet2 += origineTetraedre;
	sommet3 += origineTetraedre;
	sommet4 += origineTetraedre;

    //shader->begin();
	//dessin des triangles avec les points
	ofDrawTriangle(sommet1, sommet2, sommet3);
	ofDrawTriangle(sommet1, sommet2, sommet4);
	ofDrawTriangle(sommet1, sommet3, sommet4);
	ofDrawTriangle(sommet2, sommet3, sommet4);

	//dessin des aretes
	ofSetColor(255, 255, 255, 127);
	ofDrawLine(sommet1, sommet2);
	ofDrawLine(sommet1, sommet3);
	ofDrawLine(sommet1, sommet4);
	ofDrawLine(sommet2, sommet3);
	ofDrawLine(sommet2, sommet4);
	ofDrawLine(sommet3, sommet4);
}

void Renderer::genererOctaedre() {
	ofFill();
	ofSetColor(primitive_color);
	float taille = screenHeight / 4;
	float origineX = 0;
	float origineY = 0;
	float origineZ = -offset_scene;

	//origine
	ofVec3f origineOctaedre = ofVec3f(origineX, origineY, origineZ);
	/****************************/
	/***generation des points****/
	/***x' = x cos f - y sin f***/
	/***y' = y cos f + x sin f***/
	/****************************/

	//sommet du haut
	ofVec3f sommet1 = ofVec3f(0, -(taille*0.75), 0);
    //sommet de derriere
    ofVec3f sommet2 = ofVec3f(0, 0, -(taille) / (2* sqrt(0.75)));
    //sommet avant gauche
    ofVec3f sommet3 = ofVec3f(-(taille / 2), 0, (taille) / (4* sqrt(0.75)));
    //sommet avant droit
    ofVec3f sommet4 = ofVec3f((taille / 2), 0, (taille) / (4 * sqrt(0.75)));
    //sommet du dessous
    ofVec3f sommet5 = ofVec3f(0, (taille*0.75), 0);

    sommet1.rotate(modele_angle.x, modele_angle.y, modele_angle.z);
    sommet2.rotate(modele_angle.x, modele_angle.y, modele_angle.z);
    sommet3.rotate(modele_angle.x, modele_angle.y, modele_angle.z);
    sommet4.rotate(modele_angle.x, modele_angle.y, modele_angle.z);
    sommet5.rotate(modele_angle.x, modele_angle.y, modele_angle.z);

	//ajoute l'origine
	sommet1 += origineOctaedre;
	sommet2 += origineOctaedre;
	sommet3 += origineOctaedre;
	sommet4 += origineOctaedre;
	sommet5 += origineOctaedre;

	//dessin des triangles avec les points
	ofDrawTriangle(sommet1, sommet2, sommet3);
	ofDrawTriangle(sommet1, sommet2, sommet4);
	ofDrawTriangle(sommet1, sommet3, sommet4);
	//ofDrawTriangle(sommet2, sommet3, sommet4);
	ofDrawTriangle(sommet5, sommet2, sommet3);
	ofDrawTriangle(sommet5, sommet2, sommet4);
	ofDrawTriangle(sommet5, sommet3, sommet4);

	//dessin des aretes
	ofSetColor(255, 255, 255, 127);
	ofDrawLine(sommet1, sommet2);
	ofDrawLine(sommet1, sommet3);
	ofDrawLine(sommet1, sommet4);
	ofDrawLine(sommet2, sommet3);
	ofDrawLine(sommet2, sommet4);
	ofDrawLine(sommet3, sommet4);
	ofDrawLine(sommet5, sommet2);
	ofDrawLine(sommet5, sommet3);
	ofDrawLine(sommet5, sommet4);
}

//Color picker
void Renderer::rgbModeSwitched(bool &rgbMode) {
    if (rgbMode)
	{
		colorPickerGUI.setName("RGB Color Picker");
		redOrHue.set("red", currentColor.r, 0, 255);
		greenOrSaturation.set("green", currentColor.g, 0, 255);
		blueOrBrightness.set("blue", currentColor.b, 0, 255);
	}
	else
	{
		colorPickerGUI.setName("HSB Color Picker");
		redOrHue.set("hue", currentColor.getHue(), 0, 360);
		greenOrSaturation.set("saturation", currentColor.getSaturation(), 0, 255);
		blueOrBrightness.set("brightness", currentColor.getBrightness(), 0, 255);
	}
}

//Generer boite autour des modeles 3D
void Renderer::genererBoite() {
    // activer l'occlusion en profondeur
    ofEnableDepthTest();

    // activer l'éclairage dynamique
    ofEnableLighting();

	ofSetColor(currentColor);

	if (isGenererLapin) {
		boite = ofBoxPrimitive(402, 402, 320);
		//On met la boite à la meme position que le modele pour obtenir un rotation symetrique au modele
		boite.setPosition(0, 0, 0);
		//On suit la meme rotation que le modele
        boite.rotate(-modele_angle.x, 1, 0, 0);
		boite.rotate(-modele_angle.y, 0, 1, 0);
		boite.rotate(modele_angle.z, 0, 0, 1);
        ofVec3f offset_boite = ofVec3f(
                44*sliderProportion3DX,
                -152*sliderProportion3DY,
                0);
        offset_boite.rotate(modele_angle.x, modele_angle.y, modele_angle.z);
        boite.move(-offset_boite.x, -offset_boite.y, offset_boite.z);
		boite.setScale(sliderProportion3DX, sliderProportion3DY, sliderProportion3DZ);
		boite.draw();
	}
	else if (isGenererDragon) {
		boite = ofBoxPrimitive(410, 300, 210);
		//On met la boite à la meme position que le modele pour obtenir un rotation symetrique au modele
		boite.setPosition(0, 0, 0);
		//On suit la meme rotation que le modele
        boite.rotate(-modele_angle.x, 1, 0, 0);
		boite.rotate(-modele_angle.y, 0, 1, 0);
		boite.rotate(modele_angle.z, 0, 0, 1);
        ofVec3f offset_boite = ofVec3f(0, -145*sliderProportion3DY, 0);
        offset_boite.rotate(modele_angle.x, modele_angle.y, modele_angle.z);
        boite.move(-offset_boite.x, -offset_boite.y, offset_boite.z);

		boite.setScale(sliderProportion3DX, sliderProportion3DY, sliderProportion3DZ);
		boite.draw();
	}

    // désactiver l'éclairage dynamique
    ofDisableLighting();
    // désactiver l'occlusion en profondeur
    ofDisableDepthTest();
}

//animation des modeles 3D

void Renderer::animerMaillage() {

	//On augmente la rotation
	sliderRotation3DY = sliderRotation3DY + 1.3;
	if (sliderRotation3DY >= 360) {
		sliderRotation3DY = 0;
	}

	if (sliderProportion3DX >= sliderProportion3DX.getMax() || 
		sliderProportion3DY >= sliderProportion3DY.getMax() || 
		sliderProportion3DZ >= sliderProportion3DZ.getMax()) {
		animationGrossit = false;
	}
	else if (sliderProportion3DX <= sliderProportion3DX.getMin() || 
		sliderProportion3DY <= sliderProportion3DY.getMin() || 
		sliderProportion3DZ <= sliderProportion3DZ.getMin()) {
		animationGrossit = true;
	}
	//On augmente ou on diminue la proportion
	if (animationGrossit) {
		sliderProportion3DX = sliderProportion3DX + 0.001;
		sliderProportion3DY = sliderProportion3DY + 0.001;
		sliderProportion3DZ = sliderProportion3DZ + 0.001;
	}
	else {
		sliderProportion3DX = sliderProportion3DX - 0.001;
		sliderProportion3DY = sliderProportion3DY - 0.001;
		sliderProportion3DZ = sliderProportion3DZ - 0.001;
	}
}

//Composition d'image
void Renderer::load_image(const std::string path, ofImage &image, bool &imageLoadSuccess) {
	try {
		image.load(path);
		imageLoadSuccess = true;
		ofLog() << "< the file has been loaded>";
	}
	catch (runtime_error& e) {
		imageLoadSuccess = false;
		ofLog() << "< file not found>";
	}
}

void Renderer::boutonImporterImageTexture1() {
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		load_image(path, texture1, is_texture1_loaded);
		is_texture1_loaded ? textureName1.set(result.getName()) : textureName1.set("None");
	}
}

void Renderer::boutonImporterImageTexture2() {
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		load_image(path, texture2, is_texture2_loaded);
		if (is_texture2_loaded) {
			textureName2.set(result.getName());
		}
		else {
			textureName2.set("None");
		}
	}
}

//Traitement d'image par convolution
void Renderer::aiguiserToggled(bool & aiguiser) {
	if (aiguiser) {
		detectionBordure.set(false);
		bosseler.set(false);
		flou.set(false);
		kernel_type = ConvolutionKernel::sharpen;
		kernel_name = "aiguiser";
		filteredImage.allocate(currentImage.getWidth(), currentImage.getHeight(), OF_IMAGE_COLOR);
		filter();
	}
}

void Renderer::detectionBordureToggled(bool & detectionBordure) {
	if (detectionBordure) {
		aiguiser.set(false);
		bosseler.set(false);
		flou.set(false);
		kernel_type = ConvolutionKernel::edge_detect;
		kernel_name = "détection de bordure";
		filteredImage.allocate(currentImage.getWidth(), currentImage.getHeight(), OF_IMAGE_COLOR);
		filter();
	}
}

void Renderer::bosselerToggled(bool & bosseler) {
	if (bosseler) {
		aiguiser.set(false);
		detectionBordure.set(false);
		flou.set(false);
		kernel_type = ConvolutionKernel::emboss;
		kernel_name = "bosseler";
		filteredImage.allocate(currentImage.getWidth(), currentImage.getHeight(), OF_IMAGE_COLOR);
		filter();
	}
}

void Renderer::flouToggled(bool & flou) {
	if (flou) {
		aiguiser.set(false);
		detectionBordure.set(false);
		bosseler.set(false);
		kernel_type = ConvolutionKernel::blur;
		kernel_name = "flou";
		filteredImage.allocate(currentImage.getWidth(), currentImage.getHeight(), OF_IMAGE_COLOR);
		filter();
	}
}

// fonction de filtrage par convolution
void Renderer::filter()
{
	// résolution du kernel de convolution
	const int kernel_size = 3;

	// décalage à partir du centre du kernel
	const int kernel_offset = kernel_size / 2;

	// nombre de composantes de couleur (RGB)
	const int color_component_count = 3;

	// indices de l'image
	int x, y;

	// indices du kernel
	int i, j;

	// index des composantes de couleur
	int c;

	// index du pixel de l'image source utilisé pour le filtrage
	int pixel_index_img_src;

	// index du pixel de l'image de destination en cours de filtrage
	int pixel_index_img_dst;

	// index du pixel de l'image de destination en cours de filtrage
	int kernel_index;

	// valeur à un des indices du kernel de convolution
	float kernel_value;

	// extraire les pixels de l'image source
	ofPixels pixel_array_src = currentImage.getPixels();

	// extraire les pixels de l'image de destination
	ofPixels pixel_array_dst = filteredImage.getPixels();

	// couleur du pixel lu dans l'image source
	ofColor pixel_color_src;

	// couleur du pixel à écrire dans l'image de destination
	ofColor pixel_color_dst;

	// somme du kernel appliquée à chaque composante de couleur d'un pixel
	float sum[color_component_count];

	// itération sur les rangées des pixels de l'image source
	for (y = 0; y < currentImage.getHeight(); ++y)
	{
		// itération sur les colonnes des pixels de l'image source
		for (x = 0; x < currentImage.getWidth(); ++x)
		{
			// initialiser le tableau où les valeurs de filtrage sont accumulées
			for (c = 0; c < color_component_count; ++c)
				sum[c] = 0;

			// déterminer l'index du pixel de l'image de destination
			pixel_index_img_dst = (int)(currentImage.getWidth() * y + x) * color_component_count;

			// itération sur les colonnes du kernel de convolution
			for (j = -kernel_offset; j <= kernel_offset; ++j)
			{
				// itération sur les rangées du kernel de convolution
				for (i = -kernel_offset; i <= kernel_offset; ++i)
				{
					// déterminer l'index du pixel de l'image source à lire
					pixel_index_img_src = (int)(currentImage.getWidth() * (y - j) + (x - i)) * color_component_count;
					if (pixel_index_img_src < 0 || pixel_index_img_src >= currentImage.getWidth() * currentImage.getHeight() * color_component_count)
						pixel_color_src = 0;
					else
						// lire la couleur du pixel de l'image source
						pixel_color_src = pixel_array_src.getColor(pixel_index_img_src);

					// déterminer l'indice du facteur à lire dans le kernel de convolution
					kernel_index = kernel_size * (j + kernel_offset) + (i + kernel_offset);

					// extraction de la valeur à cet index du kernel
					switch (kernel_type)
					{
					case ConvolutionKernel::identity:
						kernel_value = convolution_kernel_identity.at(kernel_index);
						break;

					case ConvolutionKernel::emboss:
						kernel_value = convolution_kernel_emboss.at(kernel_index);
						break;

					case ConvolutionKernel::sharpen:
						kernel_value = convolution_kernel_sharpen.at(kernel_index);
						break;

					case ConvolutionKernel::edge_detect:
						kernel_value = convolution_kernel_edge_detect.at(kernel_index);
						break;

					case ConvolutionKernel::blur:
						kernel_value = convolution_kernel_blur.at(kernel_index);
						break;

					default:
						kernel_value = convolution_kernel_identity.at(kernel_index);
						break;
					}

					// itération sur les composantes de couleur
					for (c = 0; c < color_component_count; ++c)
					{
						// accumuler les valeurs de filtrage en fonction du kernel de convolution
						sum[c] = sum[c] + kernel_value * pixel_color_src[c];
					}
				}
			}

			// déterminer la couleur du pixel à partir des valeurs de filtrage accumulées pour chaque composante
			for (c = 0; c < color_component_count; ++c)
			{
				// conversion vers entier et validation des bornes de l'espace de couleur
				pixel_color_dst[c] = (unsigned char)ofClamp(sum[c], 0, 255);
			}

			// écrire la couleur à l'index du pixel en cours de filtrage
			pixel_array_dst.setColor(pixel_index_img_dst, pixel_color_dst);
		}
	}

	// écrire les pixels dans l'image de destination
	filteredImage.setFromPixels(pixel_array_dst);
}

//Texture procédural
void Renderer::binaryTreeToggled(bool & binaryTree) {
	if (binaryTree) {
		ternaryTree.set(false);
	}
}

void Renderer::ternaryTreeToggled(bool & ternaryTree) {
	if (ternaryTree) {
		binaryTree.set(false);
	}
}

void Renderer::drawTernaryTree(int length)
{
	ofDrawLine(0, 0, 0, -length);

	ofPushMatrix();
	ofRotate(angle);
	ofDrawLine(0, 0, 0, -length);
	ofPopMatrix();

	ofPushMatrix();
	ofRotate(-angle);
	ofDrawLine(0, 0, 0, -length);
	ofPopMatrix();

	float tempLength = length;
	length *= 0.5;

	ofPushMatrix();
	ofTranslate(0, -tempLength);
	if (length > 2) {
		drawTernaryTree(length);
	}
	ofPopMatrix();

	ofPushMatrix();
	ofRotate(angle);
	ofTranslate(0, -tempLength);
	if (length > 2) {
		drawTernaryTree(length);
	}
	ofPopMatrix();

	ofPushMatrix();
	ofRotate(-angle);
	ofTranslate(0, -tempLength);
	if (length > 2) {
		drawTernaryTree(length);
	}
	ofPopMatrix();	
}

void Renderer::drawBinaryTree(int length) {
	ofDrawLine(0, 0, 0, -length);
	ofTranslate(0, -length);

	length *= 0.66;

	if (length > 2) {
		ofPushMatrix();
		ofRotate(angle);
		drawBinaryTree(length);
		ofPopMatrix();

		ofPushMatrix();
		ofRotate(-angle);
		drawBinaryTree(length);
		ofPopMatrix();
	}
}

// Ray tracing

// fonction pour borner une valeur numérique entre 0 et 1
double Renderer::clamp(double x)
{
	return x < 0 ? 0 : x > 1 ? 1 : x;
}

// traitement de la couleur d'un pixel
int Renderer::format_color_component(double value)
{
	// appliquer la correction gamma
	value = pow(clamp(value), gamma_correction);

	// convertir la valeur dans l'espace de couleur
	value = value * 255 + 0.5;

	// conversion numérique de réel vers entier
	return static_cast<int>(value);
}

// fonction qui valide s'il y a intersection entre un rayon et les géométries de la scène
// retourne l'intersection la plus près de la caméra (distance et index de l'élément)
bool Renderer::raycast(const RayCastRay& ray, double& distance, int& id)
{
	// variable temporaire pour la distance d'une intersection entre un rayon et une sphère
	double d;

	// initialiser la distance à une valeur suffisamment éloignée pour qu'on la considère comme l'infini
	double infinity = distance = 1e20;

	// nombre d'éléments dans la scène
	int n = static_cast<int>(scene.size());

	// parcourir tous les éléments de la scène
	for (int index = 0; index < n; ++index)
	{
		// test d'intersection entre le rayon et la géométrie à cet index
		d = scene[index].intersect(ray);

		// valider s'il y a eu intersection et si la distance est inférieur aux autres intesections
		if (d && d < distance)
		{
			// nouvelle valeur courante de la distance et l'index de l'intersection la plus rapprochée de la caméra
			distance = d;
			id = index;
		}
	}

	// il y a eu intersection si la distance est plus petite que l'infini
	if (distance < infinity)
		return true;
	else
		return false;
}

// fonction récursive qui calcule la radiance
Vector Renderer::compute_radiance(const RayCastRay& ray, int depth)
{
	// valeur de la radiance
	Vector radiance;

	// distance de l'intersection (TODO par rapport à quoi?!)
	double distance;

	// identifiant de la géométrie en intersection
	int id = 0;

	// valider s'il n'y a pas intersection
	if (!raycast(ray, distance, id))
		return Vector(); // couleur par défault (noir)

						 // référence sur une géométrie en intersection avec un rayon
	const RayCastSphere& obj = scene[id];

	// calculer la coordonnées du point d'intersection
	Vector x = ray.origin + ray.direction * distance;

	// calculer la normale au point d'intersection
	Vector n = (x - obj.position).normalize();

	// ajustement de la direction de la normale
	Vector na = n.dot(ray.direction) < 0 ? n : n * -1;

	// isoler la composante de couleur la plus puissante
	Vector f = obj.color;
	double threshold = f.x > f.y && f.x > f.z ? f.x : f.y > f.z ? f.y : f.z;

	// valider si la limite du nombre de récursion est atteinte
	if (++depth > max_depth)
	{
		// test de probabilité
		if (random01(rng) < threshold)
			f = f * (1 / threshold);
		else
			return obj.emission;
	}

	if (obj.material == SurfaceType::diffuse)
	{
		// matériau avec réflexion diffuse

		double r1 = 2 * M_PI * random01(rng);
		double r2 = random01(rng);
		double r2s = sqrt(r2);

		Vector w = na;
		Vector u = ((fabs(w.x) > 0.1 ? Vector(0, 1) : Vector(1)).cross(w)).normalize();
		Vector v = w.cross(u);
		Vector d = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).normalize();

		radiance = obj.emission + f.multiply(compute_radiance(RayCastRay(x, d), depth));

		return radiance;
	}
	else if (obj.material == SurfaceType::specular)
	{
		// matériau avec réflexion spéculaire

		radiance = obj.emission + f.multiply(compute_radiance(RayCastRay(x, ray.direction - n * 2.0 * n.dot(ray.direction)), depth));

		return radiance;
	}
	else if (obj.material == SurfaceType::refraction)
	{
		// matériau avec réflexion réfraction

		RayCastRay reflection_ray(x, ray.direction - n * 2.0 * n.dot(ray.direction));

		bool into = n.dot(na) > 0;

		double nc = 1.0;
		double nt = 1.5;
		double nnt = into ? nc / nt : nt / nc;
		double ddn = ray.direction.dot(na);
		double cos2t;

		if ((cos2t = 1.0 - nnt * nnt * (1.0 - ddn * ddn)) < 0.0)
		{
			radiance = obj.emission + f.multiply(compute_radiance(reflection_ray, depth));

			return radiance;
		}

		Vector tdir = (ray.direction * nnt - n * ((into ? 1.0 : -1.0) * (ddn * nnt + sqrt(cos2t)))).normalize();

		double a = nt - nc;
		double b = nt + nc;
		double r0 = a * a / (b * b);
		double c = 1.0 - (into ? -ddn : tdir.dot(n));
		double re = r0 + (1.0 - r0) * c*c*c*c*c;
		double tr = 1 - re;
		double p = 0.25 + 0.5 * re;
		double rp = re / p;
		double tp = tr / (1.0 - p);

		radiance = obj.emission + f.multiply(depth > 2 ? (random01(rng) < p ?
			compute_radiance(reflection_ray, depth) * rp : compute_radiance(RayCastRay(x, tdir), depth) * tp) :
			compute_radiance(reflection_ray, depth) * re + compute_radiance(RayCastRay(x, tdir), depth) * tr);

		return radiance;
	}
	else
	{
		return radiance;
	}
}

void Renderer::setupRaycastScene() {

	ofLog() << "scene setup";

	constexpr double anchor = 1e5;
	constexpr double wall_radius = anchor;

	constexpr double box_size_x = 100.0;
	constexpr double box_size_y = 81.6;
	constexpr double box_size_z = 81.6;

	constexpr double box_x_min = 0.0;
	constexpr double box_x_max = box_size_x;
	constexpr double box_y_min = 0.0;
	constexpr double box_y_max = box_size_y;
	constexpr double box_z_min = 0.0;
	constexpr double box_z_max = box_size_z;

	constexpr double box_center_x = (box_x_max - box_x_min) / 2.0;
	constexpr double box_center_y = (box_y_max - box_y_min) / 2.0;
	constexpr double box_center_z = (box_z_max - box_z_min) / 2.0;

	// vider la scène de son contenu
	scene.clear();

	// génération du contenu de la scène
	scene.insert(scene.begin(), {

		// approximation d'une boîte de Cornell avec des sphères sur-dimensionnées qui simulent des surfaces planes
		RayCastSphere(wall_radius, Vector(box_center_x, anchor, box_size_z),   Vector(), Vector(0.75, 0.75, 0.75), SurfaceType::diffuse),    // plancher
		RayCastSphere(wall_radius, Vector(box_center_x, -anchor + box_size_y, box_size_z),   Vector(), Vector(0.75, 0.75, 0.75), SurfaceType::diffuse),    // plafond
		RayCastSphere(wall_radius, Vector(anchor + 1, box_center_y, box_size_z),   Vector(), Vector(1, 0, 0), SurfaceType::diffuse),    // mur gauche
		RayCastSphere(wall_radius, Vector(box_center_x, box_center_y, anchor), Vector(), Vector(0, 1, 0), SurfaceType::diffuse),    // mur arrière
		RayCastSphere(wall_radius, Vector(-anchor + 99, box_center_y, box_size_z), Vector(), Vector(0, 0, 1), SurfaceType::diffuse),    // mur droit
		RayCastSphere(wall_radius, Vector(box_center_x, box_center_y, -anchor + 170), Vector(), Vector(0.0,  0.0,  0.0),  SurfaceType::diffuse),    // mur avant

		// ensemble des sphères situées à l'intérieur de la boîte de Cornell
		RayCastSphere(22.5, Vector(30, 30, 40), Vector(), Vector(1.0, 1.0, 1.0), SurfaceType::specular), // sphère mirroir
		RayCastSphere(17.5, Vector(75, 40, 75), Vector(), Vector(1.0, 1.0, 1.0), SurfaceType::refraction), // sphère de verre

		RayCastSphere(600,  Vector(box_center_x, 600.0 + box_size_z - 0.27, box_size_z), Vector(15, 15, 15), Vector(0.0, 0.0, 0.0), SurfaceType::diffuse) // sphère lumineuse
		});

	// allocation de la mémoire de l'image en fonction des paramètres du programme
	image.resize(image_width, image_height);

	ofLog() << "image resize to " << image.width << "x" << image.height << " (" << image.count << " pixels) " << image.size << " MB)";

	// calibration de la caméra
	ray_cast_camera.viewport_width = image.width;
	ray_cast_camera.viewport_height = image.height;
	ray_cast_camera.fov = camera_fov;
	ray_cast_camera.calibrate();
}


// fonction de rendu de la scène
void Renderer::render()
{
	ofLog() << "render start";

	unsigned short x = 0;

	int index, y, s, sx, sy = 0;

	float progression = 0.0f;

	double r1, r2 = 0.0;
	double dx, dy = 0.0;

	Vector radiance;

	Vector distance;

	// itération sur les rangées de pixels
	for (y = 0; y < image_height; ++y)
	{
		// calculer le pourcentage de progression
		progression = 100.0f * y / (image_height - 1.0f);

		// afficher le pourcentage de progression du rendu dans la console
		fprintf(stderr, "\rraytracing (%d rays per pixel) : %4.1f %%", ray_per_pixel, progression);

		// itération sur les colonnes de pixels
		for (x = 0; x < image_width; ++x)
		{
			// déterminer l'index du pixel
			index = (image_height - y - 1) * image_width + x;

			// itération sur les rangées du bloc de 2x2 échantillons
			for (sy = 0; sy < 2; ++sy)
			{
				// itération sur les colonnes du bloc de 2x2 échantillons
				for (sx = 0; sx < 2; ++sx)
				{
					// initialiser la radiance
					radiance = Vector();

					// itération des sur les rayons par pixel
					for (s = 0; s < ray_per_pixel; ++s)
					{
						// filtre de la tente
						r1 = 2.0 * random01(rng);
						dx = r1 < 1.0 ? sqrt(r1) - 1.0 : 1.0 - sqrt(2.0 - r1);

						r2 = 2.0 * random01(rng);
						dy = r2 < 1.0 ? sqrt(r2) - 1.0 : 1.0 - sqrt(2.0 - r2);

						// calculer la distance de ...
						distance = ray_cast_camera.axis_x * (((sx + 0.5 + dx) / 2.0 + x) / image_width - 0.5) +
							ray_cast_camera.axis_y * (((sy + 0.5 + dy) / 2.0 + y) / image_height - 0.5) + ray_cast_camera.axis_z;

						// appel récursif du calcul de la radiance
						radiance = radiance + compute_radiance(RayCastRay(ray_cast_camera.position + distance * 140, distance.normalize()), 0) * (1.0 / ray_per_pixel);
					}

					image.pixel[index] = image.pixel[index] + Vector(clamp(radiance.x), clamp(radiance.y), clamp(radiance.z)) * 0.25;
				}
			}
		}
	}

	ofLog() << "\nrender done";
}

// fonction qui permet de sauvegarder des pixels dans un fichier image (format .ppm)
void Renderer::save_image_file(int width, int height, int ray_per_pixel, const Vector* pixel)
{
	ofFileDialogResult result = ofSystemSaveDialog("default.jpg", "Save");
	if (result.bSuccess) {

		string path = result.getPath();
		is_menu_displayed = false;
		draw();

		// nom du fichier image de type .ppm (portable pixmap)
		std::stringstream ss;
		ss << path << width << "x" << height << "_" << ray_per_pixel << ".ppm";
		std::string filename = ss.str();

		// déclaration et ouverture du fichier en mode écriture
		std::ofstream file;
		file.open(filename, std::ios::out);

		// entête du ficher pour une image avec un espace de couleur RGB 24 bits (P3 pour pixmap)
		file << "P3\n";

		// largeur et hauteur de l'image sur la seconde ligne de l'entête
		file << width << ' ' << height << '\n';

		// valeur maximale de l'espace de couleur sur la troisième ligne de l'entête
		file << "255\n";

		// écriture des pixels dans le fichier image
		for (int index = 0; index < width * height; ++index)
		{
			// écrire la couleur du pixel dans le fichier image
			file << static_cast<std::uint32_t>(format_color_component(pixel[index].x)) << " ";
			file << static_cast<std::uint32_t>(format_color_component(pixel[index].y)) << " ";
			file << static_cast<std::uint32_t>(format_color_component(pixel[index].z)) << " ";
		}

		// fermeture du fichier
		file.close();

		lastRayCastResultPath = filename;

		is_menu_displayed = true;
	}	
}

void Renderer::boutonRenderRayCastImagePressed() {

	image_width = widthOfRenderedImage;
	image_height = heightOfRenderedImage;
	ray_per_pixel = raysPerPixel;

	setupRaycastScene();
	render();
	save_image_file(image.width, image.height, ray_per_pixel, image.pixel);
	viewLastRenderedImage = true;
}

void Renderer::viewLastRayCastImageToggled(bool &viewRayTraceResult) {
	if (viewRayTraceResult) {
		load_image(lastRayCastResultPath, lastRayCastResult, rayCastResultLoaded);
	}
	else {

	}
}

//Traitement d'image
void Renderer::compositionToggled(bool &composition) {
	if (composition) {
		convolutionFilter.set(false);
		proceduralTexture.set(false);
		raycastRenderer.set(false);
	}
}

void Renderer::convolutionToggled(bool &convolution) {
	if (convolution) {
		imageComposition.set(false);
		proceduralTexture.set(false);
		raycastRenderer.set(false);
	}
}

void Renderer::proceduralToggled(bool &procedural) {
	if (procedural) {
		imageComposition.set(false);
		convolutionFilter.set(false);
		raycastRenderer.set(false);
	}
}

void Renderer::raycastToggled(bool &raycast) {
	if (raycast) {
		imageComposition.set(false);
		convolutionFilter.set(false);
		proceduralTexture.set(false);
	}
}

void Renderer::fillingModeSwitched(bool &fillingMode) {
    is_filled = fillingMode;
}

void Renderer::resetCamera() {
	// initialisation des variables

	offset_scene = 200.0f;
	offset_camera = offset_scene * 3.5f * -1.0f;

	// position initiale de chaque caméra
	camera_front.setPosition(0, 0, -offset_camera);
	camera_back.setPosition(0, 0, offset_camera);
	camera_left.setPosition(-offset_camera, 0, 0);
	camera_right.setPosition(offset_camera, 0, 0);
	camera_top.setPosition(0, offset_camera, 0);
	camera_down.setPosition(0, -offset_camera, 0);

	// orientation de chaque caméra
	camera_front.lookAt(camera_target);
	camera_back.lookAt(camera_target);
	camera_left.lookAt(camera_target);
	camera_right.lookAt(camera_target);
	camera_top.lookAt(camera_target, ofVec3f(1, 0, 0));
	camera_down.lookAt(camera_target, ofVec3f(1, 0, 0));

	// caméra par défaut
	camera_active = Camera::front;
    toggleFrontCamera.set(true);

	ofLog() << "<reset>";
}

void Renderer::setup_camera() {
	switch (camera_active) {
        case Camera::front:
            camera = &camera_front;
            break;

        case Camera::back:
            camera = &camera_back;
            break;

        case Camera::left:
            camera = &camera_left;
            break;

        case Camera::right:
            camera = &camera_right;
            break;

        case Camera::top:
            camera = &camera_top;
            break;

        case Camera::down:
            camera = &camera_down;
            break;

        default:
            break;
    }

	camera_position = camera->getPosition();

	camera_orientation = camera->getOrientationQuat();

	if (toggleProjectionPerspective) {
		camera->disableOrtho();
	} else {
		camera->enableOrtho();
	}

	camera->setPosition(camera_position);
	camera->setOrientation(camera_orientation);
}

void Renderer::toggleFrontCameraPressed(bool &front) {
	if (front) {
		toggleBackCamera.set(false);
		toggleLeftCamera.set(false);
		toggleRightCamera.set(false);
		toggleTopCamera.set(false);
		toggleBottomCamera.set(false);

		camera_active = Camera::front;
		setup_camera();
	}
}

void Renderer::toggleBackCameraPressed(bool &back) {
	if (back) {
		toggleFrontCamera.set(false);
		toggleLeftCamera.set(false);
		toggleRightCamera.set(false);
		toggleTopCamera.set(false);
		toggleBottomCamera.set(false);

		camera_active = Camera::back;
		setup_camera();
	}
}

void Renderer::toggleLeftCameraPressed(bool &left) {
	if (left) {
		toggleBackCamera.set(false);
		toggleFrontCamera.set(false);
		toggleRightCamera.set(false);
		toggleTopCamera.set(false);
		toggleBottomCamera.set(false);

		camera_active = Camera::right;
		setup_camera();
	}
}

void Renderer::toggleRightCameraPressed(bool &right) {
	if (right) {
		toggleBackCamera.set(false);
		toggleLeftCamera.set(false);
		toggleFrontCamera.set(false);
		toggleTopCamera.set(false);
		toggleBottomCamera.set(false);

		camera_active = Camera::left;
		setup_camera();
	}
}

void Renderer::toggleTopCameraPressed(bool &top) {
	if (top) {
		toggleBackCamera.set(false);
		toggleLeftCamera.set(false);
		toggleRightCamera.set(false);
		toggleFrontCamera.set(false);
		toggleBottomCamera.set(false);

		camera_active = Camera::top;
		setup_camera();
	}
}

void Renderer::toggleBottomCameraPressed(bool &bottom) {
	if (bottom) {
		toggleBackCamera.set(false);
		toggleLeftCamera.set(false);
		toggleRightCamera.set(false);
		toggleTopCamera.set(false);
		toggleFrontCamera.set(false);

		camera_active = Camera::down;
		setup_camera();
	}
}

void Renderer::toggleProjectionPerspectivePressed(bool &perspective) {
	if (perspective) {
		toggleProjectionOrthogonale.set(false);
		camera->disableOrtho();
	}
}

void Renderer::toggleProjectionOrthogonalePressed(bool &orthogonale) {
	if (orthogonale) {
		toggleProjectionPerspective.set(false);
		camera->enableOrtho();
	}
}

void Renderer::toggleCourbeDeBezierPressed(bool &bezier) {
	if (bezier) {
		toggleCourbeDeHermite.set(false);
		toggleCourbeSplineDeBezier.set(false);
		isCourbeParametriqueActive = true;
		curveId = CurveType::bezier;
		resetCourbeParametrique();
	} else {
		isCourbeParametriqueActive = false;
	}
}

void Renderer::toggleCourbeDeHermitePressed(bool &hermite) {
	if (hermite) {
		toggleCourbeDeBezier.set(false);
		toggleCourbeSplineDeBezier.set(false);
		isCourbeParametriqueActive = true;
		curveId = CurveType::hermite;
		resetCourbeParametrique();
	} else {
		isCourbeParametriqueActive = false;
	}
}

void Renderer::toggleCourbeSplineDeBezierPressed(bool &splineDeBezier) {
	if (splineDeBezier) {
		toggleCourbeDeBezier.set(false);
		toggleCourbeDeHermite.set(false);
		isCourbeParametriqueActive = true;
		curveId = CurveType::splineDeBezier;
		resetCourbeParametrique();
	} else {
		isCourbeParametriqueActive = false;
	}
}

void Renderer::resetCourbeParametrique() {
	float w_1_4 = screenWidth / 4.0f;
	float w_1_2 = screenWidth / 2.0f;
	float w_3_4 = screenWidth * 3.0f / 4.0f;
	float h_2_5 = screenHeight * 2.0f / 5.0f;
	float h_3_5 = screenHeight * 3.0f / 5.0f;

	switch (curveId) {
        case CurveType::bezier:
            pointDeControle1 = { w_1_4, h_3_5, 0 };
            pointDeControle2 = { w_1_4, h_2_5, 0 };
            pointDeControle3 = { w_3_4, h_3_5, 0 };
            pointDeControle4 = { w_3_4, h_2_5, 0 };
            break;

        case CurveType::hermite:
            pointDeControle1 = { w_1_4, h_3_5, 0 };
            pointDeControle2 = { w_1_4, h_2_5, 0 };
            pointDeControle4 = { w_3_4, h_3_5, 0 };
            pointDeControle3 = { w_3_4, h_2_5, 0 };
            break;

        case CurveType::splineDeBezier:
            pointDeControle1 = { w_1_4, h_3_5, 0 };
            pointDeControle2 = { w_1_4, h_2_5, 0 };
            pointDeControle3 = { w_1_2, h_3_5, 0 };
            pointDeControle4 = { w_1_2, h_2_5, 0 };
            pointDeControle5 = { w_3_4, h_3_5, 0 };
            pointDeControle6 = { w_3_4, h_2_5, 0 };
            break;

        default:
            break;
	}
	pointDeControleSelectionne = &pointDeControle2;
}

void Renderer::toggleSurfaceDeCoonsPressed(bool &coons) {
	if (coons) {
		isSurfaceParametriqueActive = true;
		resetSurfaceParametrique();
	} else {
		isSurfaceParametriqueActive = false;
	}
    selected_3D_instance = Select_3D::surface;
}

void Renderer::resetSurfaceParametrique() {
	float w_1_4 = (screenWidth / 4.0f) - screenWidth / 2;
	float w_3_4 = (screenWidth * 3.0f / 4.0f) - screenWidth / 2;
	float h_2_5 = (screenHeight * 2.0f / 5.0f) - screenHeight / 2;
	float h_3_5 = (screenHeight * 3.0f / 5.0f) - screenHeight / 2;
	float profondeur = 200;

	pointDeControleSurface1 = { w_1_4, h_3_5, -profondeur };
	pointDeControleSurface2 = { w_1_4, h_2_5, -profondeur };
	pointDeControleSurface3 = { w_3_4, h_3_5, -profondeur };
	pointDeControleSurface4 = { w_3_4, h_2_5, -profondeur };
	pointDeControleSurface5 = { w_1_4, h_3_5, profondeur };
	pointDeControleSurface6 = { w_1_4, h_2_5, profondeur };
	pointDeControleSurface7 = { w_3_4, h_3_5, profondeur };
	pointDeControleSurface8 = { w_3_4, h_2_5, profondeur };

	pointDeControleSelectionneSurface = &pointDeControleSurface2;
	lignesDeSurfaceV.clear();
	for (int i = 0; i < resolutionSurface; i++) {
		lignesDeSurfaceV.push_back(ofPolyline());
		for (int j = 0; j < resolutionSurface; ++j) {
			lignesDeSurfaceV.at(i).addVertex(ofPoint());
		}
	}
	lignesDeSurfaceU.clear();
	for (int i = 0; i < resolutionSurface; i++) {
		lignesDeSurfaceU.push_back(ofPolyline());
		for (int j = 0; j < resolutionSurface; ++j) {
			lignesDeSurfaceU.at(i).addVertex(ofPoint());
		}
	}
}

void Renderer::toogleTriangulationPressed(bool &triangulation) {
	if (triangulation) {
		isTriangulation = true;
	} else {
		isTriangulation = false;
	}
}

void Renderer::toggleActiverBrumePressed(bool &brume) {
	if (brume) {
		brumeActiver = true;
        shader->begin();
        shader->setUniform1f("fogOpacity", sliderBrume);
        shader->end();
	} else {
		brumeActiver = false;
        shader->begin();
        shader->setUniform1f("fogOpacity", 0.0f);
        shader->end();
        shader_lights.begin();
        shader_lights.setUniform1f("fogOpacity", 0.0f);
        shader_lights.end();
	}
}

Renderer::~Renderer() {
    releaseSelection();
}
