//
// Created by deziar27 on 18-02-22.
//

#include "renderer.h"

void Renderer::setup() {
    ofSetFrameRate(60);
}

void Renderer::update() {

}

void Renderer::draw() {
    ofClear(220, 210, 210);
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
