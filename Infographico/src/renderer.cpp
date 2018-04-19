#include "renderer.h"

void Renderer::setup() {
    ofSetFrameRate(60);

    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();

    is2D = true;
    is_filled = false;

    //Curseur
    mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0.0f;
    is_mouse_button_pressed = false;
    is_mouse_button_legit = false;

    is_ctrl_pressed = false;
    currentColor = ofColor(255, 0, 0);
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

	imageComposition.addListener(this, &Renderer::compositionToggled);
	convolutionFilter.addListener(this, &Renderer::convolutionToggled);
	proceduralTexture.addListener(this, &Renderer::proceduralToggled);
	

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
	guiModel3D.add(sliderRotation3DY.setup("Rotation Y", 0, 0, 360));
	guiModel3D.add(sliderRotation3DZ.setup("Rotation Z", 0, 0, 360));

	guiModel3D.add(labelProportion3D.setup("Proportion modele 3D", ""));

	guiModel3D.add(sliderProportion3DX.setup("Proportion en X", 1, 0.5, 2));
	guiModel3D.add(sliderProportion3DY.setup("Proportion en Y", 1, 0.5, 2));
	guiModel3D.add(sliderProportion3DZ.setup("Proportion en Z", 1, 0.5, 2));

	guiModel3D.add(labelEffet.setup("Effets", ""));
	guiModel3D.add(animer.setup("Animer", false));
	guiModel3D.add(dessierBoite.setup("Dessiner boite", false));

	//primitive geo
	guiModel3D.add(labelGenerationPrimitiveGeometrique.setup("Primitive geometrique 3D", ""));
	guiModel3D.add(boutonTetraedre.setup("Tetraedre"));
	guiModel3D.add(boutonOctaedre.setup("Octaedre"));

	guiModel3D.add(labelPrimitiveGeo.setup("Rotation Primitive Geo", ""));
	guiModel3D.add(buttonRotation3DX.setup("Activer rotation en X"));
	guiModel3D.add(buttonRotation3DY.setup("Activer rotation en Y"));
	guiModel3D.add(buttonRotation3DZ.setup("Activer rotation en Z"));
	guiModel3D.add(sliderRotationPrimitiveGeo.setup("Rotation sur X", 0, 0, 360));
	isRotation3DXPrimitiveGeo = true;
	isRotation3DYPrimitiveGeo = false;
	isRotation3DZPrimitiveGeo = false;
	

	guiModel3D.setPosition(-guiModel3D.getWidth(), 0);

    //color picker
	rgbMode.addListener(this, &Renderer::rgbModeSwitched);
	colorPickerGUI.setup();
	colorPickerGUI.add(rgbMode.setup("RGB mode", true));
	colorPickerGUI.add(redOrHue);
	colorPickerGUI.add(greenOrSaturation);
	colorPickerGUI.add(blueOrBrightness);
	colorPickerGUI.add(alpha.set("alpha", 255, 0, 255));
	

	buttonRotation3DX.addListener(this, &Renderer::buttonRotation3DXPressed);
	buttonRotation3DY.addListener(this, &Renderer::buttonRotation3DYPressed);
	buttonRotation3DZ.addListener(this, &Renderer::buttonRotation3DZPressed);

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

	toggleFrontCamera.addListener(this, &Renderer::toggleFrontCameraPressed);
	toggleBackCamera.addListener(this, &Renderer::toggleBackCameraPressed);
	toggleLeftCamera.addListener(this, &Renderer::toggleLeftCameraPressed);
	toggleRightCamera.addListener(this, &Renderer::toggleRightCameraPressed);
	toggleTopCamera.addListener(this, &Renderer::toggleTopCameraPressed);
	toggleBottomCamera.addListener(this, &Renderer::toggleBottomCameraPressed);

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
    }
	else {
		currentColor = ofColor::fromHsb(redOrHue, greenOrSaturation, blueOrBrightness, alpha);
	}
    
    model2D.draw();
    if (is_menu_displayed) {

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
			filteredImage.allocate(currentImage.getWidth(), currentImage.getHeight(), OF_IMAGE_COLOR);
			filter();
			filteredImage.draw(guiMenu.getWidth(), 0, currentImage.getWidth(), currentImage.getHeight());
		}
		else if (ternaryTree || binaryTree) {
			ofSetBackgroundColor(255, 255, 255, 255);
			ofSetColor(0, 0, 0, 255);
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
		}
		else if(toggleAfficherImage) {
			currentImage.draw(guiMenu.getWidth(), 0, currentImage.getWidth(), currentImage.getHeight());
		}

        //GUI et affichage
        guiMenu.setPosition(0, 0);
        guiMenu.draw();
		
        if (!is2D) {
            guiModel3D.setPosition(screenWidth - guiDessin.getWidth(), 0);
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

			ofEnableDepthTest();
			if (brumeActiver) {
				activerBrume();
			}
			ofDisableDepthTest();

			if (isSurfaceParametriqueActive) {

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

				ofSetColor(46, 48, 51);
				ofSetLineWidth(2.0f);
				for (int i = 0; i < resolutionSurface; i++) {
					lignesDeSurfaceV.at(i).draw();
				}
				for (int i = 0; i < resolutionSurface; i++) {
					lignesDeSurfaceU.at(i).draw();
				}

			}
			if (isGenererModele3D) {
				genererModele3D();
				if (dessierBoite) {
					genererBoite();
				}
			}
			else if (isGenererTetraedre) {
				genererTetraedre();
			}
			else if (isGenererOctaedre) {
				genererOctaedre();
			}
			camera->end();
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
        ofSetColor(currentColor);

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
}

