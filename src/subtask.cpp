#include "include/subtask.h"

Subtask::Subtask(QString description, QString priority) {
    this->description = description;
    this->priority = priority;
}

void Subtask::setDone(bool done) {
    this->done = done;
}

bool Subtask::getDone() {
    return done;
}
