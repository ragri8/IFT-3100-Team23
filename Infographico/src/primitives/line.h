//
// Created by deziar27 on 18-03-06.
//

#ifndef INFOGRAPHICO_LINE_H
#define INFOGRAPHICO_LINE_H

#include "primitive.h"
#include <cmath>

class Line: public Primitive {
public:
    Line(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
         const float& reqY2, const float& reqThickness);

    void draw() const final;
    void reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) final;
    bool isSelected(const float& reqX, const float& reqY) const final;
    Primitive* clone() const final;
    ~Line();


private:
    float x1;
    float y1;
    float x2;
    float y2;
    float thickness;
};


#endif //INFOGRAPHICO_LINE_H
