//
// Created by deziar27 on 18-03-06.
//

#ifndef INFOGRAPHICO_MODEL2D_H
#define INFOGRAPHICO_MODEL2D_H

#include "primitives/primitive.h"
#include <vector>
#include <list>

class Model2D {
public:
    Model2D();
    list<Primitive*>::iterator getCurrent() const;
    void draw() const;
    void addPrimitive(const Primitive& reqPrimitive);
    list<Primitive*>::iterator insertPrimitive(const list<Primitive*>::iterator& iter, const Primitive& reqPrimitive);
    bool findPrimitive(const float reqX, const float reqY);
    void deletePrimitive(const list<Primitive*>::iterator& iter);
    virtual ~Model2D();


private:
    list<Primitive*> primitives;
    list<Primitive*>::iterator current_itr;
};


#endif //INFOGRAPHICO_MODEL2D_H
