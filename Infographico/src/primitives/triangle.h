//
// Created by deziar27 on 18-03-11.
//

#ifndef INFOGRAPHICO_TRIANGLE_H
#define INFOGRAPHICO_TRIANGLE_H

#include "primitive.h"

class Triangle: public Primitive {
public:
    Triangle(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
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
    ~Triangle();


private:
    float x2;
    float y2;
    float x3;
    float y3;
    bool is_filled;
};


#endif //INFOGRAPHICO_TRIANGLE_H
