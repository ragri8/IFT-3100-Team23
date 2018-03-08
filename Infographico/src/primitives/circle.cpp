//
// Created by deziar27 on 18-03-06.
//

#include "circle.h"

Circle::Circle(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
               const float& reqY2, const float& reqThickness, const bool& filled):
        Primitive(reqColor), x(reqX1), y(reqY1), thickness(reqThickness), is_filled(filled) {
    r = (float)sqrt(pow(reqX2 - reqX1, 2) + pow(reqY2 - reqY1, 2));
    primitive_nbr++;
    ofLog() << "<New primitive: (" << primitive_nbr << ") >";
}

void Circle::draw() const {
    if(is_filled) {
        ofFill();
    } else {
        ofNoFill();
    }
    ofSetColor(color);
    ofSetLineWidth(thickness);
    ofDrawCircle(x, y, r);
}

void Circle::reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) {
    x = reqX1;
    y = reqY1;
    r = (float)sqrt(pow(reqX2 - reqX1, 2) + pow(reqY2 - reqY1, 2));
}

bool Circle::isSelected(const float& reqX, const float& reqY) const {
    bool value = false;
    float distance = (float)sqrt(pow(reqX - x, 2) + pow(reqY - y, 2));
    if (distance <= r) {
        value = true;
    }
    return value;
}

Primitive* Circle::clone() const {
    primitive_nbr++;
    ofLog() << "<New primitive: (" << primitive_nbr << ") >";
    return new Circle(*this);
}

Circle::~Circle() {
    primitive_nbr--;
    ofLog() << "<Deletion of primitive: (" << primitive_nbr << ") >";
}
