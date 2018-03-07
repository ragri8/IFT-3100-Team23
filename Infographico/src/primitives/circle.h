//
// Created by deziar27 on 18-03-06.
//

#ifndef INFOGRAPHICO_CIRCLE_H
#define INFOGRAPHICO_CIRCLE_H

#include "primitive.h"
#include <cmath>

class Circle: public Primitive {
public:
    Circle(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
           const float& reqY2, const float& reqThickness, const bool& filled=true);

    void draw() const final;
    bool isSelected(const float& reqX, const float& reqY) const final;
    Primitive* clone() const final;


private:
    float x;
    float y;
    float r;
    float thickness;
    bool is_filled;
};


#endif //INFOGRAPHICO_CIRCLE_H
