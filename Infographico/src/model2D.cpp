//
// Created by deziar27 on 18-03-06.
//

#include "model2D.h"

Model2D::Model2D() {}

list<Primitive*>::iterator Model2D::getCurrent() const {
    return current_itr;
}

void Model2D::setName(std::string reqName) {
    name = reqName;
}

std::string Model2D::getName() const {
    return name;
}

void Model2D::draw() const {
    for (auto iter = primitives.rbegin(); iter != primitives.rend(); iter++) {
        (*iter)->draw();
    }
}

void Model2D::addPrimitive(const Primitive& reqPrimitive) {
    primitives.push_back(reqPrimitive.clone());
}

list<Primitive*>::iterator Model2D::insertPrimitive(const list<Primitive*>::iterator& iter, const Primitive& reqPrimitive) {
    return primitives.insert(iter, reqPrimitive.clone());
}

bool Model2D::findPrimitive(const float reqX, const float reqY) {
    bool isFound = false;
    for (list<Primitive*>::reverse_iterator riter = primitives.rbegin(); riter != primitives.rend(); ++riter) {
        if ((*riter)->isSelected(reqX, reqY)) {
            current_itr = (riter++).base();
            isFound = true;
            break;
        }
    }
    return isFound;
}

void Model2D::deletePrimitive(const list<Primitive*>::iterator& iter) {
    primitives.erase(iter);
}

Model2D::~Model2D() {
    for (auto i = primitives.begin(); i != primitives.end(); i++) {
        delete *i;
    }
    primitives.clear();
}