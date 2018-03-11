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
    bool getFill() const final {return false;}
    void setFill(bool fill_state) final {}
    pair<float, float> getSecondPoint() const final;
    void reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) final;
    void translate(const float& reqX, const float& reqY) final;
    bool isSelected(const float& reqX, const float& reqY) const final;
    bool operator==(const Primitive& reqPrimitive) const final;
    Primitive* clone() const final;
    ~Line();


private:
    float x2;
    float y2;
};


#endif //INFOGRAPHICO_LINE_H
