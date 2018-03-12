//
// Created by deziar27 on 18-03-06.
//

#ifndef INFOGRAPHICO_PRIMITIVE_H
#define INFOGRAPHICO_PRIMITIVE_H

#include "ofMain.h"

class Primitive {
public:
    Primitive(const ofColor& reqColor, const float& reqX, const float& reqY, const float& reqThickness);
    virtual void draw() const;
    void changeColor(ofColor& reqColor);
    ofColor getColor() const;
    virtual void setFill(bool fill_state)=0;
    virtual bool getFill() const=0;
    pair<float, float> getOrigin() const;
    virtual pair<float, float> getSecondPoint() const=0;
    void setThickness(float& reqThickness);
    float getThickness() const;
    virtual bool isSelected(const float& reqX, const float& reqY) const=0;
    virtual void reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2)=0;
    virtual void translate(const float& reqX, const float& reqY)=0;
    virtual bool operator==(const Primitive& reqPrimitive) const=0;
    virtual Primitive* clone() const = 0;
    virtual ~Primitive();

    static int primitive_nbr;

protected:
    ofColor color;
    float origin_x;
    float origin_y;
    float thickness;

};

#endif //INFOGRAPHICO_PRIMITIVE_H
