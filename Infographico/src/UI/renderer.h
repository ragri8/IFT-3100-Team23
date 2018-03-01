//
// Created by deziar27 on 18-02-22.
//

#ifndef INFOGRAPHICO_RENDERER_H
#define INFOGRAPHICO_RENDERER_H

#include "ofMain.h"


class Renderer {
public:

    void setup();
    void update();
    void draw();

    void image_export(const std::string name, const std::string extension) const;

};


#endif //INFOGRAPHICO_RENDERER_H
