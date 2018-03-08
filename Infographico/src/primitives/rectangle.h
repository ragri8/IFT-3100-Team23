//
// Created by deziar27 on 18-03-06.
//

#ifndef INFOGRAPHICO_RECTANGLE_H
#define INFOGRAPHICO_RECTANGLE_H

#include "primitive.h"

class Rectangle: public Primitive {
public:
    Rectangle(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
         const float& reqY2, const float& reqThickness, const bool& filled=false);

    void draw() const final;
    void reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) final;
    bool isSelected(const float& reqX, const float& reqY) const final;
    Primitive* clone() const final;
    ~Rectangle();


private:
    float x1;
    float y1;
    float x2;
    float y2;
    float thickness;
    bool is_filled;
};


#endif //INFOGRAPHICO_RECTANGLE_H