void Renderer::update() {
	if (isGenererModele3D) {
		if (animer) {
			animerMaillage();
		}
	}
	if (!is2D) {
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
		}
	}
	else {
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
	
	
     /**case DrawPrimitive::rectangle: {
            Rectangle rectangle = Rectangle(currentColor, mouse_press_x, mouse_press_y,
                                            mouse_current_x, mouse_current_y, current_thickness);
            preview_primitive = rectangle.clone();
            break;
        }**/
        case DrawPrimitive::circle: {
            Circle circle = Circle(currentColor, mouse_press_x, mouse_press_y,
                                   mouse_current_x, mouse_current_y, current_thickness, is_filled);
            preview_primitive = circle.clone();;
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
        ofLog() << "< object not found at (" << mouse_current_x << ", " << mouse_current_y << ")>";
    }
}

void Renderer::generate_modified_primitive() {
    ofColor temp_color = model2D.getCurrentPrimitive()->getColor();
    pair<float, float> temp_origin = model2D.getCurrentPrimitive()->getOrigin();
    preview_primitive = (*model2D.getCurrentPrimitive()).clone();
    fillingMode = is_filled = model2D.getCurrentPrimitive()->getFill();
    redOrHue = temp_color.r;
    greenOrSaturation = temp_color.g;
    blueOrBrightness = temp_color.b;
    alpha = temp_alpha = temp_color.a;
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
    draw_tool = DrawTool::primitive;
    draw_primitive = DrawPrimitive::rectangle;
    ofLog() << "< drawing rectangle enabled>";
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
	isGenererLapin = true;
	isGenererDragon = false;
	isGenererModele3D = true;
}

//Si on appuie sur le bouton dragon, le modele 3D devient le dragon
void Renderer::boutonDragonPressed(){
	isGenererOctaedre = false;
	isGenererTetraedre = false;
	modele.loadModel("dragon.obj");
	isGenererDragon = true;
	isGenererLapin = false;
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
    ofEnableDepthTest();
    ofFill();
    ofSetLineWidth(1);
    ofSetColor(1);

    //On ajuste la proportion du modele selon les sliders de proportion
    modele.setScale(sliderProportion3DX / 2, sliderProportion3DY / 2, sliderProportion3DZ / 2);
    //On ajuste l'angle de rotation selon les sliders de rotation
    modele.setRotation(0, sliderRotation3DX, 1, 0, 0);
    modele.setRotation(1, sliderRotation3DY, 0, 1, 0);
	modele.setRotation(2, sliderRotation3DZ + 180, 0, 0, 1);

	modele.setPosition(0, 0, -offset_scene);
	modele.draw(OF_MESH_FILL);
    modele.drawFaces();

    ofDisableDepthTest();
}

