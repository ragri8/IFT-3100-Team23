#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <math.h> 
#include "ofxAssimpModelLoader.h"
#include <limits>

// énumération des types de kernel de convolution
enum class ConvolutionKernel
{
	identity,
	emboss,
	sharpen,
	edge_detect,
	blur
};

// kernel de convolution (3x3) : identité
const std::array<float, 9> convolution_kernel_identity
{
	0.0f,  0.0f,  0.0f,
	0.0f,  1.0f,  0.0f,
	0.0f,  0.0f,  0.0f
};

// kernel de convolution (3x3) : aiguiser
const std::array<float, 9> convolution_kernel_sharpen
{
	0.0f, -1.0f,  0.0f,
	-1.0f,  5.0f, -1.0f,
	0.0f, -1.0f,  0.0f
};

// kernel de convolution (3x3) : détection de bordure
const std::array<float, 9> convolution_kernel_edge_detect
{
	0.0f,  1.0f,  0.0f,
	1.0f, -4.0f,  1.0f,
	0.0f,  1.0f,  0.0f
};

// kernel de convolution (3x3) : bosseler
const std::array<float, 9> convolution_kernel_emboss
{
	-2.0f, -1.0f,  0.0f,
	-1.0f,  1.0f,  1.0f,
	0.0f,  1.0f,  2.0f
};

// kernel de convolution (3x3) : flou
const std::array<float, 9> convolution_kernel_blur
{
	1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f,
	1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f,
	1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f
};

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
	ofxPanel colorPickerGUI;
	ofxToggle rgbMode;
	ofParameter<float> redOrHue;
	ofParameter<float> greenOrSaturation;
	ofParameter<float> blueOrBrightness;
	ofParameter<float> alpha;

	//Generer boite
	ofBoxPrimitive boite;
	//modele 3D
	bool isGenererLapin;
	bool isGenererDragon;

	//animation
	bool animationGrossit;


	//image
	ofImage currentImage;
	bool is_current_image_loaded;

	//Selecting texture mode
	ofParameter<bool> imageComposition;
	ofParameter<bool> convolutionFilter;
	ofParameter<bool> proceduralTexture;

	//Image selector pour composition d'image
	ofxPanel textureCompositionGUI;
	ofxButton boutonImporterTexture1;
	ofxButton boutonImporterTexture2;
	ofParameter<string> textureName1;
	ofParameter<string> textureName2;
	ofParameter<bool> compositionAdd;
	ofImage texture1;
	ofImage texture2;
	bool is_texture1_loaded;
	bool is_texture2_loaded;

	//Traitement d'image par convolution
	ofxPanel filtrageConvolutionGUI;
	ofParameter<bool> aiguiser;
	ofParameter<bool> detectionBordure;
	ofParameter<bool> bosseler;
	ofParameter<bool> flou;
	ofImage filteredImage;
	ConvolutionKernel kernel_type;
	string kernel_name;

	//Texture procédurale
	ofxPanel textureProceduralGUI;
	ofParameter<bool> binaryTree;
	ofParameter<bool> ternaryTree;
	ofParameter<int> branchLength;
	ofParameter<int> angle;
	
	//*******************************************//
	//********************GUI********************//
	//*******************************************//

	//menu general
	ofxPanel guiMenu;
	ofParameter<bool> boutonMode2D;
	ofParameter<bool> boutonMode3D;
	ofxButton boutonImporterImage;
	ofxButton boutonExporterImage;
	ofxLabel labelTraitementImage;
	ofParameter<string> labelSourceImage;
	ofParameter<bool> toggleAfficherImage;


	//interface dessin
	ofxPanel guiDessin;
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

	ofxButton boutonUndo;
	ofxButton boutonRedo;


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
	ofxLabel labelEffet;


	
	//Ecouteur de l'interface
	void boutonLignePressed();
	void boutonEllipsePressed();
	void boutonRectanglePressed();
	void boutonTrianglePressed();
	void boutonTriangleRectanglePressed();
	void boutonMode2DToggled(bool &mode2D);
	void boutonMode3DToggled(bool &mode3D);
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

	//primitive geo 3D	//gui 3d
	ofxLabel labelPrimitiveGeo;
	ofxButton buttonRotation3DX;
	ofxButton buttonRotation3DY;
	ofxButton buttonRotation3DZ;
	ofxFloatSlider sliderRotationPrimitiveGeo;
	bool isRotation3DXPrimitiveGeo;
	bool isRotation3DYPrimitiveGeo;
	bool isRotation3DZPrimitiveGeo;
	//listener
	void buttonRotation3DXPressed();
	void buttonRotation3DYPressed();
	void buttonRotation3DZPressed();

	//Generer boite
	void genererBoite();

	//animation
	void animerMaillage();

	//Image composition functions
	void load_image(const std::string path, ofImage &image, bool &imageLoadSuccess);
	void boutonImporterImageTexture1();
	void boutonImporterImageTexture2();

	//Convolution filter functions
	void aiguiserToggled(bool &aiguiser);
	void detectionBordureToggled(bool &detectionBordure);
	void bosselerToggled(bool &bosseler);
	void flouToggled(bool &flou);
	void filter();

	//Procedural texture functions
	void binaryTreeToggled(bool &binaryTree);
	void ternaryTreeToggled(bool & ternaryTree);
	void drawBinaryTree(int length);
	void drawTernaryTree(int length);


	//Traitement d'image
	void compositionToggled(bool &composition);
	void convolutionToggled(bool &convolution);
	void proceduralToggled(bool &procedural);
	void importImagePressed();

};