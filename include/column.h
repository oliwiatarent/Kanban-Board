#ifndef COLUMN_H
#define COLUMN_H

#include <vector>

#include "include/task.h"
#include "include/note.h"

using namespace std;

class Column
{
private:
    QString name;
    vector<Task> tasks;
    vector<Note> notes;

public:
    Column(QString name);

    int getNumberOfTasks();
    int getNumberOfNotes();
    QString getName();
    void setName(QString newName);
    Task* getTask(int index);
    void addTask(Task task);
    void deleteTask(int taskIndex);
    void editTask(int taskIndex, Task* editedTask);
    Note* getNote(int index);
    void addNote(Note note);
    void deleteNote(int noteIndex);
    void editNote(int noteIndex, Note* editedNote);

};

#endif // COLUMN_H
