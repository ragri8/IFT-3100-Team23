#pragma once

#include "Vector.h"

class RayCastImage
{
public:
	int width;  // largeur de l'image
	int height; // hauteur de l'image
	int count;  // nombre de pixels
	int index;  // index d'un des pixels

	double size; // poids en mémoire (MB)
				 
	Vector* pixel; // pointeur vers une séquence de pixels sous forme vectorielle

	// constructeurs
	RayCastImage() : width(1), height(1) {}
	RayCastImage(int w) : width(w), height(w) {}
	RayCastImage(int w, int h) : width(w), height(h) {}

	void resize(int w, int h);

	~RayCastImage();
};

