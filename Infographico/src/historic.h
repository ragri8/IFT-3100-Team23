//
// Created by deziar27 on 18-03-07.
//

#ifndef INFOGRAPHICO_HISTORIC_H
#define INFOGRAPHICO_HISTORIC_H

#include "primitives/primitive.h"
#include <list>
#include <stack>

enum class Action {modify, add, remove};

class History {
public:
    History();

    void undo(vector<Primitive*>* reqVector);
    void redo(vector<Primitive*>* reqVector);

    void addChange(unsigned int index, Action action, Primitive* primitive);
    tuple<unsigned int, Action, Primitive*> restoreChange() const;
    void deleteLast();

    void addRestoredChange(unsigned int index, Action action, Primitive* primitive);
    tuple<unsigned int, Action, Primitive*> unrestoreChange() const;
    void deleteRestoredLast();
    void eraseRestored();

    ~History();

private:
    stack<std::tuple<unsigned int, Action, Primitive*>> previous_states;
    stack<std::tuple<unsigned int, Action, Primitive*>> restored_states;
};


#endif //INFOGRAPHICO_HISTORIC_H
