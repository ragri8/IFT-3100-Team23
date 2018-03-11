//
// Created by deziar27 on 18-03-07.
//

#include "triangleRect.h"

TriangleRect::TriangleRect(const ofColor& reqColor, const float& reqX1, const float& reqY1, const float& reqX2,
                    const float& reqY2, const float& reqThickness, const bool& filled):
        Primitive(reqColor, reqX1, reqY1, reqThickness), x2(reqX1), y2(reqY2), x3(reqX2), y3(reqY1),
        is_filled(filled) {
    primitive_nbr++;
    ofLog() << "<New primitive: (" << primitive_nbr << ") >";
}

void TriangleRect::draw() const {
    if(is_filled) {
        ofFill();
    } else {
        ofNoFill();
    }
    ofSetColor(color);
    ofSetLineWidth(thickness);
    ofDrawTriangle(origin_x, origin_y, x2, y2, x3, y3);
}

void TriangleRect::setFill(bool fill_state) {
    is_filled = fill_state;
}

bool TriangleRect::getFill() const {
    return is_filled;
}

pair<float, float> TriangleRect::getSecondPoint() const {
    return make_pair(x3, y2);
}

void TriangleRect::reshape(const float& reqX1, const float& reqY1, const float& reqX2, const float& reqY2) {
    origin_x = reqX1;
    origin_y = reqY1;
    x2 = reqX1;
    y2 = reqY2;
    x3 = reqX2;
    y3 = reqY1;
}

void TriangleRect::translate(const float& reqX, const float& reqY) {
    origin_x += reqX;
    x2 += reqX;
    origin_y += reqY;
    y2 += reqY;
    x3 += reqX;
    y3 += reqY;
}

bool TriangleRect::isSelected(const float& reqX, const float& reqY) const {
    bool value = false;
    float gradient = (y3 - y2) / (x3 - x2);
    float intercept = y3 - gradient*x3;
    if (origin_x < x3 && origin_y < y2) {
        if (reqX >= origin_x && reqY >= origin_y && reqY < (gradient*reqX + intercept) + thickness) {
            value = true;
        }
    } else if (origin_x > x3 && origin_y > y2) {
        if (reqX <= origin_x && reqY <= origin_y && reqY > (gradient*reqX + intercept) - thickness) {
            value = true;
        }
    } else if (origin_x < x3 && origin_y > y2) {
        if (reqX >= origin_x && reqY <= origin_y && reqY > (gradient*reqX + intercept) - thickness) {
            value = true;
        }
    } else if (origin_x > x3 && origin_y < y2) {
        if (reqX <= origin_x && reqY >= origin_y && reqY < (gradient*reqX + intercept) + thickness) {
            value = true;
        }
    }
    return value;
}

bool TriangleRect::operator==(const Primitive& reqPrimitive) const {
    bool value = false;
    if (color == reqPrimitive.getColor() && thickness == reqPrimitive.getThickness()
        && is_filled == reqPrimitive.getFill() &&  getOrigin() == reqPrimitive.getOrigin()
        && getSecondPoint() == reqPrimitive.getSecondPoint()) {
        value = true;
    }
    return value;
}

Primitive* TriangleRect::clone() const {
    primitive_nbr++;
    ofLog() << "<New primitive: (" << primitive_nbr << ") >";
    return new TriangleRect(*this);
}

TriangleRect::~TriangleRect() {
    primitive_nbr--;
    ofLog() << "<Deletion of primitive: (" << primitive_nbr << ") >";
}
