//
// Created by deziar27 on 18-03-06.
//

#include "rectangle.h"

Rectangle::Rectangle(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
           const float& reqY2, const float& reqThickness, const bool& filled):
        Primitive(reqColor), x1(reqX1), y1(reqY1), x2(reqX2), y2(reqY2), thickness(reqThickness), is_filled(filled) {}

void Rectangle::draw() const {
    if(is_filled) {
        ofFill();
    } else {
        ofNoFill();
    }
    ofSetColor(color);
    ofSetLineWidth(thickness);
    ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
}

bool Rectangle::isSelected(const float& reqX, const float& reqY) const {
    bool value = false;
    if (x1 <= reqX && reqX <= x2 && y1 <= reqY && reqY <= y2) {
        value = true;
    }
    return value;
}

Primitive* Rectangle::clone() const {
    return new Rectangle(*this);
}