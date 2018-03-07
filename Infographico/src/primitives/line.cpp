//
// Created by deziar27 on 18-03-06.
//

#include "line.h"

Line::Line(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
     const float& reqY2, const float& reqThickness):
    Primitive(reqColor), x1(reqX1), y1(reqY1), x2(reqX2), y2(reqY2), thickness(reqThickness) {
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }
}

void Line::draw() const {
    ofFill();
    ofSetColor(color);
    ofSetLineWidth(thickness);
    ofDrawLine(x1, y1, x2, y2);
    //ofLog() << "< draw line>";
    //ofDrawCircle(x1, y1, thickness/2);
    //ofDrawCircle(x2, y2, thickness/2);
}

bool Line::isSelected(const float& reqX, const float& reqY) const {
    bool value = false;
    if (x2 != x1) {
        if (x1 - max(thickness, 2.0f) <= reqX &&
                reqX <= x2 + max(thickness, 2.0f) &&
                min(y1, y2) - max(thickness, 2.0f) <= reqY &&
                reqY <= max(y1, y2) + max(thickness, 2.0f)) {
            float gradient = (y2 - y1) / (x2 - x1);
            float intercept = y2 - gradient*x2;
            if (abs(gradient) < 1.0f) {
                if (abs(reqY - (gradient*reqX + intercept)) < max(thickness, 2.0f)) {
                    value = true;
                }
            } else if (abs(reqX - (reqY - intercept)/gradient) < max(thickness, 2.0f)) {
                value = true;
            }
        }
    } else if (abs(x1 - reqX) < max(thickness, 2.0f) &&
            y1 <= reqY &&
            reqY <= y2) {
        value = true;
    }
    return value;
}

Primitive* Line::clone() const {
    return new Line(*this);
}
