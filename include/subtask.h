#ifndef SUBTASK_H
#define SUBTASK_H

#include "include/task.h"

class Subtask : public Task
{
private:
    bool done = false;

public:
    Subtask(QString description, QString priority);
    ~Subtask();
    void setDone(bool done);
    bool getDone();
};

#endif // SUBTASK_H
