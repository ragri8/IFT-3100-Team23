#include "RayCastImage.h"

#include <math.h>

// fonction qui redimensionne l'image
void RayCastImage::resize(int w, int h)
{
	if (w > 0 && h > 0)
	{
		width = w;
		height = h;

		// calculer le nombre de pixels dans l'image
		count = width * height;

		// calculer la taille de l'espace mémoire (en mégaoctets)
		size = sizeof(Vector) * count / pow(1024.0, 2);

		// allocation de la mémoire pour les pixels de l'image
		pixel = new Vector[count];
	}
}

RayCastImage::~RayCastImage()
{
	if (pixel != nullptr)
		delete[] pixel;
}
