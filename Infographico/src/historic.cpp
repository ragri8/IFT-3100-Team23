//
// Created by deziar27 on 18-03-07.
//

#include "historic.h"

History::History()=default;

void History::undo(vector<Primitive*>* reqVector) {
    if (!previous_states.empty()) {
        std::tuple<unsigned int, Action, Primitive *> restore_tuple;
        restore_tuple = previous_states.top();
        unsigned int rest_index = get<0>(restore_tuple);
        Action rest_action = get<1>(restore_tuple);
        Primitive *rest_primitive = get<2>(restore_tuple);
        std::tuple<unsigned int, Action, Primitive *> backup_tuple;
        switch (rest_action) {
            case Action::add:
                backup_tuple = make_tuple(rest_index, Action::remove, (*reqVector)[rest_index]->clone());
                restored_states.push(backup_tuple);
                delete *(reqVector->begin() + rest_index);
                reqVector->erase(reqVector->begin() + rest_index);
                delete rest_primitive;
                break;
            case Action::remove:
                backup_tuple = make_tuple(rest_index, Action::add, rest_primitive->clone());
                restored_states.push(backup_tuple);
                reqVector->insert(reqVector->begin() + rest_index, rest_primitive->clone());
                delete rest_primitive;
                break;

            case Action::modify:
                backup_tuple = make_tuple(rest_index, Action::modify, (*reqVector)[rest_index]->clone());
                restored_states.push(backup_tuple);
                delete *(reqVector->begin() + rest_index);
                reqVector->erase(reqVector->begin() + rest_index);
                reqVector->insert(reqVector->begin() + rest_index, rest_primitive->clone());
                delete rest_primitive;
                break;
        }
        previous_states.pop();
    }
}

void History::redo(vector<Primitive*>* reqVector) {
    if (!restored_states.empty()) {
        std::tuple<unsigned int, Action, Primitive *> restore_tuple;
        restore_tuple = restored_states.top();
        unsigned int rest_index = get<0>(restore_tuple);
        Action rest_action = get<1>(restore_tuple);
        Primitive *rest_primitive = get<2>(restore_tuple);
        std::tuple<unsigned int, Action, Primitive *> backup_tuple;
        switch (rest_action) {
            case Action::add:
                backup_tuple = make_tuple(rest_index, Action::remove, (*reqVector)[rest_index]->clone());
                previous_states.push(backup_tuple);
                delete *(reqVector->begin() + rest_index);
                reqVector->erase(reqVector->begin() + rest_index);
                delete rest_primitive;
                break;
            case Action::remove:
                backup_tuple = make_tuple(rest_index, Action::add, rest_primitive->clone());
                previous_states.push(backup_tuple);
                reqVector->insert(reqVector->begin() + rest_index, rest_primitive->clone());
                delete rest_primitive;
                break;

            case Action::modify:
                backup_tuple = make_tuple(rest_index, Action::modify, (*reqVector)[rest_index]->clone());
                previous_states.push(backup_tuple);
                delete *(reqVector->begin() + rest_index);
                reqVector->erase(reqVector->begin() + rest_index);
                reqVector->insert(reqVector->begin() + rest_index, rest_primitive->clone());
                delete rest_primitive;
                break;
        }
        restored_states.pop();
    }
}

void History::addChange(unsigned int index, Action action, Primitive* primitive) {
    previous_states.push(make_tuple(index, action, primitive->clone()));
    eraseRestored();
}

void History::eraseRestored() {
    while(!restored_states.empty()) {
        delete get<2>(restored_states.top());
        restored_states.pop();
    }
}

History::~History() {
    while (!previous_states.empty()) {
        delete get<2>(previous_states.top());
        previous_states.pop();
    }
    while (!restored_states.empty()) {
        delete get<2>(restored_states.top());
        restored_states.pop();
    }
}
