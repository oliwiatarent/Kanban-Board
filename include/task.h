#ifndef TASK_H
#define TASK_H

#include <QString>

#include "include/user.h"

class Subtask;

using namespace std;

class Task {
public:
    int id;
    QString title;
    QString description;
    QString priority;
    vector<Subtask*> subtasks;
    User* owner;

    Task(QString title = "Title", QString description = "Description", QString priority = "Niski", User* owner = new User("default", "default", "default", "default"));
    void setId(int id);
    void setTitle(QString title);
    void setDescription(QString description);
    void setPriority(QString priority);
    int getId();
    QString getTitle();
    QString getDescription();
    QString getPriority();
    void addSubtask(Subtask* subtask);
    User* getOwner();
    Subtask* getSubtask(int index);
    int getNumberOfSubtasks();
    void deleteSubtask(int subtaskIndex);
};

#endif // TASK_H
