//
// Created by deziar27 on 18-03-06.
//

#include "circle.h"

Circle::Circle(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
               const float& reqY2, const float& reqThickness, const bool& filled):
        Primitive(reqColor, reqX1, reqY1, reqThickness), is_filled(filled) {
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
    ofDrawCircle(origin_x, origin_y, r);
}

void Circle::setFill(bool fill_state) {
    is_filled = fill_state;
}

bool Circle::getFill() const {
    return is_filled;
}

pair<float, float> Circle::getSecondPoint() const {
    return make_pair(origin_x, origin_y+r);
}

void Circle::reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) {
    origin_x = reqX1;
    origin_y = reqY1;
    r = (float)sqrt(pow(reqX2 - reqX1, 2) + pow(reqY2 - reqY1, 2));
}

void Circle::translate(const float& reqX, const float& reqY) {
    origin_x += reqX;
    origin_y += reqY;
}

bool Circle::isSelected(const float& reqX, const float& reqY) const {
    bool value = false;
    float distance = (float)sqrt(pow(reqX - origin_x, 2) + pow(reqY - origin_y, 2));
    if (distance <= r) {
        value = true;
    }
    return value;
}

bool Circle::operator==(const Primitive& reqPrimitive) const {
    bool value = false;
    if (color == reqPrimitive.getColor() && thickness == reqPrimitive.getThickness()
        && is_filled == reqPrimitive.getFill() &&  getOrigin() == reqPrimitive.getOrigin()
        && getSecondPoint() == reqPrimitive.getSecondPoint()) {
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
