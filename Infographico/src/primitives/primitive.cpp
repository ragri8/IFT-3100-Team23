//
// Created by deziar27 on 18-03-06.
//

#include "primitive.h"

Primitive::Primitive(const ofColor& reqColor, const float& reqX, const float& reqY, const float& reqThickness) :
    color(reqColor), origin_x(reqX), origin_y(reqY), thickness(reqThickness) {
}

void Primitive::draw() const {}

void  Primitive::changeColor(ofColor& reqColor) {
    color = reqColor;
}

ofColor Primitive::getColor() const {
    return color;
}

pair<float, float> Primitive::getOrigin() const {
    return make_pair(origin_x, origin_y);
}

void Primitive::setThickness(float& reqThickness) {
    thickness = reqThickness;
}

float Primitive::getThickness() const {
    return thickness;
}

Primitive::~Primitive() {}


int Primitive::primitive_nbr = 0;
