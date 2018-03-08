//
// Created by deziar27 on 18-03-06.
//

#ifndef INFOGRAPHICO_PRIMITIVE_H
#define INFOGRAPHICO_PRIMITIVE_H

#include "ofMain.h"

class Primitive {
public:
    Primitive(const ofColor& reqColor);
    virtual void draw() const;
    virtual bool isSelected(const float& reqX, const float& reqY) const=0;
    virtual void reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2)=0;
    virtual Primitive* clone() const = 0;
    virtual ~Primitive();

    static int primitive_nbr;

protected:
    ofColor color;

};

#endif //INFOGRAPHICO_PRIMITIVE_H