//genere un tetraedre
void Renderer::genererTetraedre() {
	ofFill();
	ofSetColor(currentColor);
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

	//rotation x
	if (isRotation3DXPrimitiveGeo) {
		sommet1 = ofVec3f(0,
			-((taille*0.75) / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo)),
			-((taille*0.75) / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo)));
	}

	//rotation z
	else if (isRotation3DZPrimitiveGeo) {
		sommet1 = ofVec3f(((taille*0.75) / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo)),
			((-(taille*0.75) / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo))), 0);
	}
	//ajoute l'origine
	sommet1 += origineTetraedre;

	//sommet de derriere
	ofVec3f sommet2 = ofVec3f(0, (taille*0.75) / 2, -(taille / (2* (sqrt(0.75)))));

	//rotation x
	if (isRotation3DXPrimitiveGeo) {
		sommet2 = ofVec3f(0,
			((taille*0.75) / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo)) + (-(taille / (2 * (sqrt(0.75)))))*sin(ofDegToRad(sliderRotationPrimitiveGeo)),
			-(taille / (2 * (sqrt(0.75))))*cos(ofDegToRad(sliderRotationPrimitiveGeo)) - ((taille*0.75) / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo)));
	}

	//rotation y
	else if (isRotation3DYPrimitiveGeo) {
		sommet2 = ofVec3f((taille / (2 * (sqrt(0.75))))*sin(ofDegToRad(sliderRotationPrimitiveGeo)), (taille*0.75) / 2, -(taille / (2 * (sqrt(0.75))))*cos(ofDegToRad(sliderRotationPrimitiveGeo)));
	}

	//rotation z
	else if (isRotation3DZPrimitiveGeo) {
		sommet2 = ofVec3f(-((taille*0.75) / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo)), ((taille*0.75) / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo)), -(taille / (2 * (sqrt(0.75)))));

	}

	//ajoute l'origine
	sommet2 += origineTetraedre;


	//sommet avant gauche
	ofVec3f sommet3 = ofVec3f(-(taille/2), (taille*0.75)/2, (taille / 4* sqrt(0.75)));

	//rotation x
	if (isRotation3DXPrimitiveGeo) {
		sommet3 = ofVec3f(-(taille / 2),
			(((taille*0.75) / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo)) + (taille / 4 * sqrt(0.75))*sin(ofDegToRad(sliderRotationPrimitiveGeo))),
			((taille / 4 * sqrt(0.75))*cos(ofDegToRad(sliderRotationPrimitiveGeo)) - ((taille*0.75) / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo))));
	}
	
	//rotation y
	else if (isRotation3DYPrimitiveGeo) {
		sommet3 = ofVec3f(-(taille / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo)) - (taille / 4 * sqrt(0.75))*sin(ofDegToRad(sliderRotationPrimitiveGeo)),
			(taille*0.75) / 2,
			(taille / 4 * sqrt(0.75))*cos(ofDegToRad(sliderRotationPrimitiveGeo)) + (-(taille / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo))));
	}
	
	//rotation z
	else if (isRotation3DZPrimitiveGeo) {
		sommet3 = ofVec3f(((-(taille / 2))*cos(ofDegToRad(sliderRotationPrimitiveGeo))) - (((taille*0.75) / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo))),
			(((taille*0.75) / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo))) + ((-(taille / 2))*sin(ofDegToRad(sliderRotationPrimitiveGeo))),
			(taille / 4 * sqrt(0.75)));
	}

	//ajoute l'origine
	sommet3 += origineTetraedre;


	//sommet avant droit
	ofVec3f sommet4 = ofVec3f((taille / 2), (taille*0.75) / 2, (taille / 4 * sqrt(0.75)));

	//rotation x
	if (isRotation3DXPrimitiveGeo) {
		sommet4 = ofVec3f((taille / 2),
			(((taille*0.75) / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo)) + (taille / 4 * sqrt(0.75))*sin(ofDegToRad(sliderRotationPrimitiveGeo))),
			((taille / 4 * sqrt(0.75))*cos(ofDegToRad(sliderRotationPrimitiveGeo)) - ((taille*0.75) / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo))));
	}
	
	//rotation y
	else if (isRotation3DYPrimitiveGeo) {
		sommet4 = ofVec3f((taille / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo)) - (taille / 4 * sqrt(0.75))*sin(ofDegToRad(sliderRotationPrimitiveGeo)),
			(taille*0.75) / 2,
			(taille / 4 * sqrt(0.75))*cos(ofDegToRad(sliderRotationPrimitiveGeo)) + ((taille / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo))));
	}
	
	//rotation z
	else if (isRotation3DZPrimitiveGeo) {
		sommet4 = ofVec3f((((taille / 2))*cos(ofDegToRad(sliderRotationPrimitiveGeo))) - (((taille*0.75) / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo))),
			(((taille*0.75) / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo))) + (((taille / 2))*sin(ofDegToRad(sliderRotationPrimitiveGeo))),
			(taille / 4 * sqrt(0.75)));
	}

	//ajoute l'origine
	sommet4 += origineTetraedre;
	
	//dessin des triangles avec les points
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


