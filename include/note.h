#ifndef NOTE_H
#define NOTE_H

#include <QColorDialog>

#include "include/task.h"

class Note : public Task
{
private:
    QColor color;

public:
    Note(QString title, QString description, QColor color = "#fdff9e", User* owner = new User("default", "default", "default", "default"));
    void setColor(QColor color);
    QColor getColor();

};

#endif // NOTE_H
