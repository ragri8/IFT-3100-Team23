#include "ofMain.h"
#include "application.h"

//========================================================================
int main( ){
	// paramètres du contexte de rendu OpenGL
	ofGLWindowSettings windowSettings;

	// résolution de la fenêtre d'affichage
	windowSettings.width  = 1600;
	windowSettings.height = 900;

	// sélection de la version (OpenGL 3.3 / GLSL 330)
	windowSettings.setGLVersion(3, 3);

	// création de la fenêtre
	ofCreateWindow(windowSettings);

	// démarrer l'exécution de l'application
	ofRunApp(new Application());

}
