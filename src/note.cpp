#include "include/note.h"

Note::Note(QString title, QString description, QColor color, User* owner) {
    this->id = 0;
    this->title = title;
    this->description = description;
    this->color = color;
    this->owner = owner;
}

void Note::setColor(QColor color) {
    this->color = color;
}

QColor Note::getColor() {
    return this->color;
}
