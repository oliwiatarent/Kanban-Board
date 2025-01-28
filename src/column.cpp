#include "include/column.h"

#include <QDebug>

Column::Column(QString name) {
    this -> name = name;
}

int Column::getNumberOfTasks() {
    return tasks.size();
}

int Column::getNumberOfNotes() {
    return notes.size();
}

QString Column::getName() {
    return name;
}

void Column::setName(QString newName) {
    this->name = newName;
}

Task* Column::getTask(int index) {
    return &tasks[index];
}

void Column::addTask(Task task) {
    tasks.push_back(task);
}

void Column::deleteTask(int taskIndex) {
    if (taskIndex >= 0 && static_cast<int>(tasks.size())) {
        tasks.erase(tasks.begin() + taskIndex);
    }
}

void Column::editTask(int taskIndex, Task* editedTask) {
    if (taskIndex >= 0 && static_cast<int>(tasks.size())) {
        tasks[taskIndex].setTitle(editedTask->getTitle());
        tasks[taskIndex].setDescription(editedTask->getDescription());
        tasks[taskIndex].setPriority(editedTask->getPriority());

        delete editedTask;
    }
}

Note* Column::getNote(int index) {
    return &notes[index];
}

void Column::addNote(Note note) {
    notes.push_back(note);
}

void Column::deleteNote(int noteIndex) {
    notes.erase(notes.begin() + noteIndex);
}

void Column::editNote(int noteIndex, Note* editedNote) {
    notes[noteIndex].setTitle(editedNote->getTitle());
    notes[noteIndex].setDescription(editedNote->getDescription());
    notes[noteIndex].setColor(editedNote->getColor());

    delete editedNote;
}