void Renderer::genererOctaedre() {
	ofFill();
	ofSetColor(currentColor);
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

	//rotation x
	if (isRotation3DXPrimitiveGeo) {
		sommet1 = ofVec3f(0,
			-((taille*0.75))*cos(ofDegToRad(sliderRotationPrimitiveGeo)),
			-((taille*0.75))*sin(ofDegToRad(sliderRotationPrimitiveGeo)));
	}

	//rotation z
	else if (isRotation3DZPrimitiveGeo) {
		sommet1 = ofVec3f(((taille*0.75))*sin(ofDegToRad(sliderRotationPrimitiveGeo)),
			((-(taille*0.75))*cos(ofDegToRad(sliderRotationPrimitiveGeo))), 0);
	}
	//ajoute l'origine
	sommet1 += origineOctaedre;

	//sommet de derriere
	ofVec3f sommet2 = ofVec3f(0, 0, -(taille) / (2* sqrt(0.75)));

	//rotation x
	if (isRotation3DXPrimitiveGeo) {
		sommet2 = ofVec3f(0,
			(-(taille) / (2 * sqrt(0.75)))*sin(ofDegToRad(sliderRotationPrimitiveGeo)),
			((taille) / (2 * sqrt(0.75)))*cos(ofDegToRad(sliderRotationPrimitiveGeo)));
	}

	//rotation y
	else if (isRotation3DYPrimitiveGeo) {
		sommet2 = ofVec3f(((taille) / (2 * sqrt(0.75)))*sin(ofDegToRad(sliderRotationPrimitiveGeo)), 0, -((taille) / (2 * sqrt(0.75)))*cos(ofDegToRad(sliderRotationPrimitiveGeo)));
	}

	//ajoute l'origine
	sommet2 += origineOctaedre;


	//sommet avant gauche
	ofVec3f sommet3 = ofVec3f(-(taille / 2), 0, (taille) / (4* sqrt(0.75)));

	//rotation x
	if (isRotation3DXPrimitiveGeo) {
		sommet3 = ofVec3f(-(taille / 2),
			(((taille) / (4 * sqrt(0.75)))*sin(ofDegToRad(sliderRotationPrimitiveGeo))),
			(((taille) / (4 * sqrt(0.75)))*cos(ofDegToRad(sliderRotationPrimitiveGeo))));

	}

	//rotation y
	else if (isRotation3DYPrimitiveGeo) {
		sommet3 = ofVec3f(-(taille / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo)) - ((taille) / (4 * sqrt(0.75)))*sin(ofDegToRad(sliderRotationPrimitiveGeo)),
			0,
			((taille) / (4 * sqrt(0.75)))*cos(ofDegToRad(sliderRotationPrimitiveGeo)) + (-(taille / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo))));
	}

	//rotation z
	else if (isRotation3DZPrimitiveGeo) {
		sommet3 = ofVec3f(((-(taille / 2))*cos(ofDegToRad(sliderRotationPrimitiveGeo))),
			((-(taille / 2))*sin(ofDegToRad(sliderRotationPrimitiveGeo))),
			(taille) / (4 * sqrt(0.75)));
	}

	//ajoute l'origine
	sommet3 += origineOctaedre;


	/***x' = x cos f - y sin f***/
	/***y' = y cos f + x sin f***/

	//sommet avant droit
	ofVec3f sommet4 = ofVec3f((taille / 2), 0, (taille) / (4 * sqrt(0.75)));

	//rotation x
	if (isRotation3DXPrimitiveGeo) {
		sommet4 = ofVec3f((taille / 2),
			((taille) / (4 * sqrt(0.75)))*sin(ofDegToRad(sliderRotationPrimitiveGeo))),
			(((taille) / (4 * sqrt(0.75)))*cos(ofDegToRad(sliderRotationPrimitiveGeo)));
	}

	//rotation y
	else if (isRotation3DYPrimitiveGeo) {
		sommet4 = ofVec3f((taille / 2)*cos(ofDegToRad(sliderRotationPrimitiveGeo)) - ((taille) / (4 * sqrt(0.75)))*sin(ofDegToRad(sliderRotationPrimitiveGeo)),
			0,
			((taille) / (4 * sqrt(0.75)))*cos(ofDegToRad(sliderRotationPrimitiveGeo)) + ((taille / 2)*sin(ofDegToRad(sliderRotationPrimitiveGeo))));
	}

	//rotation z
	else if (isRotation3DZPrimitiveGeo) {
		sommet4 = ofVec3f((((taille / 2))*cos(ofDegToRad(sliderRotationPrimitiveGeo))),
			(((taille / 2))*sin(ofDegToRad(sliderRotationPrimitiveGeo))),
			(taille) / (4 * sqrt(0.75)));
	}

	//ajoute l'origine
	sommet4 += origineOctaedre;

	//sommet du dessous
	ofVec3f sommet5 = ofVec3f(0, (taille*0.75), 0);

	//rotation x
	if (isRotation3DXPrimitiveGeo) {
		sommet5 = ofVec3f(0,
			((taille*0.75))*cos(ofDegToRad(sliderRotationPrimitiveGeo)),
			((taille*0.75))*sin(ofDegToRad(sliderRotationPrimitiveGeo)));
	}

	//rotation z
	else if (isRotation3DZPrimitiveGeo) {
		sommet5 = ofVec3f((-(taille*0.75))*sin(ofDegToRad(sliderRotationPrimitiveGeo)),
			(((taille*0.75))*cos(ofDegToRad(sliderRotationPrimitiveGeo))), 0);
	}
	//ajoute l'origine
	sommet5 += origineOctaedre;


	//dessin des triangles avec les points
	ofDrawTriangle(sommet1, sommet2, sommet3);
	ofDrawTriangle(sommet1, sommet2, sommet4);
	ofDrawTriangle(sommet1, sommet3, sommet4);
	ofDrawTriangle(sommet2, sommet3, sommet4);
	ofDrawTriangle(sommet5, sommet2, sommet3);
	ofDrawTriangle(sommet5, sommet2, sommet4);
	ofDrawTriangle(sommet5, sommet3, sommet4);

	//dessin des aretes
	ofSetColor(255, 255, 255);
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

