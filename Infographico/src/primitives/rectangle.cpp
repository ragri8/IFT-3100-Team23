//
// Created by deziar27 on 18-03-06.
//

#include "rectangle.h"

Rectangle::Rectangle(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
           const float& reqY2, const float& reqThickness, const bool& filled):
        Primitive(reqColor, reqX1, reqY1), x2(reqX2), y2(reqY2), thickness(reqThickness), is_filled(filled) {
    if (origin_x > x2) {
        swap(origin_x, x2);
    }
    if (origin_y > y2) {
        swap(origin_y, y2);
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
    ofDrawRectangle(origin_x, origin_y, x2 - origin_x, y2 - origin_y);
}

void Rectangle::setFill(bool fill_state) {
    is_filled = fill_state;
}

bool Rectangle::getFill() const {
    return is_filled;
}

void Rectangle::reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) {
    if (reqX1  < reqX2) {
        origin_x = reqX1;
        x2 = reqX2;
    } else {
        origin_x = reqX2;
        x2 = reqX1;
    }
    if (reqY1 < reqY2) {
        origin_y = reqY1;
        y2 = reqY2;
    } else {
        origin_y = reqY2;
        y2 = reqY1;
    }
}

void Rectangle::translate(const float& reqX, const float& reqY) {
    origin_x += reqX;
    x2 += reqX;
    origin_y += reqY;
    y2 += reqY;
}

bool Rectangle::isSelected(const float& reqX, const float& reqY) const {
    bool value = false;
    if (origin_x - thickness <= reqX && reqX <= x2  + thickness && origin_y - thickness <= reqY && reqY <= y2 + thickness) {
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
