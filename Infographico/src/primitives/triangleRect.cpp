//
// Created by deziar27 on 18-03-07.
//

#include "triangleRect.h"

TriangleRect::TriangleRect(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
                    const float& reqY2, const float& reqThickness, const bool& filled):
        Primitive(reqColor), x1(reqX1), y1(reqY1), x2(reqX1), y2(reqY2), x3(reqX2), y3(reqY1),
        thickness(reqThickness), is_filled(filled) {

}

void TriangleRect::draw() const {
    if(is_filled) {
        ofFill();
    } else {
        ofNoFill();
    }
    ofSetColor(color);
    ofSetLineWidth(thickness);
    ofDrawTriangle(x1, y1, x2, y2, x3, y3);
}

bool TriangleRect::isSelected(const float& reqX, const float& reqY) const {
    bool value = false;
    float gradient = (y3 - y2) / (x3 - x2);
    float intercept = y3 - gradient*x3;
    if (x1 < x3 && y1 < y2) {
        if (reqX >= x1 && reqY >= y1 && reqY < (gradient*reqX + intercept) + thickness) {
            value = true;
        }
    } else if (x1 > x3 && y1 > y2) {
        if (reqX <= x1 && reqY <= y1 && reqY > (gradient*reqX + intercept) - thickness) {
            value = true;
        }
    } else if (x1 < x3 && y1 > y2) {
        if (reqX >= x1 && reqY <= y1 && reqY > (gradient*reqX + intercept) - thickness) {
            value = true;
        }
    } else if (x1 > x3 && y1 < y2) {
        if (reqX <= x1 && reqY >= y1 && reqY < (gradient*reqX + intercept) + thickness) {
            value = true;
        }
    }
    return value;
}

Primitive* TriangleRect::clone() const {
    return new TriangleRect(*this);
}