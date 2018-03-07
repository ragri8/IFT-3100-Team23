//
// Created by deziar27 on 18-03-06.
//

#include "primitive.h"

Primitive::Primitive(const ofColor& reqColor) :
    color(reqColor) {
}

void Primitive::draw() const {}

Primitive::~Primitive() {}