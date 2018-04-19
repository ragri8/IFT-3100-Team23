//
// Created by deziar27 on 18-03-11.
//

#include "triangle.h"

Triangle::Triangle(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
                           const float& reqY2, const float& reqThickness, const bool& filled):
        Primitive(reqColor, reqX1, reqY1, reqThickness), x3(reqX2), y2(reqY2), y3(reqY1), is_filled(filled) {
    x2 = (reqX1 + reqX2) / 2.0f;
    primitive_nbr++;
    //ofLog() << "<New primitive: (" << primitive_nbr << ") >";
}

void Triangle::draw() const {
    if(is_filled) {
        ofFill();
    } else {
        ofNoFill();
    }
    ofSetColor(color);
    ofSetLineWidth(thickness);
    ofDrawTriangle(origin_x, origin_y, x2, y2, x3, y3);
}

void Triangle::setFill(bool fill_state) {
    is_filled = fill_state;
}

bool Triangle::getFill() const {
    return is_filled;
}

pair<float, float> Triangle::getSecondPoint() const {
    return make_pair(x3, y2);
}

void Triangle::reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) {
    origin_x = reqX1;
    origin_y = reqY1;
    x2 = (reqX1 + reqX2) / 2.0f;
    y2 = reqY2;
    x3 = reqX2;
    y3 = reqY1;
}

void Triangle::translate(const float& reqX, const float& reqY) {
    origin_x += reqX;
    x2 += reqX;
    origin_y += reqY;
    y2 += reqY;
    x3 += reqX;
    y3 += reqY;
}

bool Triangle::isSelected(const float& reqX, const float& reqY) const {
    bool value = false;
    float gradient_1 = (y2 - origin_y) / (x2 - origin_x);
    float intercept_1 = y2 - gradient_1*x2;
    float gradient_2 = (y3 - y2) / (x3 - x2);
    float intercept_2 = y3 - gradient_2*x3;
    if (origin_y < y2) {
        if (reqY >= origin_y && reqY <= (gradient_1*reqX + intercept_1) + thickness
            && reqY <= (gradient_2*reqX + intercept_2) + thickness) {
            value = true;
        }
    } else {
        if (reqY <= origin_y && reqY >= (gradient_1*reqX + intercept_1) + thickness
            && reqY >= (gradient_2*reqX + intercept_2) + thickness) {
            value = true;
        }
    }
    return value;
}

bool Triangle::operator==(const Primitive& reqPrimitive) const {
    bool value = false;
    if (color == reqPrimitive.getColor() && thickness == reqPrimitive.getThickness()
        && is_filled == reqPrimitive.getFill() &&  getOrigin() == reqPrimitive.getOrigin()
        && getSecondPoint() == reqPrimitive.getSecondPoint()) {
        value = true;
    }
    return value;
}

Primitive* Triangle::clone() const {
    primitive_nbr++;
    //ofLog() << "<New primitive: (" << primitive_nbr << ") >";
    return new Triangle(*this);
}

Triangle::~Triangle() {
    primitive_nbr--;
    //ofLog() << "<Deletion of primitive: (" << primitive_nbr << ") >";
}