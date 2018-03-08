//
// Created by deziar27 on 18-03-06.
//

#include "rectangle.h"

Rectangle::Rectangle(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
           const float& reqY2, const float& reqThickness, const bool& filled):
        Primitive(reqColor), x1(reqX1), y1(reqY1), x2(reqX2), y2(reqY2), thickness(reqThickness), is_filled(filled) {
    if (x1 > x2) {
        swap(x1, x2);
    }
    if (y1 > y2) {
        swap(y1, y2);
    }
    primitive_nbr++;
    ofLog() << "<New primitive: (" << primitive_nbr << ") >";
}

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

void Rectangle::reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) {
    if (reqX1  < reqX2) {
        x1 = reqX1;
        x2 = reqX2;
        y1 = reqY1;
        y2 = reqY2;
    } else {
        x1 = reqX2;
        x2 = reqX1;
        y1 = reqY2;
        y2 = reqY1;
    }
}

bool Rectangle::isSelected(const float& reqX, const float& reqY) const {
    bool value = false;
    if (x1 - thickness <= reqX && reqX <= x2  + thickness && y1 - thickness <= reqY && reqY <= y2 + thickness) {
        value = true;
    }
    return value;
}

Primitive* Rectangle::clone() const {
    primitive_nbr++;
    ofLog() << "<New primitive: (" << primitive_nbr << ") >";
    return new Rectangle(*this);
}

Rectangle::~Rectangle() {
    primitive_nbr--;
    ofLog() << "<Deletion of primitive: (" << primitive_nbr << ") >";
}
