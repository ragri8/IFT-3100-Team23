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
    virtual Primitive* clone() const = 0;
    virtual ~Primitive();

protected:
    ofColor color;

};


#endif //INFOGRAPHICO_PRIMITIVE_H
