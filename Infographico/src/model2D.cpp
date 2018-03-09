//
// Created by deziar27 on 18-03-06.
//

#include "model2D.h"

Model2D::Model2D() {
    current_index = 0;
}

unsigned int Model2D::getCurrentIndex() const {
    return current_index;
}

void Model2D::setName(std::string reqName) {
    name = reqName;
}

std::string Model2D::getName() const {
    return name;
}

void Model2D::draw() const {
    for (auto iter = v_primitives.rbegin(); iter != v_primitives.rend(); iter++) {
        (*iter)->draw();
    }
}

void Model2D::addPrimitive(const Primitive& reqPrimitive) {
    v_primitives.push_back(reqPrimitive.clone());
}

vector<Primitive*>::iterator Model2D::last() {
    return (v_primitives.end())--;
}

unsigned int Model2D::lastIndex() const {
    return (unsigned int)v_primitives.size()-1;
}

vector<Primitive*>::iterator Model2D::insertPrimitive(const vector<Primitive*>::iterator& iter, const Primitive& reqPrimitive) {
    return v_primitives.insert(iter, reqPrimitive.clone());
}

vector<Primitive*>* Model2D::getPrimitives() {
    return &v_primitives;
}

bool Model2D::findPrimitive(const float reqX, const float reqY) {
    bool isFound = false;
    for (unsigned int i = v_primitives.size(); i != 0; i--) {
        if (v_primitives[i-1]->isSelected(reqX, reqY)) {
            current_index = i-1;
            isFound = true;
            break;
        }
    }
    return isFound;
}

void Model2D::deletePrimitive(const vector<Primitive*>::iterator& iter) {
    v_primitives.erase(iter);
}

Model2D::~Model2D() {
    for (auto i = v_primitives.begin(); i != v_primitives.end(); i++) {
        delete *i;
    }
    v_primitives.clear();
}