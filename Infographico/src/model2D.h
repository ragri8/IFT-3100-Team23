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

    unsigned int getCurrentIndex() const;
    void setName(std::string reqName);
    std::string getName() const;
    void draw() const;
    void addPrimitive(const Primitive& reqPrimitive);
    vector<Primitive*>::iterator last();
    unsigned int lastIndex() const;
    vector<Primitive*>::iterator insertPrimitive(const vector<Primitive*>::iterator& iter, const Primitive& reqPrimitive);
    vector<Primitive*>* getPrimitives();
    Primitive* getCurrentPrimitive();
    void deleteCurrentPrimitive();
    void replaceCurrentPrimitive(Primitive* reqPrimitive);
    bool findPrimitive(const float reqX, const float reqY);
    void deletePrimitive(const vector<Primitive*>::iterator& iter);
    virtual ~Model2D();


private:
    std::string name="project";
    vector<Primitive*> v_primitives;
    unsigned int current_index;
};


#endif //INFOGRAPHICO_MODEL2D_H
