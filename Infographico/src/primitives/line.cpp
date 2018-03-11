//
// Created by deziar27 on 18-03-06.
//

#include "line.h"

Line::Line(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
     const float& reqY2, const float& reqThickness):
    Primitive(reqColor, reqX1, reqY1, reqThickness), x2(reqX2), y2(reqY2) {
    if (origin_x > x2) {
        swap(origin_x, x2);
        swap(origin_y, y2);
    }
    primitive_nbr++;
    ofLog() << "<New primitive: (" << primitive_nbr << ") >";
}

void Line::draw() const {
    ofFill();
    ofSetColor(color);
    ofSetLineWidth(thickness);
    ofDrawLine(origin_x, origin_y, x2, y2);
    //ofLog() << "< draw line>";
    //ofDrawCircle(x1, y1, thickness/2);
    //ofDrawCircle(x2, y2, thickness/2);
}

pair<float, float> Line::getSecondPoint() const {
    return make_pair(x2, y2);
}

void Line::reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) {
    if (reqX1  < reqX2) {
        origin_x = reqX1;
        x2 = reqX2;
        origin_y = reqY1;
        y2 = reqY2;
    } else {
        origin_x = reqX2;
        x2 = reqX1;
        origin_y = reqY2;
        y2 = reqY1;
    }
}

void Line::translate(const float& reqX, const float& reqY) {
    origin_x += reqX;
    x2 += reqX;
    origin_y += reqY;
    y2 += reqY;
}

bool Line::isSelected(const float& reqX, const float& reqY) const {
    bool value = false;
    if (x2 != origin_x) {
        if (origin_x - max(thickness, 2.0f) <= reqX &&
                reqX <= x2 + max(thickness, 2.0f) &&
                min(origin_y, y2) - max(thickness, 2.0f) <= reqY &&
                reqY <= max(origin_y, y2) + max(thickness, 2.0f)) {
            float gradient = (y2 - origin_y) / (x2 - origin_x);
            float intercept = y2 - gradient*x2;
            if (abs(gradient) < 1.0f) {
                if (abs(reqY - (gradient*reqX + intercept)) < max(thickness, 2.0f)) {
                    value = true;
                }
            } else if (abs(reqX - (reqY - intercept)/gradient) < max(thickness, 2.0f)) {
                value = true;
            }
        }
    } else if (abs(origin_x - reqX) < max(thickness, 2.0f) &&
            origin_y <= reqY &&
            reqY <= y2) {
        value = true;
    }
    return value;
}

bool Line::operator==(const Primitive& reqPrimitive) const {
    bool value = false;
    if (color == reqPrimitive.getColor() && thickness == reqPrimitive.getThickness()
        &&  getOrigin() == reqPrimitive.getOrigin() && getSecondPoint() == reqPrimitive.getSecondPoint()) {
        value = true;
    }
    return value;
}

Primitive* Line::clone() const {
    primitive_nbr++;
    ofLog() << "<New primitive: (" << primitive_nbr << ") >";
    return new Line(*this);
}

Line::~Line() {
    primitive_nbr--;
    ofLog() << "<Deletion of primitive: (" << primitive_nbr << ") >";
}
