//
// Created by deziar27 on 18-03-07.
//

#ifndef INFOGRAPHICO_TRIANGLERECT_H
#define INFOGRAPHICO_TRIANGLERECT_H

#include "primitive.h"

class TriangleRect: public Primitive {
public:
    TriangleRect(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
         const float& reqY2, const float& reqThickness, const bool& filled=false);

    void draw() const final;
    void reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) final;
    bool isSelected(const float& reqX, const float& reqY) const final;
    Primitive* clone() const final;
    ~TriangleRect();


private:
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float thickness;
    bool is_filled;
};

#endif //INFOGRAPHICO_TRIANGLERECT_H