//primitive geo
void Renderer::buttonRotation3DXPressed() {
	isRotation3DXPrimitiveGeo = true;
	isRotation3DYPrimitiveGeo = false;
	isRotation3DZPrimitiveGeo = false;
	sliderRotationPrimitiveGeo.setName("Rotation sur X");
}
void Renderer::buttonRotation3DYPressed() {
	isRotation3DXPrimitiveGeo = false;
	isRotation3DYPrimitiveGeo = true;
	isRotation3DZPrimitiveGeo = false;
	sliderRotationPrimitiveGeo.setName("Rotation sur Y");

}
void Renderer::buttonRotation3DZPressed() {
	isRotation3DXPrimitiveGeo = false;
	isRotation3DYPrimitiveGeo = false;
	isRotation3DZPrimitiveGeo = true;
	sliderRotationPrimitiveGeo.setName("Rotation sur Z");

}

//Generer boite autour des modeles 3D
void Renderer::genererBoite() {

	ofSetColor(currentColor);

	if (isGenererLapin) {
		boite = ofBoxPrimitive(500, 700, 350);
		//On met la boite à la meme position que le modele pour obtenir un rotation symetrique au modele
		boite.setPosition((screenWidth / 2), screenHeight*0.75, 0);
		//On suit la meme rotation que le modele
		boite.rotate(-sliderRotation3DX, 1, 0, 0);
		boite.rotate(-sliderRotation3DY, 0, 1, 0);
		boite.rotate(sliderRotation3DZ, 0, 0, 1);
		boite.setScale(sliderProportion3DX, sliderProportion3DY, sliderProportion3DZ);
		boite.draw();
	}
	else if (isGenererDragon) {
		boite = ofBoxPrimitive(400, 600, 200);
		//On met la boite à la meme position que le modele pour obtenir un rotation symetrique au modele
		boite.setPosition((screenWidth / 2), screenHeight*0.75, 0);
		//On suit la meme rotation que le modele
		boite.rotate(-sliderRotation3DX, 1, 0, 0);
		boite.rotate(-sliderRotation3DY, 0, 1, 0);
		boite.rotate(sliderRotation3DZ, 0, 0, 1);

		boite.setScale(sliderProportion3DX, sliderProportion3DY, sliderProportion3DZ);
		boite.draw();
	}
	
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
	}
}

