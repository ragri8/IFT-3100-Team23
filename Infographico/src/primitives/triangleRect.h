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
    void setFill(bool fill_state) final;
    bool getFill() const final;
    pair<float, float> getSecondPoint() const final;
    void reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) final;
    void translate(const float& reqX, const float& reqY) final;
    bool isSelected(const float& reqX, const float& reqY) const final;
    bool operator==(const Primitive& reqPrimitive) const final;
    Primitive* clone() const final;
    ~TriangleRect();


private:
    float x2;
    float y2;
    float x3;
    float y3;
    bool is_filled;
};

#endif //INFOGRAPHICO_TRIANGLERECT_H