void Renderer::detectionBordureToggled(bool & detectionBordure) {
	if (detectionBordure) {
		aiguiser.set(false);
		bosseler.set(false);
		flou.set(false);
		kernel_type = ConvolutionKernel::edge_detect;
		kernel_name = "détection de bordure";
	}
}

void Renderer::bosselerToggled(bool & bosseler) {
	if (bosseler) {
		aiguiser.set(false);
		detectionBordure.set(false);
		flou.set(false);
		kernel_type = ConvolutionKernel::emboss;
		kernel_name = "bosseler";
	}
}

void Renderer::flouToggled(bool & flou) {
	if (flou) {
		aiguiser.set(false);
		detectionBordure.set(false);
		bosseler.set(false);
		kernel_type = ConvolutionKernel::blur;
		kernel_name = "flou";
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

	ofLog() << "<convolution filter done>";
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

//Traitement d'image
void Renderer::compositionToggled(bool &composition) {
	if (composition) {
		convolutionFilter.set(false);
		proceduralTexture.set(false);
	}
}
void Renderer::convolutionToggled(bool &convolution) {
	if (convolution) {
		imageComposition.set(false);
		proceduralTexture.set(false);
	}
}
void Renderer::proceduralToggled(bool &procedural) {
	if (procedural) {
		imageComposition.set(false);
		convolutionFilter.set(false);
	}
}

void Renderer::fillingModeSwitched(bool &fillingMode) {
    is_filled = fillingMode;
}
void Renderer::resetCamera()
{
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

	ofLog() << "<reset>";
}

void Renderer::setup_camera()
{
	switch (camera_active)
	{
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

	if (toggleProjectionPerspective)
	{
		camera->disableOrtho();
	}
	else
	{
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
	}
	else {
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
	}
	else {
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
	}
	else {
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
	}
	else {
		isSurfaceParametriqueActive = false;
	}
}

void Renderer::resetSurfaceParametrique() {
	float w_1_4 = (screenWidth / 4.0f) - screenWidth / 2;
	float w_3_4 = (screenWidth * 3.0f / 4.0f) - screenWidth / 2;
	float h_2_5 = (screenHeight * 2.0f / 5.0f) - screenHeight / 2;
	float h_3_5 = (screenHeight * 3.0f / 5.0f) - screenHeight / 2;
	float profondeur = 200;

	pointDeControleSurface1 = { w_1_4, h_3_5, 0 };
	pointDeControleSurface2 = { w_1_4, h_2_5, 0 };
	pointDeControleSurface3 = { w_3_4, h_3_5, 0 };
	pointDeControleSurface4 = { w_3_4, h_2_5, 0 };
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
	}
	else {
		isTriangulation = false;
	}
}

void Renderer::toggleActiverBrumePressed(bool &brume) {
	if (brume) {
		brumeActiver = true;
	}
	else {
		brumeActiver = false;
		glDisable(GL_FOG);
	}
}


void Renderer::activerBrume() {

	glEnable(GL_LIGHTING);

	ofColor blanc = ofColor(1, 1, 1, 1.0f);
	GLfloat couleursPourBlanc[4] = { blanc.r, blanc.g, blanc.b, blanc.a };
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, couleursPourBlanc);
	glFogf(GL_FOG_DENSITY, 1);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, camera->getPosition().z + 500);
	glFogf(GL_FOG_END, camera->getPosition().z + -800);
	glFogi(GL_FOG_COORD_SRC, GL_FOG_COORDINATE);

	glEnable(GL_FOG);
}

Renderer::~Renderer() {
    releaseSelection();
}
